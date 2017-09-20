#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"
#include "compress.h"
#include "hash_table.h"

#define MAX_SIZE 256

char * get_binary(char byte)
{
	int a = byte;
	char b[8];
	itoa(a,b,2);

	return b;
}

int get_trash(char bytes[2])
{
	
}

binary_tree * get_tree();