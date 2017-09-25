OBJS = src/binary_tree.c src/hash_table.c src/compress.c src/main.c

DEPS = inc/binary_tree.h inc/hash_table.h inc/compress.h

compile:
	gcc $(OBJS) $(DEPS) -o huffman
