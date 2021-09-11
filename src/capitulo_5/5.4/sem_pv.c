#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <stdio.h>
#define KEY 0x1111

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

/* Wait on a binary semaphore.  Block until the semaphore value is positive, then   
decrement it by 1.  */
int binary_semaphore_wait (int semid)
{
	struct sembuf operations[1];
	/* Use the first (and only) semaphore.  */
	operations[0].sem_num = 0;
	/* Decrement by 1.  */
	operations[0].sem_op = -1;
	/* Permit undo’ing.  */
	operations[0].sem_flg = SEM_UNDO;
	return semop (semid, operations, 1);
}
/* Post to a binary semaphore: increment its value by 1. 
This returns immediately.  */
int binary_semaphore_post (int semid)
{
	struct sembuf operations[1];
	/* Use the first (and only) semaphore.  */
	operations[0].sem_num = 0;
	/* Increment by 1.  */
	operations[0].sem_op = 1;
	/* Permit undo’ing.  */
	operations[0].sem_flg = SEM_UNDO;
	return semop (semid, operations, 1);
}

// Usamos parte del listing 5.3 para este codigo
int binary_semaphore_initialize (int semid)
{
	union semun argument;
	unsigned short values[1];
	values[0] = 1;
	argument.array = values;
	return semctl (semid, 0, SETALL, argument);
}

int main(int argc, char*argv[])
{
	int semid = semget(KEY, 1, IPC_CREAT | S_IWUSR | S_IRUSR);
	
	int valor_semaforo = binary_semaphore_initialize(semid);
	
	int valor_retorno = binary_semaphore_post(semid);
	
	printf("Valor del semaforo: %d\n", valor_semaforo);
	
	return 0;
}



