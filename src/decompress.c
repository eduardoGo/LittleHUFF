#include "../inc/decompress.h"


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


void decompress(FILE *file, FILE *new_file)
{
	int trash, tree_size;
	huffman_tree *tree = create_empty_huffman_tree();

	trash = get_trash(file);
	tree_size = get_size_tree(file);
	
	tree = rebuild_tree(tree, file);
	printf("Wait...\n");
	write_file(tree, file, new_file,trash);
	printf("Finish!\n");
}