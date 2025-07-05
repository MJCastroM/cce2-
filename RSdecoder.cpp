#include "decoder.h"
#include <iostream>
#include <cstdlib>  // Para system()
#include <vector>
#include <string>
#include <array>
using namespace std;

#define K 56
#define R 8
#define N 64

string ejecutarComando(const string& comando) {
    array<char, 128> buffer;
    string resultado;

    FILE* pipe = _popen(comando.c_str(), "r");
    if (!pipe) {
        throw runtime_error("Error al ejecutar el comando");
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        resultado += buffer.data();
    }

    _pclose(pipe);
    return resultado;
}

int main() {
    string resultado;
    // 1. Generar archivo original
    resultado = ejecutarComando("utils\\Windows\\brstchannel.exe -q 256 -n 56 -R 10000 test_files/test_original.dat");
    printf("Se utiliza comando: utils\\Windows\\brstchannel.exe -q 256 -n 56 -R 10000 test_files/test_original.dat y se obtiene salida: ", resultado);
    // 2. Codificar archivo
    resultado = ejecutarComando("utils\\Windows\\rsencode.exe -m 8 -n 64 -r 16 -L 1 -8 test_files/test_original.dat test_files/test_codificado.rse");
    printf("Se utiliza comando: utils\\Windows\\rsencode.exe -m 8 -n 64 -r 16 -L 1 -8 test_files/test_original.dat test_files/test_codificado.rse y se obtiene salida: ", resultado);
    // 3. Pasar por canal ruidoso
    resultado = ejecutarComando("utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.01 test_codificado.rse");
    printf("Se utiliza comando: utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.01 test_codificado.rse y se obtiene salida: ", resultado);
    // 4. Leer archivo con errores
    return 0;
}