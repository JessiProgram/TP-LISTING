#include <malloc.h>
#include <pthread.h>
#include <stdio.h>

/*Listing 4.10 ( job-queue1.c) Thread Function to Process Jobs from the Queue*/
/*Obs.1: La finalidad de este programa es el de simular un conjunto de hilos
        realizando tareas de una cola  en diferentes hilos. Se busca simular
        condiciones de carrera en hilos.*/
/*Obs.2:    Se agrega el main de ejecucion y los trabajos a realizarse en la cola
            de trabajos.*/

long long global_integer = 0;
int repeticiones = 999; //Cantidad de veces que cada job busca adicionar +1 a la variable global_integer.
int nro_jobs = 100; //Nro de jobs a generar y encolar.

/*Funcion que incrementa una variable global.*/
void aumentar() {
    for (int i = 0; i < repeticiones; i++)
    {
        global_integer++;
    }
}

struct job {
    /* Link field for linked list.*/
    struct job* next;

    /* Other fields describing work to be done... */
    void (*aumentarUno)(struct job*);
};


void process_job(struct job* aux) 
{
    aux->aumentarUno(aux);
}

/* A linked list of pending jobs.*/
struct job* job_queue;

/* Process queued jobs until the queue is empty.*/

void* thread_function (void* arg)
{
    while (job_queue != NULL) {

        /* Get the next available job. */
        struct job* next_job = job_queue;

        /* Remove this job from the list. */
        job_queue = (job_queue)->next;

        /* Carry out the work. */
        process_job (next_job);
        /* Clean up. */
        free (next_job);
    }

    return NULL;
}

/*Agrega un nodo nuevo luego del nodo "nodo" recibido de parametro*/
void add(struct job** nodo, void* funcion) {
    struct job* nuevo = (struct job*)malloc(sizeof(struct job));
    struct job* actual = *nodo;
    nuevo->aumentarUno = funcion;
    nuevo->next = NULL;

    if (*nodo == NULL) {
        *nodo = nuevo;
        return;
    }

    while(actual->next != NULL) {
        actual = actual->next;
    }
    actual->next = nuevo;
}

int main(int argc, char const *argv[])
{

    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;
    long long cantidad_esperada = repeticiones*nro_jobs;
    printf("--------------------------------------------------------------------------\n");
    printf( "Los procesos a realizarse en la cola de trabajos es incrementar una \n"
            "variable %d (nro_jobs)* %d (repeticiones func. aumentar) veces = %lld.\n"
            "Si ocurrio una condicion de carrera, el resultado final sera un nro.\n"
            "diferente a %lld\n", nro_jobs, repeticiones, cantidad_esperada, cantidad_esperada);
    printf("--------------------------------------------------------------------------\n");
    printf("--------------------------------------------------------------------------\n");
    printf( "Un motivo que genera las condiciones de carrera en este programa es cuando un hilo\n" 
            "accede a la funcion que adiciona con el valor X, y antes de que pueda guardar el\n"
            "valor X+1, otro hilo modifica el valor en memoria a algun valor Y\n"
            "(puede ser X+1, etc.). Luego, cuando el 1er hilo guarde X+1 en la memoria, el\n"
            "valor anterior en memoria ya no era X, ocasionando que el conteo sea incorrecto.\n"
            "Si esto ocurre, el resultado final no sera el esperado.\n");
    printf("--------------------------------------------------------------------------\n");
    printf( "La otra clase de condiciones de carrera que pueden ocurrir en este programa\n"
            "ocurren cuando los hilos buscan acceder a la cola de trabajos, y terminen\n"
            "accediendo al mismo trabajo.\n");
    printf("--------------------------------------------------------------------------\n");
    printf( "Obs.:  En algunas ejecuciones, el programa termina en medio de la ejecucion\n"
            "por los problemas que se generan en las repetidas race conditions.\n"
            "        Esto ocurre en cuando dos hilos acceden al mismo job casi al mismo\n"
            "tiempo, y uno de ellos elimina el job, provocando que el ->next en el otro\n"
            "hilo produzca un error de segmentacion.\n"
            "Se recomienda que si eso ocurre, se vuelva a probar el programa nuevamente.\n");
    printf("--------------------------------------------------------------------------\n");
    printf("--------------------------------------------------------------------------\n");
    /*Creamos y encolamos jobs (cantidad nro_jobs)*/
    job_queue = NULL;
    for (int i = 0; i < nro_jobs; i++)
    {
        add(&job_queue, aumentar);
    }
    
    pthread_create(&thread1, NULL, &thread_function, NULL);    
    pthread_create(&thread2, NULL, &thread_function, NULL);    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Resultado esperado: %lld\n", cantidad_esperada);
    printf("Resultado final: %lld\n", global_integer);
    return 0;
}
