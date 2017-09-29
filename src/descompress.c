#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/binary_tree.h"
#include "../inc/hash_table.h"

#define MAX_SIZE 256
#define DEBUG if(1)

// CONVERTE CARACTERE PARA BINÁRIO, SALVA EM STRING E ENTÃO RETORNA A STRING
char * get_bits(unsigned char a, char * c)
{
	char * byte = c;
	int b = (int) a; // CONVERTE O CARACTERE PARA DECIMAL

	int i;
	for (i = 7; i >= 0; i--)
	{
		// 0 OCUPA A POSIÇÃO 48 NA TABELA ASCII E 1 OCUPA A POSIÇÃO SEGUINTE
		byte[i] = (char) ((b%2) + 48);
		b /= 2;
	}

	c = byte;

	return c;
}

/*
	INFORMAÇÕES DO CABEÇALHO
*/

// TAMANHO DO LIXO
int get_trash(char * byte)
{
	int trash = 0;
	
	int len = strlen(byte);
	int potencia = 0;
	
	int i;
	for (i = 2; i >= 0; i--)
	{
		if ((int) byte[i] == 49) 
		{
			trash += pow(2,potencia);
		}
		potencia++;
	}
	
	return trash;
}

// ÁRVORE DE CODIFICAÇÃO
int get_size_tree(char * byte)
{
	int size = 0;
	int potencia = 0;
	int i;
	for (i = 15; i > 2 ; i--)
	{
		if ((int) byte[i] == 49) 
		{
			size += pow(2,potencia);
		}
		potencia++;
	}

	return size;
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