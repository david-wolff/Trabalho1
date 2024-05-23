#include "codifica.h"

int main() {
    struct compactadora v[32] = {
        {' ', 0b0000, 4},
        {'A', 0b0001, 4},
        {'B', 0b0010, 4},
        {'C', 0b0011, 4},
        {'D', 0b0100, 4},
        {'E', 0b0101, 4},
        {'F', 0b0110, 4},
        {'G', 0b0111, 4},
        {'H', 0b1000, 4},
        {'I', 0b1001, 4},
        {'J', 0b1010, 4},
        {'K', 0b1011, 4},
        {'L', 0b1100, 4},
        {'M', 0b1101, 4},
        {'N', 0b1110, 4},
        {'O', 0b1111, 4},
        {'P', 0b00000, 5},
        {'Q', 0b00001, 5},
        {'R', 0b00010, 5},
        {'S', 0b00011, 5},
        {'T', 0b00100, 5},
        {'U', 0b00101, 5},
        {'V', 0b00110, 5},
        {'W', 0b00111, 5},
        {'X', 0b01000, 5},
        {'Y', 0b01001, 5},
        {'Z', 0b01010, 5},
        {'.', 0b01011, 5},
        {',', 0b01100, 5},
        {'\n', 0b01101, 5},
        {4, 0b01110, 5} // EOT
    };

    FILE *arqTexto = fopen("teste1.txt", "rb");
    if (!arqTexto) {
        printf("Failed to open text file for reading.\n");
        return 1;
    }

    FILE *arqBin = fopen("teste1.bin", "wb");
    if (!arqBin) {
        printf("Failed to open binary file for writing.\n");
        fclose(arqTexto);
        return 1;
    }

    compacta(arqTexto, arqBin, v);
    fclose(arqTexto);
    fclose(arqBin);

    arqBin = fopen("teste1.bin", "rb");
    FILE *arqTextoOut = fopen("teste1.out.txt", "wb");
    if (arqBin && arqTextoOut) {
        descompacta(arqBin, arqTextoOut, v);
        fclose(arqBin);
        fclose(arqTextoOut);
    }


    return 0;
}