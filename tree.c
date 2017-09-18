#include <stdio.h>
#include <stdlib.h>

typedef struct TREE tree;

// STRUCT da árvore

struct TREE{
	unsigned char byte;
	int frequency;
	tree next;
	tree left;
	tree right;
};
/*
	Somente adciona o nó na frente da lista.
  Retorna um poteiro para o nó que foi adcionado
*/
tree* add_element(tree *tree, unsigned char byte, int frequency)
{
	tree *temp = (tree*) malloc(1*sizeof(tree));
	temp->left = NULL;
	temp->right = NULL;
	temp->next = NULL;
	tree->next = temp;
	temp->byte = byte;
	temp->frequency = frequency;
	return temp;
}
//FALTA O RESTO
