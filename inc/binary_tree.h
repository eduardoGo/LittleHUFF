#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "hash_table.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct _binary_tree binary_tree;

//RETORNA UMA ARVORE BINARIA VAZIA
binary_tree* create_empty_binary_tree();

//RETORNA UMA ARVORE BINARIA
binary_tree* create_binary_tree(void *item, int priority, binary_tree *next, binary_tree *left, binary_tree *right);

/*RECEBE UM NO E O ENFILEIRA DE ACORDO COM SUA PRIORIDADE
	E RETORNA O NO DE MENOR FREQUENCE DA FILA
*/
binary_tree* enqueue(binary_tree *bt, binary_tree *new_element);

//ORGANIZA A FILA DE NOS EM UMA ARVORE BINARIA E RETORNA A RAIZ DA ARVORE
binary_tree* queue_to_tree(binary_tree *bt);

//RECEBE UMA ARVORE BINARIA E RETORNA UMA HASH TABLE COM A CODIFICACAO DE HUFFMAN
hash_table* tree_to_table(binary_tree *bt);

//RECEBE UMA ARVORE BINARIA E RETORNA UMA STRING COM SUA REPRESENTACAO EM PRE ORDEM 
unsigned char* traversal_tree(binary_tree *bt, short int *id);

//RECEBE UM NO DE UMA ARVORE E RETORNA UM INTEIRO DO ITEM QUE ESSE NO CONTEM
unsigned char get_item(binary_tree *bt);

//RECEBE UM NO ENFILEIRADO E RETORNA O PROXIMO
binary_tree* get_next(binary_tree *bt);

//RECEBE UM ARQUIVO COM UMA ARVORE BINARIA EM PRE ORDEM E MONTA A ARVORE DE ACORDO COM A ESTRUTURA
binary_tree* rebuild_tree(binary_tree *bt,FILE *file);

void print_pre_order(binary_tree *bt);

#endif