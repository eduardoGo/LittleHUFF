#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/binary_tree.h"
#include "../inc/hash_table.h"

/*RECEBE PONTEIRO PARA O ARQUIVO COMPACTADO E OUTRO PONTEIRO PARA O ARQUIVO ONDE
DEVERÁ SER ESCRITO O CONTEUDO DESCOMPACTADO*/
void decompress(FILE * file, FILE *new_file);

#endif