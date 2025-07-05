#include "decoder.h"
#include "gf256.h"
#include <fstream>
#include <iostream>
using namespace std;

void compute_syndromes(const vector<uint8_t>& r, int num_syndromes, vector<uint8_t>& s) {
    s.resize(num_syndromes);

    for (int i = 0; i < num_syndromes; ++i) {
        uint8_t sum = 0;
        for (int j = 0; j < r.size(); ++j) {
            uint8_t power = gfpow(1, (i + 1) * j);  // α^{(i+1)·j}
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
    for (uint8_t s : sindromes) {
        if (!error && s != 0) {
            error = true;
        }
    }
    if (error) {
        vector<uint8_t> bloque_decodificado;
        // Aca sigue el verdadero proceso de decodificacion
        return "Hubo error";
    }
    else return "No hubo error";

};
