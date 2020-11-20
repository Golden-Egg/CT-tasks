#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Incorret number of elts\n");
		exit(-1);
	}
	else
	{
		char* path = argv[1];
		DIR* dir = opendir(path);
		if(dir == NULL)
		{
			printf("Opendir error\n");
			exit(-1);
		}
		struct dirent* file = NULL;
		while(file = readdir(dir))
		{
			printf("%s\n", file->d_name);
		}

	}
	return 0;
}
