#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv, char** envp)
{
	for (int i = 0; envp[i]; i++)
	{
		printf("%s\n", envp[i]);
	} 
}
