#include "../inc/hash_table.h"
#include "CUnit/Basic.h"
#include <string.h>

hash_table *ht = NULL;

//funcoes de dispersao e equivalencia passadas como parametro

int hash_func(void *key)
{
	return *((unsigned char *) key);
}

int equals(void *key1, void *key2)
{
	return *((unsigned char *) key1) == *((unsigned char*) key2);
}

//Insere na hash table
void put_test(unsigned char key, unsigned char *code){
	
	unsigned char *value = (unsigned char *) malloc(10 * sizeof(unsigned char));
	strcpy(value, code);

	unsigned char *item = (unsigned char *) malloc(sizeof(unsigned char));
	*item = key;

	put(ht, item, value, hash_func);
}

//Testa se o retorno do get é o esperado
void get_test(unsigned char key, unsigned char *expected ){

	unsigned char *result = (unsigned char *) get(ht, &key, hash_func, equals);
	
	if(result != NULL && expected != NULL){
		CU_ASSERT_EQUAL(strcmp(result, expected), 0);
	} else {
		CU_ASSERT_EQUAL(result, expected);
	}

}

//Conjunto de inserções e buscas na hash table
void hash_table_test()
{

	ht = create_hash_table();

	unsigned char i;
	for(i=0; i<128; i++){
		get_test(i, NULL);
		get_test(i+128, NULL);
		put_test(i, "000\0");
		get_test(i, "000\0");
		get_test(i+128, NULL);
		put_test(i+128, "010\0");
		get_test(i+128, "010\0");
	}

}

int main()
{
	//Initialize CUnit test registry
	if(CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	CU_pSuite pSuite = NULL;

	//Add a suite to the registry
	pSuite = CU_add_suite("hash_table_test", NULL, NULL);

	//Always check if add was successful
	if(pSuite == NULL)
	{
		CU_cleanup_registry();
		return CU_get_error();
	} 

	//Add the test to the suite
	if(NULL == CU_add_test(pSuite, "put_and_get_in_hash_table", hash_table_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	// Sets the basic run mode, CU_BRM will show maximum output of run details
	// Other choices are: CU_BRM_SILENT and CU_BRM_NORMAL
	CU_basic_set_mode(CU_BRM_VERBOSE);

	//Run the tests and show the run sumary
	CU_basic_run_tests();

	return CU_get_error();
}