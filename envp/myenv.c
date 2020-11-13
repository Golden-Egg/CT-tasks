#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv)
{
	char** args = (char**) malloc(sizeof(char*));
	args[1] = argv[1];
	execve(argv[1], args, argv + 2);
}
