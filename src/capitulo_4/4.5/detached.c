#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

/*Listing 4.5 (detached.c) Skeleton Program That Creates a Detached Thread*/

/*The thread_function imprime los primeros N nros. primos, 
donde N es recibido como parametro de funcion*/
void* thread_function1 (void* thread_arg)
{
    int n = *((int*) thread_arg);
    int i = 1;
    int esPrimo = 1; //0 - False, 1 - True
    int rep = 0;
    printf("Imprimimos los primeros %d nros. primos\n", n);
    while(rep < n) 
    {
        for (int j = 2; j < i; j++) 
        {
            if (i%j == 0) 
            {
                esPrimo = 0;
                break;
            }
        }
        if (esPrimo == 1) 
        {
            fprintf(stdout,"%d  ", i);
            rep++;
        } else {
            esPrimo = 1; //Set a 1 para el siguiente nro.
        }
        i++;
    }
    printf("\n");
  return NULL;
}

/*Imprime en un archivo los primeros N nros. primos.*/
void* thread_function2(void* args) {

    FILE* archivo = fopen("archivoListing4_5.txt", "w");
    int n = *((int*) args);
    int i = 1;
    int esPrimo = 1; //0 - False, 1 - True
    int rep = 0;
    fprintf(archivo,"Guardamos los primeros %d nros. primos\n", n);
    while(rep < n) 
    {
        for (int j = 2; j < i; j++) 
        {
            if (i%j == 0) 
            {
                esPrimo = 0;
                break;
            }
        }
        if (esPrimo == 1) 
        {
            fprintf(archivo,"%d  ", i);
            rep++;
            if (rep%10 == 0) fprintf(archivo, "\n");
        } else {
            esPrimo = 1; //Set a 1 para el siguiente nro.
        }
        i++;
    }
    fprintf(archivo,"\n");
    fclose(archivo);
    return NULL;
}

int main ()
{
    intptr_t n1 = 15; //N para el hilo 1.
    intptr_t n2 = 30; //N para el hilo 2.
    pthread_attr_t attr1;
    pthread_t thread1;
    pthread_t thread2;
    pthread_attr_t attr2;
    pthread_attr_init (&attr1);
    pthread_attr_init (&attr2);
    pthread_attr_setdetachstate (&attr1, PTHREAD_CREATE_DETACHED);
    pthread_attr_setdetachstate(&attr2, PTHREAD_CREATE_DETACHED);

    /* Do work here...  */
    printf("-------------------------------------------------------------\n");
    printf("-------------------------------------------------------------\n");
    printf( "Un detached thread es un hilo que libera sus recursos al    \n"
            "final de su ejecucin sin necesidad de ser joined por otro   \n"
            "hilo. \n"
            "Para probar el hilo, en este programa creamos dos en el main\n"
            "y como en c/c++ cuando termina la ejecucion del main, todos \n"
            "los otros hilos en ejecucion son detenidos, le agregamos un \n"
            "delay al main para dar tiempo a los otros hilos para \n"
            "terminar su ejecucion.\n");
    printf("-------------------------------------------------------------\n");
    printf("-------------------------------------------------------------\n");    
    printf( "Obs.: Para esta prueba, un hilo utiliza una funcion que     \n"
            "imprime en consola los primeros N nros. primos y el otro    \n"
            "hilo utiliza una funcion que guarda en un archivo txt los   \n"
            "primeros N nros. primos.                                    \n");
    printf("-------------------------------------------------------------\n");
    printf("-------------------------------------------------------------\n");
    pthread_create (&thread1, &attr1, &thread_function1, &n1);
    pthread_create (&thread2, &attr1, &thread_function2, &n2);
    pthread_attr_destroy (&attr1);
    pthread_attr_destroy (&attr2);
    /* No need to join the threads.  */
    sleep(3);
    return 0;
}