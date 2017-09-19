#include "binary_tree.h"
#include "hash_table.h"
#include <stdlib.h>

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

binary_tree* enqueue(binary_tree *bt, binary_tree *new_element)
{
	if(bt == NULL || bt->priority >= new_element->priority)
	{
		new_element->next = bt;
		bt = new_element;

	} else{
		binary_tree *current = bt;
		while(bt->next != NULL && bt->next->priority < new_element->priority)
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

		unsigned char *flag = (unsigned char *) malloc(sizeof(unsigned char));
		*flag = '*';

		binary_tree *parent = create_binary_tree(flag, priority, bt, next, NULL);
		return queue_to_tree( enqueue(next->next, parent) );

	} else {
		return bt;
	}
}

int hash_function(void *key)
{
	return *( (int*) key );
}

int equals(void *key1, void *key2)
{
	return ( *(int*) key1 ) == *( (int*) key2 );
}

unsigned char set_bit(unsigned char c, int i)
{
	unsigned char mask = 1 << i;
	return c | mask;
}

int is_bit_i_set(unsigned char c, int i)
{
	unsigned char mask = 1 << i;
	return c & mask;
}

void mapping(binary_tree *bt, hash_table *ht, unsigned char code, int depth)
{
	if(bt->left == NULL && bt->right == NULL)
	{
		unsigned char *value = (unsigned char *) malloc(sizeof(unsigned char));
		*value = code;

		put(ht, bt->item, value, hash_function, equals);
	
	} else {

		mapping(bt->left, ht, code, depth + 1);
		code = set_bit(code, 8 - depth);
		mapping(bt->right, ht, code, depth + 1);

	} 
}

hash_table* tree_to_table(binary_tree *bt)
{
	hash_table *ht = create_hash_table();
	mapping(bt, ht, 0, 0);


}
