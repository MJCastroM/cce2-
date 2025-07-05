#include "decoder.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib> 
#include <vector>
#include <string>
#include <array>
using namespace std;

#define K 56
#define R 8
#define N 64

bool leerArchivoPorBloques(const string& nombreArchivo, int tamanioBloque, vector<vector<int>>& bloques) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return false;
    }

    int simbolo;
    vector<int> bloqueActual;

    while (archivo >> simbolo) {
        bloqueActual.push_back(simbolo);
        if (bloqueActual.size() == tamanioBloque) {
            bloques.push_back(bloqueActual);
            bloqueActual.clear();
        }
    }

    // Si quedaron símbolos sin completar el último bloque
    if (!bloqueActual.empty()) {
        bloques.push_back(bloqueActual);
    }

    archivo.close();
    return true;
}

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
    printf("Se generan bloques de codigo aleatorios con comando: utils\\Windows\\brstchannel.exe -q 256 -n 56 -R 10000 test_files/test_original.dat\n");
    // 2. Codificar archivo
    resultado = ejecutarComando("utils\\Windows\\rsencode.exe -m 8 -n 64 -r 16 -L 1 -8 test_files/test_original.dat test_files/test_codificado.rse");
    printf("Se codifican los bloques con comando: utils\\Windows\\rsencode.exe -m 8 -n 64 -r 16 -L 1 -8 test_files/test_original.dat test_files/test_codificado.rse\n");
    // 3. Pasar por canal ruidoso
    resultado = ejecutarComando("utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.01 test_files/test_codificado.rse");
    printf("Se simula el paso por un canal ruidoso con comando: utils\\Windows\\brstchannel.exe --fieldsize 256 --delta 0.75 --rho 0.01 test_files/test_codificado.rse\n");
    // 4. Leer archivo con errores
    vector<vector<int>> bloques;
    if (leerArchivoPorBloques("test_files/test_ruidoso.rse", 64, bloques)) {
        for (const auto& bloque : bloques) {
            vector<int> resultado = decodificador(bloque, 64, 48);
    }
}
    return 0;
}