#ifndef CODIFICA_H
#define CODIFICA_H

#include <stdio.h>

struct compactadora {
    char simbolo;
    unsigned int codigo;
    int tamanho;
};

void compacta(FILE *arqTexto, FILE *arqBin, struct compactadora v[]);
void descompacta(FILE *arqBin, FILE *arqTexto, struct compactadora v[]);

#endif
