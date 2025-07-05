#ifndef DECODER_H
#define DECODER_H

#include <vector>
#include <string>

vector<int> decodificador(vector<int> a_decodificar, int N, int K);
void compute_syndromes(uint8_t r[64], uint8_t s[8]);

#endif // DECODER_H