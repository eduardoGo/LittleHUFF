#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.c"

int* frequency(FILE *arq, int tam)
{
	int *freq;
	int i;
	freq = (int*) calloc(256,sizeof(int));
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

	//for(i = 0; i < 256; ++i) printf("%d ", freq[i]); //printa o array de frequencia
	
	/*
	Esse for ta enfileirando mas ta enfileirando e repetindo tds os elementos
	por exemplo, se eu enfileirar o 'a', ai tds os elementos da fila fica 'a'
	não consegui identificar porque ta acontecendo isso, please deem uma olhada
	for(i = 0; i<256; ++i)
	{
		if(freq[i] != 0)
		{
			bt = enqueue(bt,
			create_binary_tree( &i, freq[i],NULL,NULL,NULL));
			//printf("%c\n", *(char*)bt->item);
		}
	}
	*/

}