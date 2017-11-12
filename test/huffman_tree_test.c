#include "CUnit/Basic.h"
#include "../inc/huffman_tree.h"
#include "../inc/hash_table.h"
#include "../inc/decompress.h"
#include <stdlib.h>

huffman_tree *tree = NULL;

//Adiciona nos a uma arvore 
int init_tree(){

	int i;
	tree = create_empty_huffman_tree();
	unsigned char *item;
	huffman_tree *new_node;

	for(i=1; i<=10; i++)
	{
		item = (unsigned char *) malloc(sizeof(unsigned char));
		*item = 64+i;
		new_node = create_huffman_tree(item, i, NULL, NULL, NULL);
		if(new_node != NULL) tree = enqueue(tree, new_node);

	}

	item = (unsigned char *) malloc(sizeof(unsigned char));
	*item = 'z';
	new_node = create_huffman_tree(item, 5, NULL, NULL, NULL);
	if(new_node != NULL) tree = enqueue(tree, new_node);

	item = (unsigned char *) malloc(sizeof(unsigned char));
	*item = '1';
	new_node = create_huffman_tree(item, 10000, NULL, NULL, NULL);
	if(new_node != NULL) tree = enqueue(tree, new_node);

	item = (unsigned char *) malloc(sizeof(unsigned char));
	*item = '~';
	new_node = create_huffman_tree(item, 9, NULL, NULL, NULL);
	if(new_node != NULL) tree = enqueue(tree, new_node);

	item = (unsigned char *) malloc(sizeof(unsigned char));
	*item = '*';
	new_node = create_huffman_tree(item, 2, NULL, NULL, NULL);
	if(new_node != NULL) tree = enqueue(tree, new_node);

	return 0;

}

void create_huffman_tree_test()
{
		unsigned char *item = (unsigned char *) malloc(sizeof(unsigned char));
		*item = 64;
		huffman_tree *new_node = create_huffman_tree(item, 5, NULL, NULL, NULL);
		
		if(new_node == NULL)
		{
			CU_FAIL("The tree is NULL");
		} else {
			CU_PASS("OK");		
		}
}

//Testa se o enfileiramento foi feito corretamente
void enqueue_test()
{
	int i;
	int count = 65;
	huffman_tree *current = tree;

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
	char expected[] = "*****CDG*H~**I**B*A\\*z*J*EF1";
	short int *tree_size = (short int *) malloc(sizeof(short int));

	tree = queue_to_tree(tree);
	unsigned char *string_tree = traversal_tree(tree, tree_size);

	if(string_tree == NULL){
		CU_FAIL("Tree, in pre order, is NULL");

	} else {

		int i;
		for(i=0; i<*tree_size; i++)
		{
			if(string_tree[i] != expected[i])
			{
				CU_FAIL("The tree generated is different than expected");
			}
		}
	}
	CU_PASS("OK");

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

	hash_table *ht = tree_to_table(tree);
	unsigned char *current;

	if(ht == NULL)
	{
		CU_FAIL("Hash table is NULL");

	} else {

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

	CU_PASS("OK");
}

void rebuild_tree_test()
{
	tree = create_empty_huffman_tree();
	FILE *file = fopen("file_test_tree.txt", "rw");
	getc(file);
	getc(file);

	tree = rebuild_tree(tree, file);

	short int *tree_size = (short int *) malloc(sizeof(short int));
	unsigned char *string_tree = traversal_tree(tree, tree_size);

	unsigned char expected[] = "****\\*\\*1a*\\*c";

	int i;
	for(i=0; i<*tree_size; i++)
	{
		if(string_tree[i] != expected[i])
		{
			CU_FAIL("The tree generated is different than expected");
		}
	}
	CU_PASS("OK");
}

void write_file_test()
{
	int file_size,i;
	unsigned char byte_expected,byte;
	FILE *expected = fopen("test_file.txt", "r");
	FILE *descompress = fopen("descompress.txt", "w+r");
	FILE *compressed = fopen("test_file.huff", "r");
	
	/*if(compressed == NULL);
	{ 
		CU_FAIL("the file compressed could not be opened");
	}
	if(descompress == NULL);
	{ 
		CU_FAIL("the new file  could not be creatted");
	}
	if(expected == NULL);
	{ 
		CU_FAIL("the file expected could not be opened");
	}
	*/


	int trash = get_trash(compressed);
	int tree_size = get_size_tree(compressed);
	huffman_tree *tree = rebuild_tree(tree, compressed);
	

	write_file(tree, compressed, descompress,trash);

	fseek(descompress, 0, SEEK_END);
	file_size = ftell(descompress);
	fseek(descompress, 0, SEEK_SET);

	for(i = 0; i < file_size; ++i)
	{
		//byte = getc(descompress);
		//byte_expected = getc(expected);
		if(getc(descompress) != getc(expected))
		{
			CU_FAIL("The file descompressed is different than expected");
		}
	}
	CU_PASS("OK");
			


}


int main()
{
	//Initialize CUnit test registry
	if(CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	CU_pSuite pSuite = NULL;

	//Add a suite to the registry
	pSuite = CU_add_suite("huffman_tree_test", init_tree, NULL);

	//Always check if add was successful
	if(pSuite == NULL)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(NULL == CU_add_test(pSuite, "create_huffman_tree_test", create_huffman_tree_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	//Add the test to the suite
	if(NULL == CU_add_test(pSuite, "add_in_huffman_tree", enqueue_test))
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

	if(NULL == CU_add_test(pSuite, "rebuild_tree_test", rebuild_tree_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if(NULL == CU_add_test(pSuite, "write_file_test", write_file_test ))
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