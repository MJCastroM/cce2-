#include "decoder.h"
#include "gf256.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;
typedef vector<uint8_t> poly;

void compute_syndromes(const vector<uint8_t> r, int num_syndromes, vector<uint8_t>& s) {
    s.resize(num_syndromes);

    for (int i = 0; i < num_syndromes; i++) {
        uint8_t sum = 0;
        int largo_bloque = r.size();
        for (int j = 0; j < largo_bloque; j++) {
            uint8_t power = gfpow(2, (i+1)*j);  // α^{i+1·j}
            uint8_t term  = gfmul(r[j], power);
            sum = gfadd(sum, term);
        }
        s[i] = sum;
    }
}

// Elimina ceros a la izquierda
void poly_trim(poly &p) {
    while (!p.empty() && p.back() == 0) {
        p.pop_back();
    }
}

// Multiplicación de polinomios
poly poly_mul(const poly &a, const poly &b) {
    poly result(a.size() + b.size() - 1, 0);
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < b.size(); ++j) {
            result[i + j] = gfadd(result[i + j], gfmul(a[i], b[j]));
        }
    }
    poly_trim(result);
    return result;
}

void print_poly(const poly &p, const char *name) {
    printf("%s(x) = ", name);
    bool first = true;
    for (int i = p.size() - 1; i >= 0; --i) {
        if (p[i] != 0) {
            if (!first) printf("+ ");
            printf("0x%02X*x^%d ", p[i], i);
            first = false;
        }
    }
    printf("\n");
}

// División de polinomios: devuelve cociente y resto
pair<poly, poly> poly_div(const poly &a, const poly &b) {
    poly dividend = a;
    poly divisor = b;
    poly quotient(dividend.size(), 0);

    poly_trim(dividend);
    poly_trim(divisor);

    while (!dividend.empty() && dividend.size() >= divisor.size()) {
        int coef_pos = dividend.size() - 1;
        int shift = coef_pos - (divisor.size() - 1);
        uint8_t factor = gfmul(dividend.back(), gfinv(divisor.back()));

        quotient[shift] = factor;

        for (size_t i = 0; i < divisor.size(); ++i) {
            dividend[shift + i] ^= gfmul(divisor[i], factor);
        }
        poly_trim(dividend);
    }

    poly_trim(quotient);
    poly_trim(dividend);  // el resto
    return {quotient, dividend};
}

// Algoritmo de Euclides extendido para polinomios en GF(2^8)
// Encuentra el polinomio localizador (sigma) y evaluador (omega)
void euclid(const poly &a, const poly &b, int max_deg, poly &sigma, poly &omega) {
    poly r0 = a;
    poly r1 = b;
    poly t0 = {0};
    poly t1 = {1};

    poly_trim(r0);
    poly_trim(r1);

    // Iterar hasta que deg(r1) < floor(max_deg / 2)
    while (!r1.empty() && r1.size() - 1 >= max_deg/ 2) {
        // División r0 / r1 → cociente q y resto r
        pair<poly, poly> div = poly_div(r0, r1);
        poly q = div.first;
        poly r = div.second;

        // t = t0 - q * t1
        poly qt1 = poly_mul(q, t1);
        if (t0.size() > qt1.size())
            qt1.resize(t0.size(), 0);
        else if (qt1.size() > t0.size())
            t0.resize(qt1.size(), 0);
        for (size_t i = 0; i < t0.size(); ++i) {
            qt1[i] = gfadd(qt1[i],t0[i]);
        }

        // Avanzar
        r0 = r1;
        r1 = r;
        t0 = t1;
        t1 = qt1;
    }

    sigma = t1;
    omega = r1;

    poly_trim(sigma);
    poly_trim(omega);
}

uint8_t poly_eval(const poly &p, uint8_t x) {
    uint8_t result = 0;
    for (int i = p.size() - 1; i >= 0; --i) {
        result = gfadd(gfmul(result, x), p[i]);
    }
    return result;
}


vector<int> chien_search(const poly &sigma, int n) {
    vector<int> error_positions;
    for (int i = 0; i < n; ++i) {
        // Evaluar sigma en α^{-i}
        uint8_t xi = gfalog[(255-i)];
        if (poly_eval(sigma, xi) == 0) {
            // Error en la posición i (del final hacia el principio)
            error_positions.push_back(i);
        }
    }
    return error_positions;
}

poly poly_deriv(const poly &p) {
    poly result;
    for (size_t i = 1; i < p.size(); i += 2) {  // solo grados impares
        result.push_back(p[i]);
        result.push_back(0);
    }
    poly_trim(result);
    return result;
}

// Corrige el bloque recibido en las posiciones de error usando Forney
void forney_correct(vector<uint8_t> &received, const poly &sigma, const poly &omega, const vector<int> &error_positions) {
    // Derivada de σ(x)
    poly sigma_deriv = poly_deriv(sigma);
    int n = received.size();  // debería ser 64 para RS(64,56)
    for (int pos : error_positions) {
        // Definimos X_j = α^{-i} = gfinv( α^i )
        uint8_t xj = gfinv(gfalog[pos]);

        // Evaluar Ω(x) y σ'(x)
        uint8_t numerator   = poly_eval(omega, xj);
        uint8_t denominator = poly_eval(sigma_deriv, xj);
        if (denominator == 0) {
            fprintf(stderr, "Forney error: división por cero en pos %d (σ'(x)=0).\n", pos);
            continue;
        }
        
        // Fórmula de Forney: e_j = Ω(x) / σ'(x) 
        uint8_t mj =  gfmul(numerator, gfinv(denominator));
        // Corregir con suma en GF(256) (XOR)
        received[pos] = gfadd(received[pos], mj);
    }
}

pair <bool,vector<uint8_t>> decodificador(vector<uint8_t> bloque_con_ruido, int N, int K) {
    vector<uint8_t> bloque_original = bloque_con_ruido;
    vector<uint8_t> sindromes;
    compute_syndromes(bloque_con_ruido, (N-K), sindromes);
    bool error = false;
    for (int i=0 ; i<(N-K); i++) {
        if (!error && sindromes[i] != 0) {
            error = true;
        }
    }
    if (error) {
        poly pol_loc_err, pol_ev_err;
        poly a((N-K), 0); a.push_back(1); 
        euclid(a, sindromes, N - K, pol_loc_err, pol_ev_err);
        vector<int> error_positions = chien_search(pol_loc_err, N);
        if (pol_loc_err.size() - 1 > error_positions.size()) {
            return make_pair(error, bloque_con_ruido);
        }
            forney_correct(bloque_con_ruido, pol_loc_err, pol_ev_err, error_positions); 
           bool error2 = false;    
        vector<uint8_t> sindromes_post;
        compute_syndromes(bloque_con_ruido, N-K, sindromes_post);
        for (int i=0 ; i<(N-K); i++) {
        if (!error2 && sindromes_post[i] != 0) {
            error2 = true;
        }}
        if (error2) bloque_con_ruido = bloque_original;
    }
    return make_pair(error, bloque_con_ruido);

};
