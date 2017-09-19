#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.c"
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
void compress(FILE *arq, int tamanho)
{
	int *freq = frequency(arq,tamanho);
	int i;
	binary_tree *bt = create_empty_binary_tree();

	//for(i = 0; i < MAX_SIZE; ++i) printf("%x ", freq[i]); //printa o array de frequencia
	
	
	for(i = 0; i<MAX_SIZE; ++i)
	{
		if( freq[i] )
		{
			int *code = (int *) malloc(sizeof(int));
			*code = i;
			bt = enqueue(bt,
			create_binary_tree( code, freq[i], NULL, NULL, NULL));
			//printf("%c\n", *(char*)bt->item);
		}
	}

}