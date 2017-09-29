#include "../inc/compress.h"

int* frequency(FILE *file, int size)
{
	int i;
	int *freq = (int*) calloc(MAX_SIZE, sizeof(int));

	for(i = 0; i < size; ++i)
	{
		freq[getc(file)]++;
	}
	fseek(file, 0, SEEK_SET);

	return freq;
}

int compare(void* key1,void* key2)
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

void set_header(FILE *new_file, short int tree_size, unsigned char trash)
{
	unsigned char byte = tree_size >> 8;
	trash = trash | byte;
	fprintf(new_file, "%c", trash);
	byte = tree_size;
	fprintf(new_file, "%c", byte);
}


void set_tree(FILE *new_file, unsigned char *tree, short int size)
{
	int i;
	for(i = 0; i < size; ++i)
	{
	 	fprintf(new_file,"%c", tree[i]);
	}
}


void codding(FILE *new_file, FILE *file, hash_table *dicionary, int file_size, binary_tree *bt)
{
	int i, j, pos;
	unsigned char byte = 0, trash = 0;
	
	unsigned char *current, *tree;

	fprintf(new_file,"%c", byte);
	fprintf(new_file,"%c", byte);

	short int *tree_size = (short int *) malloc(sizeof(short int));
	tree = traversal_tree(bt, tree_size); //Ponteiro para uma string que contem a arvore em pre ordem

	//REMOVER POSTERIORMENTE
	printf("Size tree: %d\n", *tree_size);
	print_pre_order(bt);
	printf("\n");
	
	set_tree(new_file, tree, *tree_size); //Coloca a arvore em pre ordem no arquivo
	pos = 0;

	for(j = 0; j < file_size; ++j)
	{
		unsigned char *aux = (unsigned char*) malloc(sizeof(unsigned char));
		*aux = getc(file);
		current = (unsigned char*) get(dicionary, aux, hash_fuction, compare);
		
		i = 0;
		while(current[i] != '\0')
		{
			if(pos >= 8)
			{
				fprintf(new_file,"%c", byte);
				byte = 0;
				pos = 0;	
			}

			if(current[i] == '1')
			{
				byte = add_bit(byte, pos);
			}

			pos++;
			i++;
		}
	}

	fprintf(new_file, "%c", byte);
	fseek(new_file, 0, SEEK_SET);
	
	//REMOVER POSTERIORMENTE
	printf("Trash: %d\n", 8-pos);
	printf("===================\n");

	trash = (8-pos) << 5;
	set_header(new_file, *tree_size, trash);
	free(tree_size);

	fseek(new_file, 0, SEEK_SET);

}

void compress(FILE *new_file, FILE *file, int file_size)
{
	int *freq = frequency(file, file_size);
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
				create_binary_tree(code, freq[i], NULL, NULL, NULL));
		}
	}

	bt = queue_to_tree(bt);
	
	dicionary = tree_to_table(bt);
	
	codding(new_file, file, dicionary, file_size, bt);
	
}