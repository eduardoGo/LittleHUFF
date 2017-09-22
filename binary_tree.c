//#include "binary_tree.h"
#ifndef BINARY_TREE
#define COMPRESS_H
#include "hash_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _binary_tree binary_tree;

struct _binary_tree
{
	void *item;
	int priority;
	binary_tree *next;

	binary_tree *left;
	binary_tree *right;
};

binary_tree* create_empty_binary_tree()
{
	return NULL;
}

binary_tree* create_binary_tree(void *item, int priority, binary_tree *next, binary_tree *left, binary_tree *right)
{
	binary_tree *bt = (binary_tree*) malloc(sizeof(binary_tree));
	bt->item = item;
	bt->priority = priority;
	bt->next = next;
	bt->left = left;
	bt->right = right;

	return bt;
}

binary_tree* enqueue(binary_tree *bt, void *item, int priority)
{
	binary_tree *new_element = create_binary_tree(item, priority, NULL, NULL, NULL);
	if(bt == NULL)
	{
		new_element->next = bt;
		bt = new_element;

	}
	else if(bt->priority >= new_element->priority)
	{
		new_element->next = bt;
		bt = new_element;

	}
	else
	{
		binary_tree *current = bt;
		while(bt->next != NULL && bt->next->priority < new_element->priority)
		{
			current = current->next;
		}

		new_element->next = current->next;
		current->next = new_element;
	}
	printf("aqui\n");
	return bt;

}

binary_tree* enqueue_node(binary_tree *queue, binary_tree *parent)
{
	parent->next = queue;
	queue = parent;
	return queue;
}

binary_tree* queue_to_tree(binary_tree *bt)
{

	if(bt != NULL && bt->next != NULL)
	{
		binary_tree *next = bt->next;
		int priority = bt->priority + next->priority;

		unsigned char *flag = (unsigned char *) malloc(sizeof(unsigned char));
		*flag = '*';

		binary_tree *parent = create_binary_tree(flag, priority, bt, next, NULL);
		return queue_to_tree( enqueue_node(next->next, parent) );

	} else {
		return bt;
	}
}

int hash_function(void *key)
{
	return *( (int*) key );
}

int compare(void *key1, void *key2)
{
	return *((unsigned char*) key1) == *((unsigned char*) key2);
}

void mapping(binary_tree *bt, hash_table *ht, unsigned char *code, int depth)
{
	if(bt->left == NULL && bt->right == NULL)
	{
		unsigned char *value = (unsigned char *) malloc(10 * sizeof(unsigned char));
		strcpy(value, code);

		put(ht, bt->item, value, hash_function,compare);
	
	} else {
		code[depth] = '0';
		code[depth + 1] = '\0';
		mapping(bt->left, ht, code, depth + 1);

		code[depth] = '1';
		code[depth + 1] = '\0';
		mapping(bt->right, ht, code, depth + 1);

	} 
}

hash_table* tree_to_table(binary_tree *bt)
{
	hash_table *ht = create_hash_table();
	unsigned char code[10];
	mapping(bt, ht, code, 0);
	return ht;
}

void insert_tree(binary_tree *bt, char *tree, int *i)
{
	if(bt != NULL)
	{
		if(*((char*) bt->item) == '*' && bt->left == NULL && bt->right == NULL) //Caracter de escape
		{
			*(tree + *i ) = '\\';
			*i = *i+1;
		}
		*(tree + *i ) = *((char*) bt->item);
		*i = *i+1;
		insert_tree(bt->left,tree,i);
		insert_tree(bt->right,tree,i);
	}
}
char* tree_pre_order(binary_tree *bt, int *i)
{
	char *tree;
	i = (int*) malloc(1*sizeof(char));
	tree = (char*) malloc(8200*sizeof(char)); //MAX_SIZE da arvore '8200'
	*i = 0;
	insert_tree(bt,tree,i);
	*(tree + *i ) = '\0';
	tree = realloc(tree, *(i) * sizeof(char)); //realloc de acordo com o tamanho da arvore (i)

	return tree;
}

#endif
