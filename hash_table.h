#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct _hash_table hash_table;
typedef struct NODE node;

//CRIA UMA HASH TABLE
hash_table* create_hash_table();

//INSERE UM NOVO ELEMENTO NA TABELA HASH
void put(hash_table *ht, void *key, void *value, int (*hash_function)(void *key), int (*equals)(void *key1, void *key2));

//BUSCA UM ELEMENTO NA TABELA HASH E RETORNA O SEU VALOR
void* get(hash_table *ht, void *key, int (*hash_function)(void *key), int (*equals)(void *key1, void *key2));



#endif