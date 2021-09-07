#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int thread_flag;
pthread_mutex_t thread_flag_mutex;

void do_work();


void initialize_flag ()
{
	pthread_mutex_init (&thread_flag_mutex, NULL);
	thread_flag = 0;
}
/* Calls do_work repeatedly while the thread flag is set; otherwise
spins. */
void* thread_function (void* thread_arg)
{
	while (1) {
		int flag_is_set;/* Protect the flag with a mutex lock. */
		pthread_mutex_lock (&thread_flag_mutex);
		flag_is_set = thread_flag;
		pthread_mutex_unlock (&thread_flag_mutex);
		if (flag_is_set)
			do_work ();
		/* Else don't do anything. Just loop again.
		*/
	}
	return NULL;
}
/* Sets the value of the thread flag to FLAG_VALUE.
*/
void set_thread_flag (int flag_value)
{
/* Protect the flag with a mutex lock. */
	pthread_mutex_lock (&thread_flag_mutex);
	thread_flag = flag_value;
	pthread_mutex_unlock (&thread_flag_mutex);
}

int main(int argc, char const *argv[])
{
	//iniciamos mutex y asignamos 0 la bandera
	initialize_flag();

	pthread_t threads1;
	pthread_create(&threads1, NULL, &thread_function, NULL);

	printf("Esperamoss 10 seg\n");
	sleep(10);
	printf("activamos\n");
	set_thread_flag(1);
	printf("Esperamoss 10 seg\n");
	sleep(10);
	printf("desactivamos\n");
	set_thread_flag(0);


	return 0;
}

void do_work (){
	sleep(1);
	printf("Duermo desde hilo\n");
}