OBJS = ../src/huffman_tree.c ../src/hash_table.c huffman_tree_test.c

DEPS = ../inc/huffman_tree.h ../inc/hash_table.h

OBJS2 = ../src/huffman_tree.c ../src/hash_table.c hash_table_test.c
compile:
	gcc -o tree_test $(OBJS) $(DEPS) -lcunit
	gcc -o ht_test $(OBJS2) $(DEPS) -lcunit