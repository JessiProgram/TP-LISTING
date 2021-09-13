#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

sig_atomic_t child_exit_status;

void clean_up_child_process (int signal_number) {
	/* Clean up the child process. */
	int status;
	wait (&status);
	/* Store its exit status in a global variable.*/
	child_exit_status = status;
}

int main () {
	/* Handle SIGCHLD by calling clean_up_child_process. */
	struct sigaction sigchld_action;
	memset (&sigchld_action, 0, sizeof (sigchld_action));
	sigchld_action.sa_handler = &clean_up_child_process;
	sigaction (SIGCHLD, &sigchld_action, NULL);
	
	/* Now do things, including forking a child process.*/
	sleep(5);

	printf("Creamos un hijo\n");
	pid_t child_pid;
	printf ("the main program process ID is %d\n", (int) getpid());

	child_pid = fork () ;
	if ( child_pid != 0 ) {
		printf ("this is the parent process, with id %d\n", (int) getpid ());
		printf ("the child's process ID is %d\n",(int) child_pid );
		printf("Dormimos padre 300 seg\n");
		sleep(300);
		printf("Fin padre\n");
		
	}else{
		printf ("this is the child process, with id %d\n", (int) getpid ());
		printf("Dormimos hijo 10 seg\n");
		sleep(10);
		printf("Fin hijo\n");

	}

	return 0;
}