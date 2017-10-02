#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>

typedef struct _hash_table hash_table;
typedef struct _node node;

// CRIA UMA HASH TABLE
hash_table* create_hash_table();

// DADOS A CHAVE, O VALOR E A FUNCAO DE DISPERSAO, INSERE UM NOVO ELEMENTO NA TABELA HASH
void put(hash_table *ht, void *key, void *value, int (*hash_function)(void *h_key));

// DADOS A CHAVE, A FUNCAO DE DISPERSAO E A FUNÇÃO DE COMPARAÇÃO, 
// BUSCA UM ELEMENTO NA TABELA HASH E RETORNA O SEU VALOR
void* get(hash_table *ht, void *key, int (*hash_function)(void *h_key), int (*equals)(void *key1, void *key2));

#endif