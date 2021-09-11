#include<stdio.h>
#include<sys/shm.h>
#include<sys/stat.h>

int main()
{
	int segment_id;
	char* shared_memory;
	struct shmid_ds shmbuffer;
	int segment_size;
	const int shared_segment_size = 0x6400; // 25600 bytes en decimal
	
	//Reservar un segmento de memoria compartida
	segment_id = shmget(IPC_PRIVATE, shared_segment_size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	//Acopalar el segmento de memoria compartida
	shared_memory = (char*)shmat(segment_id, 0, 0);
	printf("shared memory attached at adress %p\n", shared_memory);
	//Determinar el tamanio del segmento
	shmctl(segment_id, IPC_STAT, &shmbuffer);
	segment_size = shmbuffer.shm_segsz;
	printf("segment size: %d\n", segment_size);
	//Escribe una cadena en el segmento de memoria compartida
	sprintf(shared_memory, "Hola, Mundo.");
	//Desacoplar el segmento de memoria compartida
	shmdt(shared_memory);
	
	
	//Reacoplar el segmento de memoria compartida en otra direcc.
	shared_memory = (char*)shmat(segment_id, (void*) 0x5000000, 0);
	printf("shared memory reattached at address %p\n", shared_memory);
	// Imprimir la cadena desde la memoria compartida
	printf("%s", shared_memory);
	// Desacoplar el segmento de memoria compartida
	shmdt(shared_memory);
	
	// Desreservar el segmento de memoria compartida
	shmctl(segment_id, IPC_RMID, 0);
	
	return 0;
}

