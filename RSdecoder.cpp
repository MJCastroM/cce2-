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

bool leerArchivoBinarioPorBloques(const string& nombreArchivo, int tamanioBloque,
                                  vector<vector<uint8_t>>& bloques) {
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo binario: " << nombreArchivo << endl;
        return false;
    }

    vector<uint8_t> bloqueActual(tamanioBloque);
    while (archivo.read(reinterpret_cast<char*>(bloqueActual.data()), tamanioBloque)) {
        bloques.push_back(bloqueActual);
    }

    // Si quedan bytes sueltos al final
    streamsize bytesRestantes = archivo.gcount();
    if (bytesRestantes > 0) {
        bloqueActual.resize(bytesRestantes);
        archivo.read(reinterpret_cast<char*>(bloqueActual.data()), bytesRestantes); 
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
    vector<vector<uint8_t>> bloques;
    printf("Se lee el archivo en: test_files/test_codificado.brst para ver si hubo error: \n");
    if (leerArchivoBinarioPorBloques("test_files/test_codificado.brst", N, bloques)) {
        for (const auto& bloque : bloques) {
            string res = decodificador(bloque, N, K);
            cout << res;
    }
}
    return 0;
}