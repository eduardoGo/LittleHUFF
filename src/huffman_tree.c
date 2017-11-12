
#include "../inc/huffman_tree.h"
//REMOVER INCLUDES ABAIXO POSTERIORMENTE, USADOS EM TESTES
#include <string.h>
#include <stdio.h>

struct _huffman_tree
{
	void *item;
	int priority;
	huffman_tree *next;

	huffman_tree *left;
	huffman_tree *right;
};

huffman_tree* create_empty_huffman_tree()
{
	return NULL;
}

huffman_tree* create_huffman_tree(void *item, int priority, huffman_tree *next, huffman_tree *left, huffman_tree *right)
{
	huffman_tree *tree = (huffman_tree*) malloc(sizeof(huffman_tree));
	
	if(tree != NULL)
	{
		tree->item = item;
		tree->priority = priority;
		tree->next = next;
		tree->left = left;
		tree->right = right;
	}

	return tree;
}

huffman_tree* enqueue(huffman_tree *tree, huffman_tree *new_element)
{	
	if(tree == NULL || tree->priority >= new_element->priority)
	{
		new_element->next = tree;
		tree = new_element;

	} else{
		huffman_tree *current = tree;
		while(current->next != NULL && current->next->priority < new_element->priority)
		{
			current = current->next;
		}

		new_element->next = current->next;
		current->next = new_element;
	}

	return tree;

}

huffman_tree* queue_to_tree(huffman_tree *tree)
{

	if(tree != NULL && tree->next != NULL)
	{
		huffman_tree *next = tree->next;
		huffman_tree *new_head = next->next;
		int priority = tree->priority + next->priority;

		unsigned char *flag = (unsigned char *) malloc(sizeof(unsigned char));
		*flag = '*';

		huffman_tree *parent = create_huffman_tree(flag, priority, NULL, tree, next);
		next->next = NULL;
		tree->next = NULL;

		return queue_to_tree( enqueue(new_head, parent) );

	} else {
		return tree;
	}
}

int hash_function(void *key)
{
	return *( (int*) key );
}

void mapping(huffman_tree *tree, hash_table *ht, unsigned char *code, int depth)
{
	if(tree->left == NULL && tree->right == NULL)
	{
		unsigned char *value = (unsigned char *) malloc(10 * sizeof(unsigned char));
		strcpy(value, code);

		unsigned char *item = (unsigned char *) malloc(sizeof(unsigned char));
		*item = *((unsigned char *) tree->item);
		put(ht, item, value, hash_function);
	
	} else {
		code[depth] = '0';
		code[depth + 1] = '\0';
		mapping(tree->left, ht, code, depth + 1);

		code[depth] = '1';
		code[depth + 1] = '\0';
		mapping(tree->right, ht, code, depth + 1);

	} 
}

hash_table* tree_to_table(huffman_tree *tree)
{
	hash_table *ht = NULL;

	if(tree != NULL) {
		ht = create_hash_table();
		unsigned char code[10];
		mapping(tree, ht, code, 0);
	}

	return ht;
}

huffman_tree* get_next(huffman_tree *tree)
{
	if(tree != NULL)
	{
		return tree->next;
	} else {
		return tree;
	}
}

unsigned char get_item(huffman_tree *tree)
{
	if(tree != NULL)
	{
		return *( (unsigned char*) tree->item ); 
	} else {
		return -1;
	}
}

unsigned char *string_tree = NULL;

void traversal_pre_order(huffman_tree *tree, short int *id)
{
	if(tree != NULL){

		if(tree->left == NULL && tree->right == NULL && (get_item(tree) == 42 || get_item(tree) == 92) )
		{
			string_tree[*id] = '\\';
			*id += 1;
		}

		string_tree[*id] = get_item(tree);
		*id += 1 ;
		traversal_pre_order(tree->left, id);
		traversal_pre_order(tree->right, id);
	}
}

unsigned char* traversal_tree(huffman_tree *tree, short int *id)
{
	if(tree != NULL) {
		//São reservados 13 bits para o tamanho da árvore
		//O tamanho máximo é 2^13 = 8192
		string_tree = (unsigned char *) malloc(8300*sizeof(char));
		*id = 0;
		traversal_pre_order(tree, id);
	}
	return string_tree;
}

huffman_tree* rebuild_tree(huffman_tree *tree, FILE *file)
{
	unsigned char *aux = (unsigned char*) malloc(sizeof(unsigned char));
	*aux = getc(file);

	if(*aux == '\\')
	{
		*aux = getc(file);
		tree = create_huffman_tree(aux, 0, NULL, NULL, NULL);
		return tree;
			
	}
	else if(*aux == '*')
	{ 
		tree = create_huffman_tree(aux, 0, NULL, NULL, NULL);
		tree->left = rebuild_tree(tree->left, file);
		tree->right = rebuild_tree(tree->right, file);
		return tree;
	}
	else
	{
		tree = create_huffman_tree(aux, 0, NULL, NULL, NULL);
		return tree;
	}
}
void write_file(huffman_tree *root, FILE *file, FILE *new_file, short int trash)
{
	unsigned char byte,previous_byte;
	int i;

	huffman_tree * tree = root;

	byte = getc(file);
	previous_byte = byte;

	while ( fscanf(file, "%c", &byte ) != EOF ) //Tava bugando com o getc
	{
		
		for (i = 7; i >= 0; i--)
		{
			if (tree->left == NULL && tree->right == NULL)
			{
				fprintf(new_file, "%c", *((unsigned char*)tree->item));
				tree = root;	
			}

			if((previous_byte >> i) & 1) tree = tree->right;
			else tree = tree->left;
		}

		previous_byte = byte;
	}

	for(i = 7; i >= trash; --i )
	{

		if(tree->left == NULL && tree->right == NULL)
		{
			fprintf(new_file, "%c", *((unsigned char*) tree->item));
			tree = root;
		}

		if(previous_byte >> i & 1)
			tree = tree->right;
		else tree = tree->left;

	}

	if(tree->left == NULL && tree->right == NULL)
	{
		fprintf(new_file, "%c", *((unsigned char*) tree->item));
	}


}