#include <stdio.h>
#include <stdlib.h>

// Función que imprime un byte en binario
void print_byte_as_binary(unsigned char byte) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (byte >> i) & 1);
    }
    printf(" ");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s holamundo3.txt\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb"); // abrir en modo binario
    if (!file) {
        perror("Error al abrir el archivo");
        return 1;
    }

    unsigned char buffer;
    while (fread(&buffer, sizeof(unsigned char), 1, file) == 1) {
        print_byte_as_binary(buffer);
    }

    fclose(file);
    return 0;
}
