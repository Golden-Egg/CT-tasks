#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <assert.h>

int main(int argc, char** argv)
{
	int in = open(argv[1], O_RDONLY);
	assert(in > -1);

	struct stat finfo;
	assert(fstat(in, &finfo) > -1);

	int size = finfo.st_size;

	mkfifo("/home/liv/Рабочий стол/liv/semafor/mk", 0666);
	int fifo = open("/home/liv/Рабочий стол/liv/semafor/mk", O_WRONLY);
	assert(fifo > -1);

	write(fifo, &size, sizeof(int));
	close(fifo);
	
	int key = 11;

	int id = semget(key, 1, IPC_CREAT | 0666);
	assert(id > -1);

	int mid = shmget(key, size * sizeof(char), IPC_CREAT | IPC_EXCL | 0666);
	assert(mid > -1);

	void* mem = shmat(mid, NULL, 0);

	struct sembuf op = {0, 1, 0};
	int i = 0;
	read(in, mem, size * sizeof(char));

	assert(semop(id, &op, 1) > -1);

	shmdt(mem);
	//shmctl(mid, IPC_RMID, NULL);
	//semctl(id, 0, IPC_RMID);
	close(in);
	return 0;
}

