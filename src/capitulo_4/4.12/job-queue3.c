#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>


/*Listing 4.12 ( job-queue3.c) Job Queue Controlled by a Semaphore*/
/*Obs.: Este programa resuelve el problema de los race conditions
        que se tienen en el listing 4.9, utilizando semáforos.*/


long long global_integer = 0;
int repeticiones = 100; //Cantidad de veces que cada job busca adicionar a la variable global_integer.
int nro_jobs = 100; //Nro de jobs a generar y encolar en cada ciclo del hilo3.

pthread_t thread1; //Hilo que va a procesar los jobs.
pthread_t thread2; //Hilos que va a procesar los jobs.
pthread_t thread3; //Hilo que va a agregar más jobs a la cola de trabajos.
time_t inicio;

/* A mutex protecting job_queue. */
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

/*A mutex protecting in thread_function2.*/
pthread_mutex_t thread_function2_mutex = PTHREAD_MUTEX_INITIALIZER;

/*A mutex protecting the addition in function aumentar.*/
pthread_mutex_t aumentar_mutex = PTHREAD_MUTEX_INITIALIZER;

/* A semaphore counting the number of jobs in the queue.*/
sem_t job_queue_count;

/* A linked list of pending jobs.*/
struct job* job_queue;

/*Funcion que incrementa una variable global.*/
void aumentar(struct job* b, intptr_t sumando) {
        
    for (int i = 0; i < repeticiones; i++)
    {
        pthread_mutex_lock (&aumentar_mutex);
        global_integer += sumando;
        pthread_mutex_unlock (&aumentar_mutex);
    }
    
}


struct job {
    /* Link field for linked list.*/
    struct job* next;

    /* Other fields describing work to be done... */
    void (*aumentarUno)(struct job*, intptr_t);
};

void process_job(struct job* aux, intptr_t sumando) 
{
    aux->aumentarUno(aux, sumando);
}

/* Perform one-time initialization of the job queue.*/

void initialize_job_queue ()
{
    /* The queue is initially empty. */
    job_queue = NULL;

    /* Initialize the semaphore which counts jobs in the queue.
    Its initial value should be zero.*/
    sem_init (&job_queue_count, 0, 0);
}

/* Process queued jobs until the queue is empty.*/
void* thread_function (void* arg)
{
    intptr_t sumando = (intptr_t) arg;
    while (1) {

        struct job* next_job;
        /* Wait on the job queue semaphore. If its value is positive,
        indicating that the queue is not empty, decrement the count by
        1. If the queue is empty, block until a new job is enqueued. */
        sem_wait (&job_queue_count);

        /* Lock the mutex on the job queue. */
        pthread_mutex_lock (&job_queue_mutex);
        

        /* Because of the semaphore, we know the queue is not empty. Get
        the next available job. */
        next_job = job_queue;

        /* Remove this job from the list. */
        job_queue = job_queue->next;

        /* Unlock the mutex on the job queue because we’re done with the
        queue for now. */
        pthread_mutex_unlock (&job_queue_mutex);

        /* Carry out the work. */
        process_job (next_job, sumando);
        /* Clean up. */
        free (next_job);
    }
    return NULL;
}

/* Add a new job to the front of the job queue.*/
void enqueue_job (void * function)
{

    struct job* new_job;

    /* Allocate a new job object. */
    new_job = (struct job*) malloc (sizeof (struct job));

    /* Set the other fields of the job struct here... */
    new_job->aumentarUno = function;
    new_job->next = NULL;
    /* Lock the mutex on the job queue before accessing it.*/
    pthread_mutex_lock (&job_queue_mutex);

    /* Place the new job at the head of the queue. */
    new_job->next = job_queue;
    job_queue = new_job;

    /* Post to the semaphore to indicate that another job is available. If
    threads are blocked, waiting on the semaphore, one will become
    unblocked so it can process the job. */
    sem_post (&job_queue_count);

    /* Unlock the job queue mutex. */
    pthread_mutex_unlock (&job_queue_mutex);

}


/*  Función que utilizará el hilo que encargado de encolar jobs a la cola.
    Pasados unos 30 seg. (segundos del programa general), cierra los otros 
    dos hilos y deja de encolar jobs.*/
void* thread_function2() {
    
    time_t final = time(NULL);
    while( final - inicio < 30) {
        /*Vamos encolando los jobs.*/
        for (int i = 0; i < nro_jobs; i++)
        {
            enqueue_job(&aumentar);  
        }
        final = time(NULL);
    }

    pthread_mutex_lock(&thread_function2_mutex);
    pthread_cancel(thread1);
    pthread_cancel(thread2);
    pthread_mutex_unlock(&thread_function2_mutex);
    
    return NULL;
}

int main(int argc, char const *argv[])
{

    
    long long cantidad_esperada = repeticiones*nro_jobs;
    printf("--------------------------------------------------------------------------\n");
    printf("--------------------------------------------------------------------------\n");
    printf( "En este programa, tenemos un ejemplo del uso de semaforos para hilos.\n"
            "El hilo 1 y 2 procesan y realizan los jobs desencolando de job_queue.\n"
            "Mientras tanto, el hilo 3 se encarga de cargar jobs en la cola de jobs.\n"
            "Esto ocurre durante 30 segundos, al termino de los cuales se finalizan\n"
            "los hilos y se imprime la suma obtenida.\n");
    printf("--------------------------------------------------------------------------\n");
    printf( "Obs.: Las condiciones de carrera que ocurrian en el listing 4.9\n"
            "se evitan en este programa mediante el uso de Mutex y semaforos.\n");
    printf("--------------------------------------------------------------------------\n");
    printf("--------------------------------------------------------------------------\n");
    initialize_job_queue();
    intptr_t sumando1 = 3;
    intptr_t sumando2 = 7;
    inicio = time(NULL);
    pthread_create(&thread1, NULL, &thread_function, (void*) sumando1);    
    pthread_create(&thread2, NULL, &thread_function, (void*) sumando2);
    pthread_create(&thread3, NULL, &thread_function2, NULL);    
    pthread_join(thread3,NULL);

    printf("Resultado final: %lld\n", global_integer);
    return 0;
}
