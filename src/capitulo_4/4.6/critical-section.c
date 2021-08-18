#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
/*Listing 4.6 (critical-section.c) Protect a Bank Transaction with a Critical Section*/
/*Obs.: Este ejemplo no tiene ningún código a ejecutar, por eso le agregamos 
el main para probar las funciones en threads.*/

/* An array of balances in accounts, indexed by account number.*/
float* account_balances;

/* Transfer DOLLARS from account FROM_ACCT to account TO_ACCT. Return
0 if the transaction succeeded, or 1 if the balance FROM_ACCT is
too small. */
long long process_transaction (int from_acct, int to_acct, float dollars)
{
    int old_cancel_state;

    /* Check the balance in FROM_ACCT. */
    if (account_balances[from_acct] < dollars)
        return (long long) 1;
    
    /* Begin critical section. */
    pthread_setcancelstate (PTHREAD_CANCEL_DISABLE, &old_cancel_state);
    
    /* Move the money. */
    account_balances[to_acct] += dollars;
    account_balances[from_acct] -= dollars;
    /* End critical section. */
    
    pthread_setcancelstate (old_cancel_state, NULL);
    return (long long) 0;
}


struct transaction 
{
    int from_account;
    int to_account;
    float dollars;
};


void* principal_function (void* parameters) 
{
    struct transaction* aux = (struct transaction*) parameters;
    return (void*) ( process_transaction(aux->from_account, aux->to_account, aux->dollars));
}

int main(int argc, char const *argv[])
{
    pthread_t thread1;
    pthread_t thread2;
    struct transaction thread1_args;
    struct transaction thread2_args;
    long long int aux1, aux2;

    /*Inicializamos 10 cuentas y solo la cuenta 3 tiene dinero registrado*/
    account_balances = malloc(sizeof(float)*10);
    for (int i = 0; i < 10; i++) {
        account_balances[i] = 0.0;
    }
    account_balances[3] = 18.0;

    /*Probamos que las secciones criticas se bloquean 
    cuando un hilo llega a ellas, transferimos usando 2 hilos
    para simular las transacciones.*/
    thread1_args.from_account = 3;
    thread1_args.to_account = 5;
    thread1_args.dollars = 10;
    thread2_args.from_account = 5;
    thread2_args.to_account = 2;
    thread2_args.dollars = 4;
    printf("Imprimimos el array original...\n");
    for (int i = 0; i < 10; i++) {
        printf("%.2f    ", account_balances[i]);
    }
    printf("\n");
    pthread_create(&thread1, NULL, &principal_function,&thread1_args);
    pthread_create(&thread2, NULL, &principal_function, &thread2_args);
    pthread_join(thread1, (void**)  &aux1);
    pthread_join(thread2, (void**) &aux2);
    if (aux1 == 0 && aux2 == 0) {
        printf("Transacciones exitosas.\n");
        printf("Imprimimos el array float para ver las cuentas actualizadas...\n");
        for (int i = 0; i < 10; i++) {
            printf("%.2f    ", account_balances[i]);
        }
        printf("\n");
    } else {
        printf("No se pudieron realizar las transferencias.\n");
    }

    return 0;
}

