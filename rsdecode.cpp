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

tuple<int, int, int> leerYProcesarBloques(const string& nombreArchivo, int tamanio_bloque, int redundancia, const string& nombreDestino) {
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        cerr << "Uso: rsdecode.exe [m] [r] archivoentrada.ext [archivosalida]" << endl;
        return make_tuple(0, 0, 0);
    }

    ofstream salida(nombreDestino, ios::binary | ios::app);
    if (!salida.is_open()) {
        cerr << "No se pudo abrir el archivo de salida: " << nombreDestino << endl;
        return make_tuple(0, 0, 0);
    }

    vector<uint8_t> bloque(tamanio_bloque);
    int bloqueIndex = 0;
    int sin_error = 0;
    int corregidos = 0;
    int no_corregidos = 0;
    const int datos_utiles = tamanio_bloque - redundancia;

    while (archivo.read(reinterpret_cast<char*>(bloque.data()), tamanio_bloque)) {
        // Invertir el bloque (si es necesario)
        for (int i = 0, j = tamanio_bloque - 1; i < j; i++, j--) {
            std::swap(bloque[i], bloque[j]);
        }

        auto resultado = decodificador(bloque, tamanio_bloque, datos_utiles);

        // Contabilizar estadísticas
        if (!resultado.first) {
            sin_error++;
        } else if (bloque == resultado.second) {
            no_corregidos++;
        } else {
            corregidos++;
        }

        // Revertir el bloque corregido (si era necesario)
        for (int i = 0, j = resultado.second.size() - 1; i < j; i++, j--) {
            std::swap(resultado.second[i], resultado.second[j]);
        }

        // Guardar solo los datos útiles (K bytes)
        salida.write(reinterpret_cast<const char*>(resultado.second.data()), datos_utiles);
        bloqueIndex++;
    }

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
    tuple <int, int, int> estadisticas = leerYProcesarBloques(argv[3], stoi(argv[1]), stoi(argv[2]), nombreDestino);
    cout << "Bloques sin error: " << get<0>(estadisticas) << endl;
    cout << "Bloques corregidos: " << get<1>(estadisticas) << endl;
    cout << "Bloques sin corregir: " << get<2>(estadisticas) << endl;
    return 0;
}
