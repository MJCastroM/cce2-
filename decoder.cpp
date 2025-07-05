#include "decoder.h"
#include "gf256.h"
#include <fstream>
#include <iostream>
using namespace std;

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

vector<int> decodificador(vector<int> bloque_con_ruido, int N, int K) {
    uint8_t sindromes[8];
    compute_syndromes(bloque_con_ruido, sindromes);
    vector<int> bloque_decodificado;
    return bloque_decodificado;
};
