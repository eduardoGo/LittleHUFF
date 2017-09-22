#include <stdio.h>
#include <stdlib.h>
#include "../inc/binary_tree.h"
#include "../inc/hash_table.h"
#include "../inc/compress.h"

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
	fseek(arq,0,SEEK_SET);
	return freq;
}



int hash_fuction(void *key)
{
	return *((int*) key);
}


char add_byte(unsigned char byte, int pos)
{
	unsigned mask = 1 << (7 - pos);
	return mask | byte;
}

void set_trash(FILE *new_arq,unsigned char trash)
{
	unsigned char byte;
	byte = getc(new_arq);
	trash = trash << 5;
	byte = byte & trash;
	fprintf(new_arq,"%c",byte);
}


void set_tree_size(FILE *new_arq,short int tree_size)
{
	unsigned char byte1 = (tree_size & 255);
	unsigned char byte2 = ((tree_size >> 8) & 255);
	fprintf(new_arq, "%c", byte2);
	fprintf(new_arq, "%c", byte1);

}


void set_tree(FILE *new_arq, char *tree)
{
  while(*tree != '\0')
  {
  	fprintf(new_arq,"%c", *(tree++));
  }
}


void codding(FILE *new_arq, FILE *arq, hash_table *dicionary,int size_arq,binary_tree *bt)
{
	int i,j,pos;

	unsigned char byte = 0,trash = 0;
	char *current,*tree;
	int *tree_size = (int*) malloc(sizeof(int));
	
	fprintf(new_arq,"%c", byte);
	fprintf(new_arq,"%c", byte);

	tree = tree_pre_order(bt,tree_size); //Ponteiro para uma string que contem a arvore em pre ordem
										  // tambem coloca o tamanho da arvore no ponteiro *tree_size
	
	set_tree(new_arq,tree); //Coloca a arvore em pre ordem no arquivo
	fseek(new_arq,*tree_size,SEEK_CUR); //Seta o fluxo corrente a partir da arvore

	
	pos = j = i = 0;

	for(j = 0; j < size_arq; ++j)
	{
		unsigned char *aux = (unsigned char*) malloc(1*sizeof(unsigned char));
		*aux = getc(arq);
		current = (unsigned char*) get(dicionary, aux, hash_fuction);
		while(current[i] != '\0')
		{
			if(pos == 8)
			{
				fprintf(new_arq,"%c", byte);
				byte = 0;
				pos = 0;	
			}
			if(current[i] == '1') byte = add_byte(byte,pos);

			pos++;
			i++;
		}
	}
	
	fseek(new_arq,0,SEEK_SET); //Seta o fluxo corrente no inicio do arquivo
	set_tree_size(new_arq,*tree_size);
	
	if(pos != 0)
	{
		trash = 8 - pos; //trash contem a quantidade de bits que nao estao em uso no ultimo byte do arquivo
		set_trash(new_arq,trash);
	}


}



void compress(FILE *new_arq,FILE *arq, int tamanho)
{
	printf("Take frequency...\n");
	
	int *freq = frequency(arq,tamanho);
	int i;
	binary_tree *bt = create_empty_binary_tree();
	hash_table *dicionary;

	for(i = 0; i < MAX_SIZE; ++i) printf("%d ", freq[i]); //printa o array de frequencia
	printf("\n\n");
	
	

	for(i = 0; i<MAX_SIZE; ++i)
	{
		if( freq[i] )
		{
			int *code = (int *) malloc(sizeof(int));
			*code = i;
			bt = enqueue(bt,code,freq[i]);
		}
	}

	printf("Creatting tree...\n");
	bt = queue_to_tree(bt);
	printf("Creatting dicionary...\n");
	dicionary = tree_to_table(bt);
	printf("Codding...\n");
	codding(new_arq,arq,dicionary,tamanho,bt);
	
	printf("Sucess! :)\n");
	
	


}
