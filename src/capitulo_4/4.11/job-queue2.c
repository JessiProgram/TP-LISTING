#include <malloc.h>
#include <pthread.h>
#include <stdio.h>

/*Listing 4.11 ( job-queue2.c) Job Queue Thread Function, Protected by a Mutex*/
/*Obs.1:    Este programa tiene la misma implementacion que el listing 4.10, pero 
            se evitan las condiciones de carrera con el uso de un Mutex.*/
/*Obs.2:    Se agrega el main de ejecucion y los trabajos a realizarse en la cola
            de trabajos.*/

long long global_integer = 0;
int repeticiones = 999; //Cantidad de veces que cada job busca adicionar +1 a la variable global_integer.
int nro_jobs = 100; //Nro de jobs a generar y encolar.

/* A mutex protecting job_queue. */
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

/*Funcion que incrementa una variable global.*/
void aumentar() {
    pthread_mutex_lock (&job_queue_mutex);
    for (int i = 0; i < repeticiones; i++)
    {
        global_integer++;
    }
    pthread_mutex_unlock (&job_queue_mutex);
}


struct job {
    /* Link field for linked list.*/
    struct job* next;

    /* Other fields describing work to be done... */
    void (*aumentarUno)(struct job*);
};

/* A linked list of pending jobs.*/
struct job* job_queue;

void process_job(struct job* aux) 
{
    aux->aumentarUno(aux);
}



/* Process queued jobs until the queue is empty.
Synchronization and Critical Sections
*/
void* thread_function (void* arg)
{
    while (1) {
        struct job* next_job;
        
        /* Lock the mutex on the job queue. */
        pthread_mutex_lock (&job_queue_mutex);
        
        /* Now it’s safe to check if the queue is empty. */
        if (job_queue == NULL) {
            next_job = NULL;
        } else {

            /* Get the next available job. */
            next_job = job_queue;
            
            /* Remove this job from the list. */
            job_queue = job_queue->next;
        }

        /* Unlock the mutex on the job queue because we’re done with the
        queue for now. */
        pthread_mutex_unlock (&job_queue_mutex);

        /* Was the queue empty?*/
        if (next_job == NULL) {
            break;
            /*If so, end the thread.*/
        }

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
    long long cantidad_esperada = repeticiones*nro_jobs;
    printf("--------------------------------------------------------------------------\n");
    printf("--------------------------------------------------------------------------\n");
    printf( "Los procesos a realizarse en la cola de trabajos es incrementar una \n"
            "variable %d (nro_jobs)* %d (repeticiones func. aumentar) veces = %lld.\n"
            "Si ocurrio una condicion de carrera, el resultado final sera un nro.\n"
            "diferente a %lld\n", nro_jobs, repeticiones, cantidad_esperada, cantidad_esperada);
    printf("--------------------------------------------------------------------------\n");
    printf( "Obs.: Las condiciones de carrera que ocurrian en el listing anterior\n"
            "se evitan en este programa mediante el uso de Mutexs.\n"
            "Tanto los problemas en el manejo de las colas y la asignacion de los\n"
            "jobs a realizar por cada hilo, como en el for que aumentaba la variable\n"
            "global_integer++, fueron solucionados con el uso de Mutexs en cada\n"
            "seccion. Es por ello, que el valor esperado y el resultado final son\n"
            "iguales al finalizar el programa.\n");
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
