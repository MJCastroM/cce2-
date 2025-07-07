#include "decoder.h"
#include "gf256.h"
#include <fstream>
#include <iostream>
using namespace std;

void compute_syndromes(const vector<uint8_t> r, int num_syndromes, vector<uint8_t>& s) {
    s.resize(num_syndromes);

    for (int i = 0; i < num_syndromes; i++) {
        uint8_t sum = 0;
        int largo_bloque = r.size();
        for (int j = 0; j < largo_bloque; j++) {
            uint8_t power = gfpow(2, (i+1)*j);  // α^{i·j}
            uint8_t term  = gfmul(r[j], power);
            sum = gfadd(sum, term);
        }
        s[i] = sum;
    }
}

string decodificador(vector<uint8_t> bloque_con_ruido, int N, int K) {
    vector<uint8_t> sindromes;
    compute_syndromes(bloque_con_ruido, 8, sindromes);
    bool error = false;
    for (int i=0 ; i<8; i++) {
        if (!error && sindromes[i] != 0) {
            error = true;
        }
    }
    if (error) {
        vector<uint8_t> bloque_decodificado;

        return "E";
    }
    else return "N";

};
