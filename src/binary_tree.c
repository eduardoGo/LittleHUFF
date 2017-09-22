#include "../inc/binary_tree.h"
#include <string.h>

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
	
	if(bt != NULL)
	{
		bt->item = item;
		bt->priority = priority;
		bt->next = next;
		bt->left = left;
		bt->right = right;
	}

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
		while(current->next != NULL && current->next->priority < new_element->priority)
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
		binary_tree *new_head = next->next;
		int priority = bt->priority + next->priority;

		unsigned char *flag = (unsigned char *) malloc(sizeof(unsigned char));
		*flag = '*';

		binary_tree *parent = create_binary_tree(flag, priority, NULL, bt, next);
		next->next = NULL;
		bt->next = NULL;

		return queue_to_tree( enqueue(new_head, parent) );

	} else {
		return bt;
	}
}

int hash_function(void *key)
{
	return *( (int*) key );
}

void mapping(binary_tree *bt, hash_table *ht, unsigned char *code, int depth)
{
	if(bt->left == NULL && bt->right == NULL)
	{
		unsigned char *value = (unsigned char *) malloc(10 * sizeof(unsigned char));
		strcpy(value, code);

		unsigned char *item = (unsigned char *) malloc(sizeof(unsigned char));
		*item = *((unsigned char *) bt->item);

		put(ht, item, value, hash_function);
	
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

binary_tree* get_next(binary_tree *bt)
{
	return bt->next;
}

unsigned char get_item(binary_tree *bt)
{
	return *( (unsigned char*) bt->item ); 
}

char *tree = NULL;
int id = 0;

void traversal_pre_order(binary_tree *bt)
{
	if(bt != NULL){

		if( bt->left == NULL && bt->right == NULL && (get_item(bt) == 42 || get_item(bt) == 92)){ /* caracteres * e \ */
			tree[id++] = '\\';
		}
		tree[id++] = get_item(bt);
		traversal_pre_order(bt->left);
		traversal_pre_order(bt->right);
	}
}

char* traversal_tree(binary_tree *bt)
{
	tree = (char *) malloc(8300*sizeof(char));
	traversal_pre_order(bt);
	tree[id] = '\0';
	return tree;
}