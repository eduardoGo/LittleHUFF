#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE_ 250

typedef struct _binary_tree binary_tree;
typedef struct NODE node;
typedef struct _hash_table hash_table;


struct NODE
{
	void* key;
	void* value;	
};


struct _hash_table
{
	node* table[MAX_SIZE_];
};

struct _binary_tree
{
	void *item;
	int priority;
	binary_tree *next;

	binary_tree *left;
	binary_tree *right;
};

hash_table* create_hash_table()
{
	hash_table *ht = (hash_table*) malloc(sizeof(hash_table));
	node *new;

	int i;
	for(i=0; i<MAX_SIZE_; i++)
	{
		new = (node*) malloc(sizeof(node));
		ht->table[i] = new;

	}

	return ht;
}


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

void print_pre_order(binary_tree *bt)
{

	if(bt != NULL)
	{
		printf("%c ", *(char*) bt->item);
		print_pre_order(bt->left);
		print_pre_order(bt->right);
	}
}


binary_tree* queue_to_tree(binary_tree *bt)
{
	char *i = (char*) malloc(10*sizeof(char));
	*(i) = '#';
 	bt = create_binary_tree(i, rand() & 10,NULL,NULL,NULL);
 	*(i+1) = '*';
 	bt->right = create_binary_tree(i+1, rand() & 10,NULL,NULL,NULL);
 	*(i+2) = '@';	
  	bt->left = create_binary_tree(i+2, rand() & 10,NULL,NULL,NULL);
  	*(i+3) = '&';
  	bt->right->right = create_binary_tree(i+3, rand() & 10,NULL,NULL,NULL);
  	*(i+4) = '(';
  	bt->right->left = create_binary_tree(i+4, rand() & 10,NULL,NULL,NULL);
  	*(i+5) = ')';
  	bt->left->right = create_binary_tree(i+5, rand() & 10,NULL,NULL,NULL);
  	*(i+6) = '$';
  	bt->left->left = create_binary_tree(i+6, rand() & 10,NULL,NULL,NULL);
  	*(i+7) = '!';

  	return bt;
 }

void print_hash(hash_table *ht)
{
	int i;
	for(i = 0; i < 8; ++i)
	{
		printf("[%d] Key: '%c' Value: %s\n", i, * (char*) ht->table[i]->key, (char*) ht->table[i]->value);
	}
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
	tree = (char*) malloc(8200*sizeof(char)); //MAX_SIZE da arvore '8200'
	*i = 0;
	insert_tree(bt,tree,i);
	*(tree + *i ) = '\0';
	tree = realloc(tree, *(i) * sizeof(char)); //realloc de acordo com o tamanho da arvore (i)
	printf("Array com elementos da arvore em pre ordem:\n");
	printf("%s\n", tree);
	printf("Size: %d\n", *i);
	return tree;
}


hash_table* tree_to_table(binary_tree *bt)
{
	int k;
	hash_table *ht = create_hash_table();
	char *i = (char*) malloc(10*sizeof(char));
	char **value;
	value = (char**) malloc(10*sizeof(char*));
	
	for( k = 0; k < 10; ++k) value[k] = (char*) malloc(10*sizeof(char));


	*(i) = '#';
	value[0] = "00";

	ht->table[0]->key =  i;
	ht->table[0]->value = value[0];


	*(i+1) = 'F';
	value[1] = "01";

	ht->table[1]->key =  i+1;
	ht->table[1]->value = value[1];

	*(i+2) = '@';
	value[2] = "10";


	ht->table[2]->key =  i+2;
	ht->table[2]->value =value[2];

	*(i+3) = '&';
	value[3] = "11";

	ht->table[3]->key =  i+3;
	ht->table[3]->value = value[3];
	*(i+4) = '(';
	value[4] = "001";

	ht->table[4]->key =  i+4;
	ht->table[4]->value =value[4];

	*(i+5) = ')';
	value[5] = "010";


	ht->table[5]->key =  i+5;
	ht->table[5]->value =value[5];

	*(i+6) = '$';
	value[6] = "100";

	ht->table[6]->key =  i+6;
	ht->table[6]->value =value[6];

	*(i+7) = '!';
	value[7] = "011";

	ht->table[7]->key =  i+7;
	ht->table[7]->value =value[7];

	return ht;
	
	

}


binary_tree* enqueue(binary_tree *bt, void *item, int priority)
{
	printf("Enfileirou '%c' --> Prioridade %d\n", *(char*) item,priority);

	return bt;

}

void* get(hash_table *dicionary,void* key, int (*hash_function)(void *key))
{
	int i;
	int h = hash_function(key) % 8;
	//printf("Pegar a key: %d\n", h);
	return dicionary->table[h]->value;
}