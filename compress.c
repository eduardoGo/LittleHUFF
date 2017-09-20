#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.c"
#include "compress.h"
#include "hash_table.c"
#define MAX_SIZE 256

int* frequency(FILE *arq, int tam)
{
	int *freq;
	int i;
	freq = (int*) calloc(MAX_SIZE,sizeof(int));
	for(i = 0; i < tam; ++i)
	{
		freq[getc(arq)]++;
	}
	return freq;
}

int hash_fuction(void *key)
{
	return *((int*) key)
}

int compare(void *key1, void *key2)
{
	return *((unsigned char*) key1) == *((unsigned char*) key2);
}

// // This probrlem
// void codding(FILE *new_arq, FILE *arq, hash_table *dicionary, int size)
// {
// 	int i = 0;
// 	unsigned char byte;
// 	fseek(new_arq,16,SEEK_SET); //Os primeiros 16bits são do head
	
// 	for(i = 0; i < size; ++i)
// 	{
// 		byte = *((unsigned char*) get(dicionary,getc(arq), hash_fuction, compare));
// 		fprintf(new_arq,"%s", byte);
// 	}
// }

void compress(FILE *new_arq,FILE *arq, int tamanho)
{
	int *freq = frequency(arq,tamanho);
	int i;
	binary_tree *bt = create_empty_binary_tree();
	hash_table *dicionary;


	// for(i = 0; i < MAX_SIZE; ++i) printf("%d ", freq[i]); //printa o array de frequencia
	// printf("\n");
	
	for(i = 0; i<MAX_SIZE; ++i)
	{
		if( freq[i] )
		{
			int *code = (int *) malloc(sizeof(int));
			*code = i;
			bt = enqueue(bt,
			create_binary_tree( code, freq[i], NULL, NULL, NULL));
		}
	}
	bt = queue_to_tree(bt);
	// printf("Passou\n");
	// printf("Root: %c prioridade: %d\n", *(char*) bt->item,bt->priority);
	printf("\nCreatting dicionary...\n");
	dicionary = tree_to_table(bt);
	printf("Codding...\n");
	codding(new_arq,arq,dicionary,tamanho);


}
