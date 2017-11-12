#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/huffman_tree.h"
#include "../inc/hash_table.h"

#define MAX_SIZE 256

//RECEBE UM ARQUIVO VAZIO,O ARQUIVO QUE VAI SER COMPACTADO E O TAMANHO DO
//ARQUIVO QUE SERÁ COMPACTADO. COMPACTA O ARQUIVO.

void compress(FILE *new_file, FILE *file, int file_size);


#endif