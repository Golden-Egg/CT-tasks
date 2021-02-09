#include "server.h"


int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Wrong number of params");
		return 0;
	}

    	struct sockaddr_un name = {0};
    	int sk, ret;
    	
	sk = socket(AF_UNIX, SOCK_STREAM, 0);
    	if (sk < 0)
    	{
        	perror("socket error");
        	return 1;
    	}

    	name.sun_family = AF_UNIX;
    	strncpy(name.sun_path, PATH, sizeof(PATH));
    	
	ret = connect(sk, (struct sockaddr*)&name, sizeof(name));
    	if (ret < 0)
    	{
        	perror("connect error");
        	close(sk);
        	return 1;
    	}
    	
	ret = write(sk, argv[1], strlen(argv[1]));
	if (ret < 0)
    	{
        	perror("write error");
        	return 1;
    	}
    	return 0;
}
