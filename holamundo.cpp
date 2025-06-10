#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

using namespace std;

// Función para ejecutar un .exe y capturar su salida
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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <nombre_archivo_sin_extension>" << endl;
        return 1;
    }

    string entrada = argv[1];
    string salida = "salida.txt";

    string comando = "RS_brstchannel_Utils\\Windows\\rsencode.exe " + entrada + " " + salida;

    try {
        string resultado = ejecutarComando(comando);
        cout << "Salida del ejecutable:\n" << resultado << endl;
    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }

    return 0;
}

