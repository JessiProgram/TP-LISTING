#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <sys/stat.h>

#define KEY 0x1111

/* We must define union semun ourselves.  */
union semun {
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

// Usamos parte del listing 5.2 para este codigo
/* Deallocate a binary semaphore.  All users must have finished their
use.  Returns -1 on failure.  */
int binary_semaphore_deallocate (int semid)
{
	union semun ignored_argument;
	return semctl (semid, 1, IPC_RMID, ignored_argument);
}

/* Initialize a binary semaphore with a value of 1.  */
int binary_semaphore_initialize (int semid)
{
	union semun argument;
	unsigned short values[1];
	values[0] = 1;
	argument.array = values;
	return semctl (semid, 0, SETALL, argument);
}


int main (int argc, char* argv[])
{
	// Primero debemos alojar espacio para el semaforo 
	int id_semaforo = semget(KEY, 1, IPC_CREAT | S_IWUSR | S_IRUSR);
	
	printf("Valor del id del semaforo: %d\n", id_semaforo);
	
	int valor_semaforo = binary_semaphore_initialize(id_semaforo);
	
	printf("Valor retornado por la funcion semctl: %d\n", valor_semaforo);
	printf("Este valor significa que se inicializo exitosamente el semaforo\n");
	
	int estado = binary_semaphore_deallocate(id_semaforo);
	
	printf("Semaforo binario desalojado\n");
	
	return 0;
}


