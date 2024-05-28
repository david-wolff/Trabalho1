// main.c
#include "codifica.h"
#include "trees.h"
#include <stdio.h>

void process_files(const char *input_txt, const char *output_bin, const char *output_txt, struct compactadora tree[]) {
    FILE *arqTexto = fopen(input_txt, "rb");
    if (!arqTexto) {
        printf("Failed to open text file %s for reading.\n", input_txt);
        return;
    }

    FILE *arqBin = fopen(output_bin, "wb");
    if (!arqBin) {
        printf("Failed to open binary file %s for writing.\n", output_bin);
        fclose(arqTexto);
        return;
    }

    compacta(arqTexto, arqBin, tree);
    fclose(arqTexto);
    fclose(arqBin);

    arqBin = fopen(output_bin, "rb");
    FILE *arqTextoOut = fopen(output_txt, "wb");
    if (arqBin && arqTextoOut) {
        descompacta(arqBin, arqTextoOut, tree);
        fclose(arqBin);
        fclose(arqTextoOut);
    } else {
        if (!arqBin) printf("Failed to open binary file %s for reading.\n", output_bin);
        if (!arqTextoOut) printf("Failed to open text file %s for writing.\n", output_txt);
    }
}

int main() {
    process_files("k1.txt", "k1.bin", "k1.out.txt", compacta_normal);
    process_files("k2.txt", "k2.bin", "k2.out.txt", compacta_normal);
    process_files("k3.txt", "k3.bin", "k3.out.txt", compacta_normal);
    process_files("k4.txt", "k4.bin", "k4.out.txt", compacta_normal);
    process_files("k5.txt", "k5.bin", "k5.out.txt", compacta_normal);
    process_files("k6.txt", "k6.bin", "k6.out.txt", compacta_normal);
    process_files("k7.txt", "k7.bin", "k7.out.txt", compacta_normal);
    process_files("k8.txt", "k8.bin", "k8.out.txt", compacta_normal);

    return 0;
}
