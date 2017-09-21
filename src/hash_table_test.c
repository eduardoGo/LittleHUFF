#include "hash_table.h"
#include "CUnit/CUnit.h"
#include <stdio.h>
#include <stdlib.h>



int hash_function(void *key)
{
	return *( (int*) key );
}

int equals(void *key1, void *key2)
{
	return ( *(int*) key1 ) == *( (int*) key2 );
}

void test(void){
	CU_ASSERT(1 == 1);
}

int main(int argc, char const *argv[])
{

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