#ifndef DECODER_H
#define DECODER_H

#include <vector>
#include <string>
using namespace std;

vector<uint8_t> decodificador(vector<uint8_t> bloque_con_ruido, int N, int K);

#endif // DECODER_H