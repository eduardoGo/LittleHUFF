OBJS = ../src/binary_tree.c ../src/hash_table.c binary_tree_test.c

DEPS = ../inc/binary_tree.h ../inc/hash_table.h

OBJS2 = ../src/binary_tree.c ../src/hash_table.c hash_table_test.c
compile:
	gcc -o bt_test $(OBJS) $(DEPS) -lcunit
	gcc -o ht_test $(OBJS2) $(DEPS) -lcunit