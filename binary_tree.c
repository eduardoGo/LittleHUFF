#include "binary_tree.h"
#include <stdlib.h>

typedef struct _binary_tree binary_tree;

struct binary_tree
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

binary_tree* enqueue(binary_tree *bt, binary_tree *new_element)
{
	if(bt == NULL || bt->priority >= priority)
	{
		new_element->next = bt;
		bt = new_element;

	} else{
		binary_tree *current = bt;
		while(bt->next != NULL && bt->next->priority < priority)
		{
			current = current->next;
		}

		new_element->next = current->next;
		current->next = new_element;
	}

	return bt;

}

binary_tree* queue_to_tree(binary_tree *bt)
{

	if(bt != NULL && bt->next != NULL)
	{
		binary_tree *next = bt->next;
		int priority = bt->priority + next->priority;
		binary_tree *parent = create_binary_tree('*', priority, bt, next, NULL);
		return queue_to_tree( enqueue(next->next, parent) );

	} else {
		return bt;
	}
}
