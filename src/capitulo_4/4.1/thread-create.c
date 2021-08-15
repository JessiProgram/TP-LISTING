#include <pthread.h>
#include <stdio.h>
/*Obs.:Este ejemplo no necesita que se le adicione 
codigo para ser funcional.*/

/*Prints x's to stderr. The parameter is unused. Does not return*/

void* print_xs(void* unused) 
{
    while(1)
        fputc('x', stderr);
    return NULL;
}

/*The main program*/

int main()
{
    pthread_t thread_id;
    /*Create a new thread. The new thread will run the 
    print_xs function*/
    pthread_create (&thread_id, NULL, &print_xs, NULL);

    /*Print o's continuously to stderr*/
    while(1)
        fputc('o', stderr);
    
    return 0;
}
/*Recordar para el makefile:
Para compilar en linux:  cc -o thread-create thread-create.c -lpthread*/