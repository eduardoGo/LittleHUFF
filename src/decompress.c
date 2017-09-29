#include "../inc/decompress.h"

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
	return byte >> 5;
}

// ÁRVORE DE CODIFICAÇÃO
int get_size_tree(FILE *file)
{
	fseek(file, 0, SEEK_SET);

	unsigned char byte = getc(file);
	short int size = 0;

	byte = byte << 3;
	byte = byte >> 3;

	size = byte;
	size = size << 8;
	byte = getc(file);
	size = byte | size;

	return size;
}

void write_file(hash_table *dicionary, FILE *file, FILE *new_file)
{
	unsigned char byte;

	while( ( byte = getc(file) ) != EOF)
	{
		

	}
}

void decompress(FILE *file)
{
	int trash, tree_size;
	binary_tree *bt = create_empty_binary_tree();
	hash_table *dicionary;
	FILE *new_file;
	char name[200];

	//fread(c, sizeof(unsigned char), 2, file);

	trash = get_trash(file);
	tree_size = get_size_tree(file);
	
	printf("Trash: %d\tree_size: %d\n", trash,tree_size);

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