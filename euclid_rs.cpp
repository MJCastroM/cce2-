#include <vector>
#include <stdint.h>
#include <stdio.h>
#include "gf256.h"

using namespace std;

typedef vector<uint8_t> poly;

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
            result[i + j] ^= gfmul(a[i], b[j]);
        }
    }
    poly_trim(result);
    return result;
}

// División de polinomios: devuelve cociente y resto
pair<poly, poly> poly_div(const poly &a, const poly &b) {
    poly dividend = a;
    poly divisor = b;
    poly quotient(dividend.size(), 0);

    poly_trim(dividend);
    poly_trim(divisor);

    while (dividend.size() >= divisor.size() && !dividend.empty()) {
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
void euclid(const poly &syndromes, int max_deg, poly &sigma, poly &omega) {
    poly r0 = poly(syndromes);
    poly r1 = {1};
    poly t0 = {0};
    poly t1 = {1};

    poly_trim(r0);
    r0.resize(max_deg + 1, 0);  // padding con ceros si es necesario
    poly_trim(r0);

    while (r0.size() > max_deg / 2) {
        auto [q, r] = poly_div(r0, r1);
        poly temp_r = r;
        poly temp_t = poly_mul(q, t1);
        for (size_t i = 0; i < temp_t.size(); ++i) {
            if (i < t0.size()) {
                temp_t[i] ^= t0[i];
            }
        }
        r0 = r1;
        r1 = temp_r;
        t0 = t1;
        t1 = temp_t;
    }

    sigma = t1;
    omega = r1;

    poly_trim(sigma);
    poly_trim(omega);
}

// Debug: imprimir polinomio
void print_poly(const poly &p, const char *name) {
    printf("%s(x) = ", name);
    for (int i = p.size() - 1; i >= 0; --i) {
        if (p[i] != 0) {
            printf("%s0x%02X·x^%d ", (i != (int)p.size() - 1 ? "+ " : ""), p[i], i);
        }
    }
    printf("\n");
}
