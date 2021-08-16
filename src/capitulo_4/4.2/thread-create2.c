#include <pthread.h>
#include <stdio.h>

/*Listing 4.2 (thread-create2) Create Two Threads*/
/*Obs.: Este programa tiene como fin pasar datos a dos hilos y ejecutarlos.
        Este ejemplo listing4.2 no presenta un código funcional 
        (porque eso era el objetivo de este ejemplo), y dicho
        inconveniente lo soluciona en el ejemplo listing_4.3.
        Para lograr que el código actual sea funcional, le 
        agregamos el código que asegure los threads 1 y 2
        finalicen antes de terminar la ejecución del main principal
        (este era el problema que se presentaba en este ejemplo).*/




/* Parameters to print_function. */
struct char_print_parms
{
    /* The character to print. */
    char character;
    /* The number of times to print it. */
    int count;
};

/* Prints a number of characters to stderr, as given by PARAMETERS,
which is a pointer to a struct char_print_parms. */
void* char_print (void* parameters)
{
    /* Cast the cookie pointer to the right type. */
    struct char_print_parms* p = (struct char_print_parms*) parameters;
    
    int i;
    for (i = 0; i < p->count; ++i)
        fputc (p->character, stderr);
    
    return NULL;
}

/* The main program. */
int main ()
{
    pthread_t thread1_id;
    pthread_t thread2_id;
    struct char_print_parms thread1_args;
    struct char_print_parms thread2_args;

    /* Create a new thread to print 30,000 ’x’s. */
    thread1_args.character = 'x';
    thread1_args.count = 30000;
    pthread_create (&thread1_id, NULL, &char_print, &thread1_args);

    /* Create a new thread to print 20,000 o’s. */
    thread2_args.character = 'o';
    thread2_args.count = 20000;
    pthread_create (&thread2_id, NULL, &char_print, &thread2_args);

    /*Agregado: Asegurarnos que el 1er y 2do thread hayan terminado.
    Para ello, se utiliza la función phthread_join, de la librería 
    pthread.h. Su primer parámetro es el thread ID del thread 
    a esperar finalice, y su segundo parámetro es el valor de retorno
    del thread (en este caso, no retornan ningún valor).*/
    pthread_join(thread1_id, NULL);
    pthread_join(thread2_id, NULL);
    /*Ahora puede finalizar el main sin haber interrumpido los hilos.*/
    return 0;
}