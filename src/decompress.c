#include "../inc/decompress.h"

#define DEBUG if(1)

// CONVERTE CARACTERE PARA BINÁRIO, SALVA EM STRING E ENTÃO RETORNA A STRING
unsigned char * get_bits(unsigned char a)
{
	unsigned char * bits;
	int b = (int) a; // CONVERTE O CARACTERE PARA DECIMAL

	int i;
	for (i = 7; i >= 0; i--)
	{
		// 0 OCUPA A POSIÇÃO 48 NA TABELA ASCII E 1 OCUPA A POSIÇÃO SEGUINTE
		bits[i] = (char) ((b%2) + 48); 
		b /= 2;
	}

	return bits;
}

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

// file = arquivo que está sendo manipulado atualmente
// new_file = arquivo que será gerado
void write_file(binary_tree * root, FILE *file, FILE *new_file)
{
	unsigned char * byte = (char *) malloc(sizeof(8*char));
	unsigned char c;

	binary_tree * bt = root;
	// i = INDICE DO ARRAY COM OS BITS PEGOS
	// can_get = VARIÁVEL QUE DIZ SE POSSO PEGAR UM NOVO CARACTERE E PERCORRE-LO
	int i = 0, can_get = 1;

	while ( (c = getc(file)) != EOF )
	{
		byte = get_bits(c);
		
		for (i = 0; i < 8; i++)
		{
			if (bt->right != NULL || bt->left != NULL)
			{
				if (byte[i] == 48)
				{
					bt = bt->left;
				}
				else 
				{
					bt = bt->right;
				}
			}
			else 
			{
				fprintf(new_file, "%c", bt->value);
				bt = root;
			}
		}
	}
}

void decompress(FILE *file)
{
	int trash, tree_size;
	binary_tree *bt = create_empty_binary_tree();
	hash_table *dicionary;
	FILE *new_file;
	char name[200];

	trash = get_trash(file);
	tree_size = get_size_tree(file);
	
	printf("Trash: %d\nTree_size: %d\n", trash, tree_size);

	printf("Digite o nome do arquivo de saida:\n");
	scanf("%s", name);

	new_file = fopen(name,"wb");

	bt = rebuild_tree(bt,file);

	//dicionary = tree_to_table(bt); //acho que vai ter que mudar isso
	
	//write_file(dicionary,file,new_file);
	/*
		Ate aqui ta funcionando, ja testei e comparei e deu certinho...
	*/
	write_file(bt, file, new_file);

}