#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compress.h"
#include "descompress.h"

int main(int argc, char const *argv[])
{
	FILE *arq;
	FILE *new_arq;
	char name[] = "TESTANDO";
	long int tam = 0;

	if(argc == 3)
	{
		if(argv[1][0] == 'c')
		{
			arq = fopen(argv[2],"rb");
			// strcpy(name,argv[2]);
			printf("NAME: %s\n", name);
			strcat(name,".huff");
			new_arq = fopen(name, "w");
			if(arq == NULL)
			{
				printf("Não foi possível abrir o arquvio\n");
				return 0;
			}
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
	}
	else
	{
		printf("Argumentos inválidos, ultilize o formato < c > < file >");
		return 0;
	}
	return 0;
}
