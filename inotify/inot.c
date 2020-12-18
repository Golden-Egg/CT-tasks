#include <sys/inotify.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		perror("number of elts");
		return -1;
	}
	
	int mask = IN_CREATE | IN_DELETE | IN_MOVE_SELF;
	char buf[4096] = {};
	struct inotify_event* event;
	char* ptr;

	int fd = inotify_init();
	if(fd == -1)
	{
		perror("inotify_init");
		return -1;
	}

	int watch = inotify_add_watch(fd, argv[1], mask);
	if(watch == -1)
	{
		perror("inotify_add_watch");
		return -1;
	}

	while(1)
	{
		int ev = read(fd, buf, 4096);
		if(ev > 0)
		{
			for(ptr = buf; ptr < buf + ev; ptr += sizeof(struct inotify_event) + event->len)
			{
				event = (struct inotify_event*) ptr;
				
            			if (event->mask & IN_CREATE)
                			printf("Create %s\n", event->name);
            			if (event->mask & IN_DELETE)
                			printf("Delete %s\n", event->name);
           			if (event->mask & IN_MOVE_SELF)
                			printf("Moveself %s\n", argv[1]);
			}
		}
		else if(ev == 0)
		{
			break;
		}
		else
		{
			perror("read error");
			return -1;
		}
	}
	close(fd);
	return 0;
}
