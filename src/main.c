#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/compress.h"
#include "../inc/decompress.h"

void print_help()
{
	printf("Usage : ./huffman [options] [source_filename_path] [destination_filename_path]\n\n");
	printf("Options:\n");
	printf("-c : Compress the source file to destination file\n");
	printf("-d : Decompress the source file to destination file\n");
}

int main(int argc, char const *argv[])
{
	FILE *file;
	FILE *new_file;
	char name[200];
	long int file_size = 0;

	if(argc == 4)
	{
		if(argv[1][1] == 'c')
		{
			file = fopen(argv[2],"rb");

			if(file == NULL)
			{
				printf("the file could not be opened\n");
				return 0;
			}
			strcpy(name,argv[3]);
			strcat(name,".huff");
			new_file = fopen(name, "wb");
			fseek(file, 0, SEEK_END);
			file_size = ftell(file);
			fseek(file, 0, SEEK_SET);
			
			//REMOVER POSTERIORMENTE
			printf("=======================\n");
			printf("Arquivo com %li bytes!\n", file_size);

			compress(new_file, file, file_size);

			fclose(new_file);
			fclose(file);
		}
		else if(argv[1][1] == 'd')
		{
			file = fopen(argv[2],"rb");

			if(file == NULL)
			{
				printf("the file could not be opened\n");
				return 0;
			}
			strcpy(name,argv[3]);
			new_file = fopen(name,"wb");
			decompress(file,new_file);
			fclose(new_file);
			fclose(file);
		}
		else
		{
			print_help();
		}
	}
	else
	{
		print_help();
	}

	return 0;
}
