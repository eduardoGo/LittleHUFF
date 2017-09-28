#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/binary_tree.h"
#include "../inc/hash_table.h"

#define MAX_SIZE 256
#define DEBUG if(1)

// CONVERTE CARACTERE PARA BINÁRIO, SALVA EM STRING E ENTÃO RETORNA A STRING

/*
	INFORMAÇÕES DO CABEÇALHO|
*/

// TAMANHO DO LIXO
int get_trash(FILE *arquivo)
{
	unsigned char byte;
	byte = getc(arquivo);
	byte = byte >> 5;
	byte = byte & 255;
	return byte;
}

// ÁRVORE DE CODIFICAÇÃO
int get_size_tree(FILE *arquivo)
{
	fseek(arquivo,0,SEEK_SET);
	unsigned char byte;
	short int tam = 0;
	byte = getc(arquivo);
	byte = byte << 3;
	byte = byte >> 3;
	tam = byte;
	tam = tam << 8;
	byte = getc(arquivo);
	tam = byte | tam;
	return tam;
}

void write_file(hash_table *dicionary, FILE *file, FILE *new_file)
{
	unsigned char byte;

	while(byte = getc(file) != EOF)
	{
		

	}
}

void descompress(FILE *file)
{
	int trash,size_tree;
	binary_tree *bt = create_empty_binary_tree();
	hash_table *dicionary;
	FILE *new_file;
	char name[200];

	//fread(c, sizeof(unsigned char), 2, file);

	trash = get_trash(file);
	size_tree = get_size_tree(file);
	
	printf("Trash: %d\nsize_tree: %d\n", trash,size_tree);

	printf("Digite o nome do arquivo de saida:\n");
	scanf("%s", name);

	new_file = fopen(name,"wb");

	bt = rebuild_tree(bt,file);
	//dicionary = tree_to_table(bt); //acho que vai ter que mudar isso
	
	//write_file(dicionary,file,new_file);
	/*
		Ate aqui ta funcionando, ja testei e comparei e deu certinho...
	*/

}