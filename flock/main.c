#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Wrong number of args\n");
		exit(-1);
	}

	int fd = open(argv[1], O_RDWR);
	if(fd < 0)
	{
		perror("Open error");
		exit(-1);
	}

	/*struct flock fl1 = {0};
        fl1.l_type = F_RDLCK;
        fl1.l_whence = SEEK_SET;
        fl1.l_len = 0;
	fl1.l_pid = 0;

        int ret = fcntl(fd, F_SETLK, &fl1);
        if(ret < 0)
        {
                perror("fcntl error");
                close(fd);
                exit(-1);
        }*/

	struct flock fl = {0};
	while(fcntl(fd, F_GETLK, &fl) >= 0)
	{
		printf("l_type: %d\tl_whence: %d\tl_start: %ld\tl_len: %ld\tl_pid: %d\n",fl.l_type, fl.l_whence, fl.l_start, fl.l_len, fl.l_pid);
	}

	close(fd);
	return 0;
}
