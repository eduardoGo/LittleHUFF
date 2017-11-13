#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/huffman_tree.h"
#include "../inc/hash_table.h"

/*RECEBE PONTEIRO PARA O ARQUIVO COMPACTADO E OUTRO PONTEIRO PARA O ARQUIVO ONDE
DEVERÁ SER ESCRITO O CONTEUDO DESCOMPACTADO*/
void decompress(FILE * file, FILE *new_file);
/* RECEBE UM PONTEIRO PARA O ARQUIVO COMPACTADO E RETORNA O LIXO QUE ESTÁ CONTIDO NO ULTIMO BYTE DO ARQUIVO */
int get_trash(FILE *arquivo);

/* RECEBE UM PONTEIRO PARA O ARQUIVO COMPACTADO E RETORNA O TAMANHO DA ARVORE QUE CONTEM A CONDIFICAÇÃO DOS BYTES */
int get_size_tree(FILE *file);

#endif
