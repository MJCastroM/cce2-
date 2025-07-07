#include "decoder.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib> 
#include <vector>
#include <string>
#include <array>
#include <algorithm>
using namespace std;

bool leerYProcesarBloques(const string& nombreArchivo, int tamanio_bloque, int redundancia) {
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo binario: " << nombreArchivo << endl;
        return false;
    }

    vector<uint8_t> bloque(tamanio_bloque);
    int bloqueIndex = 0;

    while (archivo.read(reinterpret_cast<char*>(bloque.data()), tamanio_bloque)) {
        // Procesar bloque individual
        reverse(bloque.begin(), bloque.end());
        vector<uint8_t> resultado = decodificador(bloque, tamanio_bloque, (tamanio_bloque - redundancia));
        bloqueIndex++;
    }

    archivo.close();
    return true;
}

int main(int argc, char* argv[]) {
    // . Leer archivo con errores
    leerYProcesarBloques(argv[3], stoi(argv[1]), stoi(argv[2]));
    return 0;
}
