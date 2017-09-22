#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/binary_tree.h"
#include "../inc/hash_table.h"

#define MAX_SIZE 256
#define DEBUG if(1)

// CONVERTE CARACTERE PARA BINÁRIO, SALVA EM STRING E ENTÃO RETORNA A STRING
char * get_bits(char a)
{
	char bits[8];
	int b = (int) a; // CONVERTE O CARACTERE PARA DECIMAL

	int i;
	for (i = 7; i >= 0; i--)
	{
		// 0 OCUPA A POSIÇÃO 48 NA TABELA ASCII E 1 OCUPA A POSIÇÃO SEGUINTE
		bits[i] = (char) ((b%2) + 48); 
	}

	return bits;
}

/*
	INFORMAÇÕES DO CABEÇALHO
*/

// TAMANHO DO LIXO
int get_trash(char byte[8])
{
	int trash = 0;
	int len = strlen(byte);
	
	int i;
	for (i = 2; i >= 0; i--)
	{
		if (byte[i] == '1') trash += pow(2,i);
	}
	
	return trash;
}

// ÁRVORE DE CODIFICAÇÃO
int get_size_tree(char byte[16])
{
	int size = 0;
	int i;
	for (i = sizeof(byte); i > (16-) ; i--)
	{
		if ()
	}
}

void descompress(FILE * file, FILE * new_file)
{
	unsigned char c[2];
	char bits[8];
	int trash;
	
	fread(c, sizeof(unsigned char), 2, file);

	bits = get_bits(c[0]);
	trash = get_trash(bits);

}