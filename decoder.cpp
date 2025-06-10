#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <fstream>

using namespace std;
        




/*
[a^0 a^0 a^0 a^0 a^0 a^0 a^0 a^0]
[a^0 a^1 a^2 a^3 a^4 a^5 a^6 a^7]
[a^0 a^2 a^4 a^6 a^0 a^2 a^4 a^6]
[a^0 a^3 a^6 a^1 a^4 a^7 a^2 a^5]
[a^0 a^4 a^0 a^4 a^0 a^4 a^0 a^4]
[a^0 a^5 a^2 a^7 a^4 a^1 a^6 a^3]
[a^0 a^6 a^4 a^2 a^0 a^6 a^4 a^2]
[a^0 a^7 a^6 a^5 a^4 a^3 a^2 a^1]*/







// Función para ejecutar un .exe y capturar su salida
/*try {
        string resultado = ejecutarComando(comando);
        cout << "Salida del ejecutable:\n" << resultado << endl;
    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }*/
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

// Función que implementa el algoritmo de Euclides
int mcd(int a, int b) {
    while (b != 0) {
        int resto = a % b;
        a = b;
        b = resto;
    }
    return a;
}

void copiarArchivoPorBloques(const string& archivoEntrada, const string& archivoSalida, size_t tamBloque = 8) {
    char* buffer = new char[tamBloque];

    ifstream entrada(archivoEntrada, ios::binary);
    ofstream salida(archivoSalida, ios::binary);

    if (!entrada) {
        cerr << "Error al abrir archivo de entrada: " << archivoEntrada << endl;
        delete[] buffer;
        return;
    }

    if (!salida) {
        cerr << "Error al abrir archivo de salida: " << archivoSalida << endl;
        delete[] buffer;
        return;
    }

    while (!entrada.eof()) {
        entrada.read(buffer, tamBloque);
        streamsize bytesLeidos = entrada.gcount();
        //aca tengo la palabra de tamaño de bloque
        //aca hay que procesar
        salida.write(buffer, bytesLeidos);
    }

    entrada.close();
    salida.close();
    delete[] buffer;

    cout << "Copia finalizada correctamente." << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Faltan parámetros";
        return 1;
    }
    string n            = argv[1];
    string r            = argv[2];
    string channelfile  = argv[3];

    copiarArchivoPorBloques(channelfile, channelfile+"2");
    cout << n + r + channelfile;

    return 0;
}

