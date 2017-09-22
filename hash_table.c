#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"
#define MAX_SIZE 256

struct NODE
{
	void* key;
	void* value;	
};

struct _hash_table
{
	node* table[MAX_SIZE];
};

hash_table* create_hash_table()
{
	hash_table *ht = (hash_table*) malloc(sizeof(hash_table));
	int i;
	for(i=0; i<MAX_SIZE; i++)
	{
		ht->table[i] = NULL;
	}

	return ht;
}

void put(hash_table *ht, void *key, void *value, int (*hash_function)(void *key), int (*equals)(void *key1, void *key2))
{
	int h = (* hash_function)(key);
	int count = 0;
	while(ht->table[h] != NULL && count < MAX_SIZE)
	{
		if( equals(ht->table[h]->key, key) )
		{
			ht->table[h]->value = value;
			break;
		}

		h = ( h + 1 ) % MAX_SIZE;
		count++;
	}

	if(ht->table[h] == NULL)
	{
		node *new_element = (node*) malloc(sizeof(node));
		new_element->key = key;
		new_element->value = value;
		ht->table[h] = new_element;
	}

}

void* get(hash_table *ht, void *key, int (*hash_function)(void *key), int (*equals)(void *key1, void *key2))
{
	int h = hash_function(key);
	int count = 0;
	while(ht->table[h] != NULL && count < MAX_SIZE)
	{
		if( (*equals)(ht->table[h]->key, key) )
		{
			return ht->table[h]->value;
		}

		h = ( h + 1 ) % MAX_SIZE;
		count++;
	}

	return NULL;
}