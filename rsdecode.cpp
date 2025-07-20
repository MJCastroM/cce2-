#include "decoder.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib> 
#include <vector>
#include <string>
#include <array>
#include <tuple>
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

tuple<int, int, int> leerYProcesarBloques(const string& nombreArchivo, int tamanio_bloque, int redundancia, string nombreDestino) {
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        cout << "Recuerde:" << endl;
        cout << "Uso: rsdecode.exe [m] [r] archivoentrada.ext [archivosalida]" << endl;
        return make_tuple(0, 0, 0);
    }

    vector<uint8_t> bloque(tamanio_bloque);
    int bloqueIndex = 0;
    int sin_error = 0;
    int corregidos = 0;
    int no_corregidos = 0;

    while (archivo.read(reinterpret_cast<char*>(bloque.data()), tamanio_bloque)) {
        // Procesar bloque individual
        reverse(bloque.begin(), bloque.end());
        pair <bool, vector<uint8_t>> resultado = decodificador(bloque, tamanio_bloque, (tamanio_bloque - redundancia));
        // Armado de estadisticas
        if (!resultado.first)     
            sin_error++;
        else {if (bloque == resultado.second)
            no_corregidos++;
            else corregidos++;}

        reverse(resultado.second.begin(), resultado.second.end());
        resultado.second.resize(56);
        guardar(resultado.second, nombreDestino);
        bloqueIndex++;
    }

    archivo.close();
    return make_tuple(sin_error, corregidos, no_corregidos);
}

int main(int argc, char* argv[]) {
    if (argc < 4 || argc > 5) {
        cout << "Uso: rsdecode.exe [m] [r] archivoentrada.ext [archivosalida]" << endl;
        cout << endl;
        cout << "archivoentrada             : archivo a decodificar" << endl;
        cout << "archivosalida              : archivo decodificado (por defecto: 'archivoentrada.out')" << endl;
        cout << endl;
        cout << "Parametros:" << endl;
        cout << "m <largocodigo>            : largo del codigo" << endl;
        cout << "r <redundancia>            : redundancia del codigo" << endl;
        cout << endl;
        cout << "Nota: debe especificar los parametros m, r y la entrada." << endl;
        return 0;
    }
    string nombreDestino;
    if (argc == 5) {
        nombreDestino = argv[4];
    } else {
        nombreDestino = argv[3];
        size_t punto = nombreDestino.rfind('.');
        nombreDestino = nombreDestino.substr(0, punto) + ".out";
    }
    

    // Crear archivo vacío al inicio (truncar si ya existe)
    ofstream limpiar(nombreDestino, ios::trunc | ios::binary);
    if (!limpiar) {
        cerr << "Error al crear el archivo: " << nombreDestino << endl;
        return 1;
    }
    limpiar.close();
    // . Leer archivo con errores
    tuple <int, int, int> estadisticas = leerYProcesarBloques(argv[3], stoi(argv[1]), stoi(argv[2]), nombreDestino);
    cout << "Bloques sin error: " << get<0>(estadisticas) << endl;
    cout << "Bloques corregidos: " << get<1>(estadisticas) << endl;
    cout << "Bloques sin corregir: " << get<2>(estadisticas) << endl;
    return 0;
}
