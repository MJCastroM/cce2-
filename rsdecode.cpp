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

void guardar(const vector<uint8_t>& datos, const string& nombre_archivo) {
    ofstream archivo(nombre_archivo, ios::app | ios::binary);
    if (!archivo) {
        cerr << "Error al abrir el archivo: " << nombre_archivo << endl;
        return;
    }

    for (uint8_t byte : datos) {
        archivo << static_cast<char>(byte);
    }

    archivo.close();
}

bool leerYProcesarBloques(const string& nombreArchivo, int tamanio_bloque, int redundancia, string nombreDestino) {
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
        cout << "Bloque " << bloqueIndex << ":" << endl;
        vector<uint8_t> resultado = decodificador(bloque, tamanio_bloque, (tamanio_bloque - redundancia));
        reverse(resultado.begin(), resultado.end());
        resultado.resize(55);
        guardar(resultado, nombreDestino);
        bloqueIndex++;
    }

    archivo.close();
    return true;
}

int main(int argc, char* argv[]) {
    string nombreDestino = argv[3];
    size_t punto = nombreDestino.rfind('.');
    nombreDestino = nombreDestino.substr(0, punto) + ".out";

    // Crear archivo vacío al inicio (truncar si ya existe)
    ofstream limpiar(nombreDestino, ios::trunc | ios::binary);
    if (!limpiar) {
        cerr << "Error al crear el archivo: " << nombreDestino << endl;
        return 1;
    }
    limpiar.close();
    // . Leer archivo con errores
    leerYProcesarBloques(argv[3], stoi(argv[1]), stoi(argv[2]), nombreDestino);
    return 0;
}
