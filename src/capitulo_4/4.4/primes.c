#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
/* Listing 4.4 ( primes.c) Compute Prime Numbers in a Thread*/

/* Compute successive prime numbers (very inefficiently).  Return the
Nth prime number, where N is the value pointed to by *ARG.  */
/*Obs.: También computamos el nro. enésimo N de una sucesión de fibonacci.*/
void* compute_prime (void* arg)
{
    intptr_t candidate = 2;
    int n = *((int*) arg);
    while (1) {
        int factor;
        int is_prime = 1;
        /* Test primality by successive division.  */
        for (factor = 2; factor < candidate; ++factor)
            if (candidate % factor == 0) {
                is_prime = 0;
                break;
            }
        /* Is this the prime number we’re looking for?  */
        if (is_prime) {
            if (--n == 0)
                /* Return the desired prime number as the thread return value.  */
                return (void*) candidate;
        }
        ++candidate;
    }

    return NULL;
}

/*Codigo agregado:*/
/*Retorna el N-esimo nro de fibonacci.*/
void* compute_fibo(void* arg)
{
    
    int n = *((int*) arg);
    if (n == 1) return (void*) ((intptr_t) 0);
    if (n == 2) return (void*) ((intptr_t) 1); 
    intptr_t resultado = 0;
    int a = 0,b = 1;
    for(int i = 2; i < n; i++)//loop starts from 2 because 0 and 1 are already printed    
    {    
        resultado = a + b;    
        a = b;    
        b = resultado;    
    }  

    return (void*) resultado;
}



int main ()
{
    pthread_t thread;
    pthread_t thread2;
    int which_prime = 5000;
    int prime;
    int n = 10; //Para el valor de N para hallar el N-ésimo nro de fibonacci.
    int enesimo_fibo;
    
    /* Start the computing thread, up to the 5,000th prime number.  */
    pthread_create (&thread, NULL, &compute_prime, &which_prime);
    
    /* Do some other work here...  */
    pthread_create(&thread2, NULL, &compute_fibo, &n);
    
    /* Wait for the prime number thread to complete, and get the result.  */
    pthread_join (thread, (void*) &prime);
    
    pthread_join (thread2, (void*) &enesimo_fibo);
    
    /* Print the largest prime it computed.  */
    printf("The %dth prime number is %d.\n", which_prime, prime);
    printf("El numero de fibonacci nro. %d es: %d\n", n, enesimo_fibo);
    return 0;
}