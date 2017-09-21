#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"
#include "hash_table.h"

#define MAX_SIZE 256
#define DEBUG if(1)

int get_trash(char byte[16])
{
	int trash = 0;
	int len = strlen(byte);
	
	if (len == 16)
	{
		if (byte[0] == 1) trash += 4;
		if (byte[1] == 1) trash += 2;
		if (byte[2] == 1) trash += 1;
	}
	else if (len == 15)
	{		
		if (byte[0] == 1) trash += 2;
		if (byte[1] == 1) trash += 1;
	}
	else if (len == 14)
	{
		if (byte[0] == 1) trash += 1;
	}
	
	return trash;
}

binary_tree * get_tree(char byte[16], char str[]);

void descompress(FILE * file, FILE * new_file)
{
	unsigned char c[2];
	char bits[16];
	int trash;
	
	fread(c, sizeof(unsigned char), 2, file);

	itoa((int) c[1], bits, 2);
	trash = get_trash(bits);

}
