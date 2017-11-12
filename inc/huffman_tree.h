#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "hash_table.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct _huffman_tree huffman_tree;

//RETORNA UMA ARVORE BINARIA VAZIA
huffman_tree* create_empty_huffman_tree();

//RETORNA UMA ARVORE BINARIA
huffman_tree* create_huffman_tree(void *item, int priority, huffman_tree *next, huffman_tree *left, huffman_tree *right);

/*RECEBE UM NO E O ENFILEIRA DE ACORDO COM SUA PRIORIDADE
	E RETORNA O NO DE MENOR FREQUENCE DA FILA
*/
huffman_tree* enqueue(huffman_tree *tree, huffman_tree *new_element);

//ORGANIZA A FILA DE NOS EM UMA ARVORE BINARIA E RETORNA A RAIZ DA ARVORE
huffman_tree* queue_to_tree(huffman_tree *tree);

//RECEBE UMA ARVORE BINARIA E RETORNA UMA HASH TABLE COM A CODIFICACAO DE HUFFMAN
hash_table* tree_to_table(huffman_tree *tree);

//RECEBE UMA ARVORE BINARIA E RETORNA UMA STRING COM SUA REPRESENTACAO EM PRE ORDEM 
unsigned char* traversal_tree(huffman_tree *tree, short int *id);

//RECEBE UM NO DE UMA ARVORE E RETORNA UM INTEIRO DO ITEM QUE ESSE NO CONTEM
unsigned char get_item(huffman_tree *tree);

//RECEBE UM NO ENFILEIRADO E RETORNA O PROXIMO
huffman_tree* get_next(huffman_tree *tree);

//RECEBE UM ARQUIVO COM UMA ARVORE BINARIA EM PRE ORDEM E MONTA A ARVORE DE ACORDO COM A ESTRUTURA
huffman_tree* rebuild_tree(huffman_tree *tree,FILE *file);

void print_pre_order(huffman_tree *tree);

//RECEBE UMA ARVORE BINARIA, UM ARQUIVO VAZIO E O ARQUIVO A SER DESCOMPRIMIDO E ESCREVE A DESCOMPRESSAO
// NO ARQUIVO VAZIO. 
void write_file(huffman_tree *root, FILE *file, FILE *new_file, short int trash);

#endif