#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "gf256.h"

#define K 56
#define R 8
#define N 64

void compute_syndromes(uint8_t r[64], uint8_t s[8]) {
    for (int i = 0; i < 8; i++) {
        uint8_t sum = 0;
        for (int j = 0; j < 64; j++) {
            uint8_t power = gfpow(1, (i + 1) * j);  // α^{(i+1)·j}
            uint8_t term  = gfmul(r[j], power);
            sum = gfadd(sum, term);
        }
        s[i] = sum;
    }
}

// Test
int main() {
//rsencode --redundancy 8 --rootstart 0 holamundo.txt holamundo4.dat
    uint8_t data[K] = {0};
    uint8_t parity[R] = {0};
    uint8_t syndromes[R] = {0};
    uint8_t received[64] = {
        // 56 bytes de datos
        0x71, 0x75, 0x65, 0x20, 0x70, 0x61, 0x73, 0x61,
        0x3F, 0x20, 0x74, 0x6F, 0x78, 0x64, 0x6F, 0x20,
        0x62, 0x69, 0x65, 0x6E, 0x3F, 0x20, 0x73, 0x69,
        0x20, 0x73, 0x69, 0x20, 0x73, 0x69, 0x20, 0x6E,
        0x6F, 0x20, 0x6E, 0x6F, 0x20, 0x6E, 0x6F, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

        // Paridad RS (8 bytes)
        0x91, 0xE4, 0x93, 0x80, 0x96, 0x20, 0x24, 0xC5
    };

    // Simular errores opcionales (descomentar)
    // received[10] ^= 0x11;
    // received[35] ^= 0xA7;

    // Calcular síndromes
    compute_syndromes(received, syndromes);

    printf("Mensaje original:\n%s\n\n");

    printf("Síndromes:\n");
    for (int i = 0; i < R; i++) {
        printf("S[%d] = 0x%02X\n", i + 1, syndromes[i]);
    }

    return 0;
}
