#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#include "compress.h"
#include "hash_table.h"
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

hash_table* dicionary(binary_tree *bt,hash_table *dicionary)
{
	unsigned char byte;
	char *path;
	path = (char*) calloc(10,sizeof(char));
	back_track(bt, path,dicionary);
}

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
	printf("Creatting dicionary...\n");
	dicionary = tree_to_table(bt);

}
