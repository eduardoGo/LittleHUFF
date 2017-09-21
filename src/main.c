#include <stdio.h>
#include <stdlib.h>
#include "compress.c" //dps tem que mudar isso

int main(int argc, char const *argv[])
{
	FILE *arq;
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
			fseek(arq,0,SEEK_END);
			tam = ftell(arq);
			fseek(arq,0,SEEK_SET);
			printf("Arquivo com %li bytes!\n", tam);
			compress(arq,tam);
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
