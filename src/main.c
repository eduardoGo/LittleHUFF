#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/compress.h"

int main(int argc, char const *argv[])
{
	FILE *arq;
	FILE *new_arq;
	char name[200];
	long int tam = 0;

	if(argc == 3)
	{
		if(argv[1][0] == 'c')
		{
			arq = fopen(argv[2],"rb");
			if(arq == NULL)
			{
				printf("Não foi possível abrir o arquvio\n");
				return 0;
			}
			printf("Digite o nome do arquivo de saída:\n");
			scanf("%s", name);
			strcat(name,".huff");
			new_arq = fopen(name, "wb");
			fseek(arq,0,SEEK_END);
			tam = ftell(arq);
			fseek(arq,0,SEEK_SET);
			printf("Arquivo com %li bytes!\n", tam);

			compress(new_arq,arq,tam);
		}
		else if(argv[1][0] == 'd')
		{
			arq = fopen(argv[2],"rb");
			printf("DSucess\n");
		}
		else
		{
			printf("Argumentos inválidos, ultilize o formato (< c > or < d >) < file >");
			return 0;
		}
	}
	else
	{
		printf("Argumentos inválidos, ultilize o formato (< c > or < d >) < file >");
		return 0;
	}
	return 0;
}
