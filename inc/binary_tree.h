#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct _node node;
typedef struct _hash_table node;

//RETORNA UMA ARVORE BINARIA VAZIA
binary_tree* create_empty_binary_tree();

//RETORNA UMA ARVORE BINARIA
binary_tree* create_binary_tree(void *item, int priority, binary_tree *next, binary_tree *left, binary_tree *right);

/*RECEBE O ITEM E PRIORIDADE CRIA UM NO E O ENFILEIRA DE ACORDO COM SUA PRIORIDADE
	E RETORNA O NO DE MENOR FREQUENCE DA FILA
*/
binary_tree* enqueue(binary_tree *bt, void *item, int priority);

//ORGANIZA A FILA DE NOS EM UMA ARVORE BINARIA E RETORNA A RAIZ DA ARVORE
binary_tree* queue_to_tree(binary_tree *bt);


#endif