#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <math.h>

/*Listing 4.7 (tsd.c) Per-Thread Log Files Implemented with Thread-Specific Data*/

/* The key used to associate a log file pointer with each thread.*/
static pthread_key_t thread_log_key;

/* Write MESSAGE to the log file for the current thread.*/
void write_to_thread_log (const char* message)
{
    FILE* thread_log = (FILE*) pthread_getspecific (thread_log_key);
    fprintf (thread_log, "%s\n", message);
}

/* Close the log file pointer THREAD_LOG.*/
void close_thread_log (void* thread_log) {
    fclose ((FILE*) thread_log);
}

/*Código agregado: Encuentra el sgte. nro. cuadrado perfecto luego de un 
valor randómicamente generado 0 < N < 500. 
Por ejemplo,    si N = 5, el siguiente cuadrado perfecto es 9,
                si N = 89, el siguiente cuadrado perfecto es 100...*/

int find_square(int N) 
{
    int aux1;
    int i = N;

    do
    {
        i++;
        aux1 = (int) sqrt((double) i);
    } while (aux1 * aux1 != i);
    return i;
}



void* thread_function (void* args)
{
    char thread_log_filename[20];
    FILE* thread_log;

    /* Generate the filename for this thread’s log file. */
    sprintf (thread_log_filename, "thread%d.log", (int) pthread_self ());

    /* Open the log file. */
    thread_log = fopen (thread_log_filename, "w");

    /* Store the file pointer in thread-specific data under thread_log_key.*/
    pthread_setspecific (thread_log_key, thread_log);
    int N = *(int*) args;
    write_to_thread_log ("Thread starting.");
    write_to_thread_log ("Calculating...");
    long long square = (long long) find_square(N);
    write_to_thread_log ("Calculations Finished...");
    return (void*) square;
}

int main ()
{
    int i;
    int aux;
    void* aux1;
    pthread_t threads[5];
    long long resultados[5];

    /* Create a key to associate thread log file pointers in
    thread-specific data. Use close_thread_log to clean up the file
    pointers. */
    pthread_key_create (&thread_log_key, close_thread_log);
    srand(time(NULL));  
    /* Create threads to do the work. */
    printf("Generamos numeros aleatorios...\n");
    for (i = 0; i < 5; ++i) {
        aux = (int) rand() % 100 + 1;
        pthread_create (&(threads[i]), NULL, thread_function, &aux);
    }
    /* Wait for all threads to finish. */
    for (i = 0; i < 5; ++i) {
        pthread_join (threads[i], &aux1); 
        resultados[i] = (long long) aux1;
    }
    
    /*Imprimimos los resultados*/
    printf("Los siguientes numeros, son cuadrados perfectos mas cercanos y \nmayores a los generados randomicamente:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%lld  ", resultados[i]);
    }
    printf("\n");
    return 0;
}

/*Obs.: Para el makefile, usar "cc -o tsd tsd.c -lpthread -lm"*/