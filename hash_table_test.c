#include "hash_table.h"
#include "CUnit/CUnit.h"
#include <stdio.h>
#include <stdlib.h>

static FILE *temp_file = NULL;

int init_suite(void)
{
	if(NULL == (temp_file = fopen("temp.txt", w+)))
	{
		return -1;
	}
	else {
		return 0;
	}
}

int clean_suit(void)
{
	if( 0 != fclose(temp_file))
	{
		return -1;
	} else {
		temp_file = NULL;ni
		return 0;
	}
}

int hash_function(void *key)
{
	return *( (int*) key );
}

int equals(void *key1, void *key2)
{
	return ( *(int*) key1 ) == *( (int*) key2 );
}

int main(int argc, char const *argv[])
{

	CU_pSuite pSuite = NULL;

	// hash_table *ht = create_hash_table();

	// int *key = (int*) malloc(sizeof(int));
	 // *key = 64;
	// int *value = (int*) malloc(sizeof(int));
	// *value = *key;

	// if(get(ht, key, hash_function, equals) == NULL) printf(":)\n");

	// put(ht, key, value, hash_function, equals);

	// value = get(ht, key, hash_function, equals);

	// if(value != NULL) printf("%c\n", *value);

	return 0;
}