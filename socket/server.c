#include "server.h"

#define STR "La-la-la-la-\nLa vida sola vi-viviras!\nLa vida sola vi-viviras!\n"
#define STR2 "La vida sola vi-viviras!\nJustice! Justice! La vi-vivida!\n"

int main()
{
	int sk, ret;
	struct sockaddr_un name = {0};
	
	sk = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sk < 0)
	{
        	perror("socket error");
        	return 1;
    	}

    	name.sun_family = AF_UNIX;
    	strncpy(name.sun_path, PATH, sizeof(PATH));

    	ret = bind(sk, (struct sockaddr*)&name, sizeof(name));
    	if(ret < 0)
    	{
        	perror("bind error");
        	close(sk);
        	return 1;
    	}

    	ret = listen(sk, 20);
    	if(ret)
    	{
        	perror("listen error");
        	close(sk);
        	return 1;
    	}

    	while(1)
    	{
        	int client;
        	
        	client = accept(sk, NULL, NULL);
        	if(client < 0)
        	{
            		perror("accept error");
            		exit(1);
        	}

		char buffer[BUFSZ] = {0};
		
        	ret = read(client, buffer, BUFSZ);
        	if (ret < 0 || ret > BUFSZ)
        	{
            		perror("read error");
            		return 1;
        	}
        	close(client);

        	if(strcmp(buffer, "PRINT") == 0)
      		{
			printf(STR);
			printf(STR2);
		}

        	if(strcmp(buffer, "EXIT") == 0)
            	{
			printf("Exit\n");
			break;
		}
    	}

    	unlink(PATH);
}
