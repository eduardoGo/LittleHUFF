#include "CUnit/Basic.h"
#include "../inc/binary_tree.h"
#include "../inc/hash_table.h"
#include <stdlib.h>

binary_tree *bt = NULL;

//Adiciona nos a uma arvore 
int init_bt(){

	int i;
	bt = create_empty_binary_tree();
	unsigned char *item;
	binary_tree *new_node;

	for(i=1; i<=10; i++)
	{
		item = (unsigned char *) malloc(sizeof(unsigned char));
		*item = 64+i;
		new_node = create_binary_tree(item, i, NULL, NULL, NULL);
		bt = enqueue(bt, new_node);

	}

	item = (unsigned char *) malloc(sizeof(unsigned char));
	*item = 'z';
	new_node = create_binary_tree(item, 5, NULL, NULL, NULL);
	bt = enqueue(bt, new_node);

	item = (unsigned char *) malloc(sizeof(unsigned char));
	*item = '1';
	new_node = create_binary_tree(item, 10000, NULL, NULL, NULL);
	bt = enqueue(bt, new_node);

	item = (unsigned char *) malloc(sizeof(unsigned char));
	*item = '~';
	new_node = create_binary_tree(item, 9, NULL, NULL, NULL);
	bt = enqueue(bt, new_node);

	item = (unsigned char *) malloc(sizeof(unsigned char));
	*item = '*';
	new_node = create_binary_tree(item, 2, NULL, NULL, NULL);
	bt = enqueue(bt, new_node);

	return 0;

}

//Testa se o enfileiramento foi feito corretamente
void enqueue_test()
{
	int i;
	int count = 65;
	binary_tree *current = bt;

	for(i=1; i<=14; i++){

		if(i == 2)
		{
			CU_ASSERT_EQUAL( get_item(current), 42);
		}
		else if(i == 6)
		{
			CU_ASSERT_EQUAL( get_item(current) , 122);
		}
		else if(i == 11)
		{
			CU_ASSERT_EQUAL( get_item(current) , 126);
		}
		else if(i == 14)
		{
			CU_ASSERT_EQUAL( get_item(current), 49);
		}
		else {
			CU_ASSERT_EQUAL( get_item(current), count);
			count++;
		}
	
		current = get_next(current);
	}
}

//Testa se a transformacao da fila em arvore binaria esta correta
void queue_to_tree_test()
{
	char expected[] = "*****CDG*H~**I**B*A\\*z*J*EF1\0";
	bt = queue_to_tree(bt);

	CU_ASSERT_EQUAL(strcmp(traversal_tree(bt), expected), 0);

}

//funcoes de dispersao e equivalencia passadas como parametro
int hash_func(void *key)
{
	return *((unsigned char *) key);
}

int equals(void *key1, void *key2)
{
	return *((unsigned char *) key1) = *((unsigned char*) key2);
}

//PROBLEMA NA INSERÇÃO NA HASH TABLE, HASH_FUNC PEGA NUM MUITO ALTO E DÁ SF
void tree_to_table_test()
{

	int i;
	unsigned char keys[] = "CDGH~IBA*zJEF1";
	unsigned char codes[][8]= {
		"00000\0", "00001\0", "0001\0", "0010\0", "0011\0",
		"0100\0", "010100\0", "0101010\0", "0101011\0", "01011\0",
		"0110\0", "01110\0", "01111\0", "1\0"
	};

	hash_table *ht = tree_to_table(bt);
	unsigned char *current;

	for(i=0; i<14; i++)
	{
		current = (unsigned char*) get(ht, &keys[i], hash_func, equals);
		
		if(current != NULL){
			CU_ASSERT_EQUAL(strcmp(current, codes[i]), 0);
		} else {
			CU_FAIL("There are elements that were not entered in the hash table")
		}
	}
}

int main()
{
	//Initialize CUnit test registry
	if(CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	CU_pSuite pSuite = NULL;

	//Add a suite to the registry
	pSuite = CU_add_suite("binary_tree_test", init_bt, NULL);

	//Always check if add was successful
	if(pSuite == NULL)
	{
		CU_cleanup_registry();
		return CU_get_error();
	} 

	//Add the test to the suite
	if(NULL == CU_add_test(pSuite, "create_and_add_in_binary_tree", enqueue_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "turn_queue_to_tree", queue_to_tree_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "turn_tree_to_table", tree_to_table_test))
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