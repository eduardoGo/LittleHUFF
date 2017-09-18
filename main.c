#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	FILE *arq;
	char a[100];
	if(argc == 3)
	{
		if(argv[1][0] == 'c')
		{
			arq = fopen(argv[2],"rb");
			fgets(a,100,arq);
			printf("%s\n", a);
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
