//#include "binary_tree.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct BINARY_TREE binary_tree;

struct BINARY_TREE
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


void print_queue(binary_tree *bt)
{
	binary_tree *current = bt;
	while(current != NULL)
	{
		printf("Item: '%c', frequencia: %d\n", *(char*)current->item,current->priority);
		current = current->next;
	}
}


binary_tree* enqueue(binary_tree *bt, binary_tree *new_element)
{
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
		while(current->next != NULL && bt->next->priority < new_element->priority)
		{
			current = current->next;
		}

		new_element->next = current->next;
		current->next = new_element;
	}
	print_queue(bt);//Só pra verificar como ta a fila
	return bt;

}

binary_tree* queue_to_tree(binary_tree *bt)
{

	if(bt != NULL && bt->next != NULL)
	{
		binary_tree *next = bt->next;
		int priority = bt->priority + next->priority;
		binary_tree *parent = create_binary_tree((char*) '*', priority, bt, next, NULL);
		return queue_to_tree( enqueue(next->next, parent) );

	} else {
		return bt;
	}
}
