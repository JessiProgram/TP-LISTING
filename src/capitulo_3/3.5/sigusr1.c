#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
sig_atomic_t sigusr1_count = 0;

void handler (int signal_number) {
    ++sigusr1_count;
}

#define MAX_CALSS_SIGUSR1 5

int main () {
    struct sigaction sa;
    memset (&sa, 0, sizeof (sa)); 
    sa.sa_handler = &handler;
    sigaction (SIGUSR1, &sa, NULL);

    pid_t child_pid = fork();
    if (child_pid != 0) {
        
        int i = 0;
        while (1) {

            if (sigusr1_count == MAX_CALSS_SIGUSR1) {
                kill(child_pid, SIGKILL);
                break;
            }
            
            // Realizando algun trabajo
            sleep(1);
        }

    } else {

        int llamadas = 0;

        while (1) {
            int option;
            printf("\n--------------------------\n");
            printf("Proceso padre: |%d| - Llamadas: |%d|\n", getppid(), llamadas);
            printf("Proceso hijo: |%d|\n", getpid());

            printf("\nOperaciones:\n");
            printf("1. Llamar a señal de proceso padre %d\n", getppid());
            printf("$ Elija una opción: ");

            scanf("%d", &option);

            int ret;
            switch (option) {

                case 1: // Llamar a handler
                    ret = kill(getppid(), SIGUSR1);

                    if (ret == -1) {
                        break;
                    }
                    
                    ++llamadas;
                    if (llamadas == 5) {
                        return 0;
                    }
                    
                    break;
                
                default:
                    printf("\n--------------------------\n");
                    printf("Opcion invalida..\n\n");
                    break;
            }
            
        }
        
    }

    printf ("SIGUSR1 was raised %d times\n", sigusr1_count);

    return 0;

}