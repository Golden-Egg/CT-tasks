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
#include <time.h>

int main(int argc, char** argv)
{
	assert(argc == 2);

	int size = 0;
        int out = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	assert(out > -1);

        int key = 11;

	int fifo = open("/home/liv/Рабочий стол/liv/semafor/mk", O_RDONLY);
	assert(fifo > -1);

	read(fifo, &size, sizeof(int));
	close(fifo);

	sleep(1);
        int mid = shmget(key, size * sizeof(char) , 0);
	assert(mid > -1);

        void* mem = shmat(mid, NULL, 0);

	int id = semget(key, 1, 0);
	assert(id > -1);

        struct sembuf op = {0, -1, 0};
	assert(semop(id, &op, 1) > -1);

        write(out, mem, size * sizeof(char));

	shmdt(mem);
	shmctl(mid, IPC_RMID, NULL);
        semctl(id, 0, IPC_RMID);
        close(out);
        return 0;
}

