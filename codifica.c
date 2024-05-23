#include "codifica.h"
#include <stdio.h>

void compacta(FILE *arqTexto, FILE *arqBin, struct compactadora v[]) {
    char ch;
    int found;
    unsigned char bit_buffer = 0;
    int bits_in_buffer = 0;

    printf("Starting compression...\n");
    while ((ch = fgetc(arqTexto)) != EOF) {
        printf("Reading char: %c (%d)\n", ch, ch);  
        if (ch == '\r') {
            printf("Skipping carriage return.\n");
            continue; 
        }
        found = 0;
        for (int i = 0; i < 32 && !found; i++) {
            if (v[i].simbolo == ch) {
                found = 1;
                printf("Writing code for %c: ", ch);
                for (int j = v[i].tamanho - 1; j >= 0; j--) {
                    bit_buffer = (bit_buffer << 1) | ((v[i].codigo >> j) & 1);
                    bits_in_buffer++;
                    if (bits_in_buffer == 8) {
                        printf("%c", bit_buffer);
                        fputc(bit_buffer, arqBin);
                        bit_buffer = 0;
                        bits_in_buffer = 0;
                    }
                }
                printf("\n");
            }
        }
        if (!found) {
            printf("Character not in Huffman table: %c (%d)\n", ch, ch);
        }
    }
    if (bits_in_buffer > 0) {
        bit_buffer <<= (8 - bits_in_buffer);
        fputc(bit_buffer, arqBin);
    }
    printf("Compression complete.\n");
}

void descompacta(FILE *arqBin, FILE *arqTexto, struct compactadora v[]) {
    int bit_count = 0;
    unsigned int buffer = 0;
    int bit;
    int input_byte;

    printf("Starting decompression...\n");
    while ((input_byte = fgetc(arqBin)) != EOF) {
        for (int k = 7; k >= 0; k--) {
            bit = (input_byte >> k) & 1;
            buffer = (buffer << 1) | bit;
            bit_count++;
            printf("Bit read: %d (Buffer: %d, Count: %d)\n", bit, buffer, bit_count);
            for (int i = 0; i < 32; i++) {
                if (bit_count == v[i].tamanho && buffer == v[i].codigo) {
                    if (v[i].simbolo == '\0') {
                        printf("EOT found, stopping.\n");
                        return;
                    }
                    fputc(v[i].simbolo, arqTexto);
                    printf("Decompressed to: %c\n", v[i].simbolo);
                    buffer = 0;
                    bit_count = 0;
                    break;
                }
            }
        }
    }
    printf("Decompression complete.\n");
}


