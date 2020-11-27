#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <assert.h>

int main(int argc, char** argv)
{
	assert(argc > 1);

	int n = argc - 1;
	int* fds = (int*) calloc(n, sizeof(int));
	assert(fds);
	
	for (int i = 0; i < n; ++i) 
	{
		fds[i] = open(argv[i + 1], O_NONBLOCK);
		assert(fds[i] != -1);
	}
	
	struct pollfd* pfds = (struct pollfd*) calloc(n, sizeof(struct pollfd));
	assert(pfds);
	
	for (int i = 0; i < n; ++i) 
	{
		pfds[i].fd = fds[i];
		pfds[i].events = POLLIN;
	}

	while(poll(pfds, n, -1) > 0)
	{
		for(int i = 0; i < n; ++i)
		{
			if(pfds[i].revents & POLLIN)
			{
				pfds[i].revents = 0;

				struct stat finfo;
				fstat(fds[i], &finfo);
				int size = finfo.st_size;

				char* buf = (char*) malloc(size);
				assert(read(fds[i], buf, size) != -1);
				assert(write(STDOUT_FILENO, buf, size) != -1);
				free(buf);
			}
		}
	}
	free(fds);
	free(pfds);
	return 0;
}
