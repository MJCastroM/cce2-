#ifndef DECODER_H
#define DECODER_H

#include <vector>
#include <string>
using namespace std;

string decodificador(vector<uint8_t> bloque_con_ruido, int N, int K);
void compute_syndromes(uint8_t r[64], uint8_t s[8]);

#endif // DECODER_H