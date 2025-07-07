// Euclides extendido para polinomios sobre GF(2^8), con coeficientes byte a byte
#include <iostream>
#include <iomanip>
#include <cstring>
#include "gf256.h"

#define FIELD_SIZE 256
#define MAX_DEGREE 8
#define PRIMITIVE_POLY 0x11B

typedef unsigned char byte;

// Polinomio con coeficientes byte (elementos en GF(2^8))
struct Polinomio {
    byte coef[MAX_DEGREE + 1];
    int grado;

    Polinomio() { memset(coef, 0, sizeof(coef)); grado = 0; }
};

void imprimir_polinomio(const char* nombre, const Polinomio& p) {
    std::cout << nombre << "(x) = ";
    bool primero = true;
    for (int i = p.grado; i >= 0; i--) {
        if (p.coef[i] != 0) {
            if (!primero) std::cout << " + ";
            std::cout << "0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (int)p.coef[i];
            if (i > 0) std::cout << "*x";
            if (i > 1) std::cout << "^" << i;
            primero = false;
        }
    }
    if (primero) std::cout << "0";
    std::cout << std::dec << std::endl;
}

void normalizar(Polinomio& p) {
    while (p.grado > 0 && p.coef[p.grado] == 0)
        p.grado--;
}

void copiar(const Polinomio& src, Polinomio& dst) {
    memcpy(dst.coef, src.coef, sizeof(src.coef));
    dst.grado = src.grado;
}

void suma(const Polinomio& a, const Polinomio& b, Polinomio& r) {
    memset(r.coef, 0, sizeof(r.coef));
    int maxdeg = std::max(a.grado, b.grado);
    for (int i = 0; i <= maxdeg; i++)
        r.coef[i] = gfadd(a.coef[i], b.coef[i]);
    r.grado = maxdeg;
    normalizar(r);
}

void multiplicar(const Polinomio& a, const Polinomio& b, Polinomio& r) {
    memset(r.coef, 0, sizeof(r.coef));
    for (int i = 0; i <= a.grado; i++) {
        for (int j = 0; j <= b.grado; j++) {
            if (i + j <= MAX_DEGREE)
                r.coef[i + j] ^= gfmul(a.coef[i], b.coef[j]);
        }
    }
    r.grado = a.grado + b.grado;
    if (r.grado > MAX_DEGREE) r.grado = MAX_DEGREE;
    normalizar(r);
}

void multiplicar_monomio(const Polinomio& p, byte escalar, int exp, Polinomio& r) {
    memset(r.coef, 0, sizeof(r.coef));
    for (int i = 0; i <= p.grado && i + exp <= MAX_DEGREE; i++)
        r.coef[i + exp] = gfmul(p.coef[i], escalar);
    r.grado = p.grado + exp;
    if (r.grado > MAX_DEGREE) r.grado = MAX_DEGREE;
    normalizar(r);
}

void dividir(const Polinomio& a, const Polinomio& b, Polinomio& q, Polinomio& r) {
    copiar(a, r);
    memset(q.coef, 0, sizeof(q.coef)); q.grado = 0;
    while (r.grado >= b.grado && r.grado >= 0 && b.grado >= 0 && b.coef[b.grado] != 0) {
        int d = r.grado - b.grado;
        byte factor = gfmul(r.coef[r.grado], gfinv(b.coef[b.grado]));
        q.coef[d] = factor;
        if (d > q.grado) q.grado = d;

        Polinomio tmp;
        multiplicar_monomio(b, factor, d, tmp);
        suma(r, tmp, r); // resta = suma en GF(2^8)
        normalizar(r);
        imprimir_polinomio("r: ", r);
    }
}



void euclides_extendido(Polinomio a, Polinomio b, Polinomio& d, Polinomio& x, Polinomio& y) {
    Polinomio r0 = a, r1 = b, s0, s1, t0, t1;
    memset(s0.coef, 0, sizeof(s0.coef)); s0.coef[0] = 1; s0.grado = 0;
    memset(s1.coef, 0, sizeof(s1.coef)); s1.grado = 0;
    memset(t0.coef, 0, sizeof(t0.coef)); t0.grado = 0;
    memset(t1.coef, 0, sizeof(t1.coef)); t1.coef[0] = 1; t1.grado = 0;

    while (!(r1.grado == 0 && r1.coef[0] == 0)) {
        Polinomio q, r, qs1, qt1, s, t;
        dividir(r0, r1, q, r);
        multiplicar(q, s1, qs1);
        suma(s0, qs1, s);
        multiplicar(q, t1, qt1);
        suma(t0, qt1, t);

        r0 = r1; r1 = r;
        s0 = s1; s1 = s;
        t0 = t1; t1 = t;
    }
    d = r0;
    x = s0;
    y = t0;
}



int main() {

    Polinomio a, b;
    a.coef[8] = 0x01; a.coef[7] = 0x00; a.coef[6] = 0x00; a.coef[5] = 0x00;
    a.coef[4] = 0x00;
    a.coef[3] = 0x00; a.coef[2] = 0x00; a.coef[1] = 0x00; a.coef[0] = 0x00;
    imprimir_polinomio("a", a);
    a.grado = 8;
    imprimir_polinomio("a", a);

    b.coef[8] = 0x00; b.coef[7] = 0xB3 ;b.coef[6] = 0xDC; b.coef[5] = 0xF9; b.coef[4] = 0x44; b.coef[3] = 0xB2;
    b.coef[2] = 0x69; b.coef[1] = 0x25; b.coef[0] = 0xA1;
    b.grado = 8;

    Polinomio d, x, y;
    euclides_extendido(a, b, d, x, y);

    imprimir_polinomio("a", a);
    imprimir_polinomio("b", b);
    imprimir_polinomio("d", d);
    imprimir_polinomio("x", x);
    imprimir_polinomio("y", y);

    Polinomio ax, by, suma_xy;
    multiplicar(a, x, ax);
    multiplicar(b, y, by);
    suma(ax, by, suma_xy);
    imprimir_polinomio("a*x + b*y", suma_xy);

    return 0;
}