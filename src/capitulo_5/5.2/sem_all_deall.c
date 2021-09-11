#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include<stdio.h>

#define KEY 0x1111
/* We must define union semun ourselves.  */
union semun {
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};
/* Obtain a binary semaphore’s ID, allocating if necessary.  */
int binary_semaphore_allocation (key_t key, int sem_flags)
{
	return semget (key, 1, sem_flags);
}
/* Deallocate a binary semaphore.  All users must have finished their
use.  Returns -1 on failure.  */
int binary_semaphore_deallocate (int semid)
{
	union semun ignored_argument;
	return semctl (semid, 1, IPC_RMID, ignored_argument);
}

int main(int argc, char *arcv[])
{
	int semid = binary_semaphore_allocation(KEY, IPC_CREAT);
	
	printf("Valor de semid:%d\n", semid);
	
	binary_semaphore_deallocate(semid);
	
	printf("Semaforo binario desalojado\n");
	
	return 0;
}
