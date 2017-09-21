#ifndef BINARY_TREE_H
#define BINARY_TREE_H

//RETORNA UMA ARVORE BINARIA VAZIA
binary_tree* create_empty_binary_tree();

//RETORNA UMA ARVORE BINARIA
binary_tree* create_binary_tree(void *item, int priority, binary_tree *next, binary_tree *left, binary_tree *right);

/*ENFILEIRA UM NO DA ARVORE BINARIA DE ACORDO COM SUA PRIORIDADE
	E RETORNA O NO DE MENOR FREQUENCE DA FILA
*/
binary_tree* enqueue(binary_tree *bt, binary_tree *new_element);

//ORGANIZA A FILA DE NOS EM UMA ARVORE BINARIA E RETORNA A RAIZ DA ARVORE
binary_tree* queue_to_tree(binary_tree *bt);

/*
	Recebe uma arvore e um ponteiro para string vazia e retorna o ponteiro para string contendo a arvore em pre ordem
*/

char* tree_pre_order(binary_tree *bt, char *tree);

#endif