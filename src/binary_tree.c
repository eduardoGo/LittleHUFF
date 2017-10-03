
#include "../inc/binary_tree.h"
//REMOVER INCLUDES ABAIXO POSTERIORMENTE, USADOS EM TESTES
#include <string.h>
#include <stdio.h>

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

//FUNÇÃO DE TESTE REMOVER POSTERIORMENTE
void print_queue(binary_tree *bt)
{
	binary_tree *node = bt;
	while(node->next != NULL)
	{
		printf("%x --> ", *(char*)node->item);
		node = node->next;
	}
}

//FUNÇÃO DE TESTE REMOVER POSTERIORMENTE
void print_pre_order(binary_tree *bt)
{
		if(bt != NULL)
		{
			printf("%c ", *(char*)bt->item);
			print_pre_order(bt->left);
			print_pre_order(bt->right);
		}
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

unsigned char *tree = NULL;

void traversal_pre_order(binary_tree *bt, short int *id)
{
	if(bt != NULL){

		if( bt->left == NULL && bt->right == NULL && (get_item(bt) == 42 || get_item(bt) == 92)){ /* caracteres * e \ */
			tree[*id] = '\\';
			*id += 1;
		}
		tree[*id] = get_item(bt);
		*id += 1 ;
		traversal_pre_order(bt->left, id);
		traversal_pre_order(bt->right, id);
	}
}
unsigned char* traversal_tree(binary_tree *bt, short int *id)
{
	tree = (unsigned char *) malloc(8300*sizeof(char));
	*id = 0;
	traversal_pre_order(bt, id);
	return tree;
}

binary_tree* rebuild_tree(binary_tree *bt, FILE *file)
{
	unsigned char *aux = (unsigned char*) malloc(sizeof(unsigned char));
	*aux = getc(file);

	if(*aux == '\\')
	{
		*aux = getc(file);
		bt = create_binary_tree(aux, 0, NULL, NULL, NULL);
		return bt;
			
	}
	else if(*aux == '*')
	{ 
		bt = create_binary_tree(aux, 0, NULL, NULL, NULL);
		bt->left = rebuild_tree(bt->left, file);
		bt->right = rebuild_tree(bt->right, file);
		return bt;
	}
	else
	{
		bt = create_binary_tree(aux, 0, NULL, NULL, NULL);
		return bt;
	}
}
void write_file(binary_tree *root, FILE *file, FILE *new_file, short int trash)
{
	unsigned char byte,previous_byte;
	int i;

	binary_tree * bt = root;

	byte = getc(file);
	previous_byte = byte;

	while ( fscanf(file, "%c", &byte ) != EOF ) //Tava bugando com o getc
	{
		
		for (i = 7; i >= 0; i--)
		{
			if (bt->left == NULL && bt->right == NULL)
			{
				fprintf(new_file, "%c", *((unsigned char*)bt->item));
				bt = root;	
			}

			if((previous_byte >> i) & 1) bt = bt->right;
			else bt = bt->left;
		}

		previous_byte = byte;
	}

	for(i = 7; i >= trash; --i )
	{

		if(bt->left == NULL && bt->right == NULL)
		{
			fprintf(new_file, "%c", *((unsigned char*) bt->item));
			bt = root;
		}

		if(previous_byte >> i & 1)
			bt = bt->right;
		else bt = bt->left;

	}


}