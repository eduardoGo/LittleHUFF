
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int compara(void* key1,void* key2)
{
	return *((char*) key1) == *((char*) key2);
}

int hash_fuction(void *key)
{
	return *((int*) key);
}


char add_bit(unsigned char byte, int pos)
{
	unsigned char mask = 0;
	mask = 1 << (7 - pos);
	return mask | byte;
}

void set_header(FILE *new_arq,short int *tree_size, unsigned char trash)
{
	unsigned char byte = *tree_size >> 8;
	trash =  trash | byte;
	fprintf(new_arq, "%c", trash);
	byte = *tree_size;
	trash = byte & 255; //reaproveitando a variavel trash
	fprintf(new_arq, "%c", trash);
}


void set_tree(FILE *new_arq, char *tree, short int *size)
{
	int i = 0;
	for(i = 0; i < *size; ++i)
	{
	 	fprintf(new_arq,"%c", tree[i]);
	}
}


void codding(FILE *new_arq, FILE *arq, hash_table *dicionary,int size_arq,binary_tree *bt)
{
	int i,j,pos;
	unsigned char byte = 0,trash = 0;
	
	char *current,*tree;
	short int *tree_size = (short int *) malloc(1*sizeof(short int));
	
	fprintf(new_arq,"%c", byte);
	fprintf(new_arq,"%c", byte);

	tree = traversal_tree(bt,tree_size); //Ponteiro para uma string que contem a arvore em pre ordem

	printf("Size tree: %d\n", *tree_size);

	print_pre_order(bt);
	printf("\n");
	
	set_tree(new_arq,tree,tree_size); //Coloca a arvore em pre ordem no arquivo
	pos = j = i = 0;

	for(j = 0; j < size_arq; ++j)
	{
		//printf("< Rodando o arquivo no byte %d>\n", j);
		unsigned char *aux = (unsigned char*) malloc(1*sizeof(unsigned char));
		*aux = getc(arq);
		current = (unsigned char*) get(dicionary, aux, hash_fuction, compara);
		//printf("Caracter: %x codificacao a ser gravada: %s\n", *aux,current);
		while(current[i] != '\0')
		{
			if(pos == 8)
			{
				fprintf(new_arq,"%c", byte);
				//printf("Gravou byte: %x\n", byte);
				byte = 0;
				pos = 0;	
			}
			if(current[i] == '1') byte = add_bit(byte,pos);
			pos++;
			i++;
		}
		i = 0;
	}

	fprintf(new_arq, "%c", byte);
	fseek(new_arq,0,SEEK_SET);
	
	printf("Trash: %d\n", 8-pos);

	trash = (8-pos) << 5;
	set_header(new_arq,tree_size,trash);

	fseek(new_arq,0,SEEK_SET);

}



void compress(FILE *new_arq,FILE *arq, int tamanho)
{
	printf("Take frequency...\n");
	int *freq = frequency(arq,tamanho);
	int i;
	binary_tree *bt = create_empty_binary_tree();
	hash_table *dicionary;
	
	for(i = 0; i<MAX_SIZE; ++i)
	{
		if( freq[i] )
		{
			int *code = (int *) malloc(sizeof(int));
			*code = i;
			bt = enqueue(bt,
				create_binary_tree(code,freq[i],NULL,NULL,NULL));
		}
	}
	printf("Creatting tree...\n");
	bt = queue_to_tree(bt);
	printf("Creatting dicionary...\n");
	dicionary = tree_to_table(bt);
	printf("Codding...\n");
	codding(new_arq,arq,dicionary,tamanho,bt);
	
	printf("Sucess! :)\n");
	
	fclose(new_arq);
	fclose(arq);


}