#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include <time.h>
#include <math.h>
#define MAX_INTENTOS 10

sig_atomic_t sigusr1_count = 0;

void handler (int signal_number) {
    ++sigusr1_count;
}

int main () {
    srand(time(NULL)); 

    struct sigaction sa;
    memset (&sa, 0, sizeof (sa)); 
    sa.sa_handler = &handler;
    sigaction (SIGUSR1, &sa, NULL);

    int ret;
    int M = 1;
    int N = 6;
    int intentos = 0;

    printf("\nProceso id: %d\n", getpid());
    while (1) {
        printf("\n##############################\n");

        // Sumar un intento
        ++intentos;

        // Lanzar dados
        int dado1 = rand() % (N-M+1) + M;
        int dado2 = rand() % (N-M+1) + M;
        printf("Intento %d\n", intentos);
        printf("Dados lanzados\n");
        printf("    Dado1: %d\n", dado1);
        printf("    Dado2: %d\n", dado2);

        // Obtener la diferencia de los valores de dado 1 y 2
        int diff = (int) fabs((double) (dado1 - dado2));
        printf("Difieren en %d\n", diff);

        // Verificar que difieran el valor de cada dado en 2
        if (diff <= 2) {
            ret = kill(getpid(), SIGUSR1);  // kill -USR1 {{ getpid() }}
            printf("    Señal/es realizadas %d\n", sigusr1_count);
        }

        // Si da error la funcion kill() retornar 1
        if (ret == -1) {
            return 1;
        }

        printf("##############################\n");
        
        // Espera 1 segundo para que se lancen los 2 siguientes dados
        sleep(1);

        // Si se llega a la cantidad maxima de intentos, salir
        if (intentos == MAX_INTENTOS) {
            break;
        }
    }

    printf ("SIGUSR1 was raised %d times\n", sigusr1_count);

    return 0;

}