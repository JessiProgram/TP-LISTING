#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/*Listing 4.9 (cxx-exit.cpp) Implementing Safe Thread Exit with C++ Exceptions*/
/*Observaciones:    Este código se encuentra incompleto, por ello, le agregamos
                    implementación en la función do_some_work() y un main.*/

/*Exception de ejecución en un hilo*/
class ThreadExitException
{
    public:
    /* Create an exception-signaling thread exit with RETURN_VALUE.*/
    ThreadExitException (void* return_value)
        : thread_return_value_ (return_value)
    {
    }

    /* Actually exit the thread, using the return value provided in the
    constructor. */
    void* DoThreadExit ()
    {
        pthread_exit (thread_return_value_);
        return NULL;
    }

    private:
    /* The return value that will be used when exiting the thread.*/
    void* thread_return_value_;

};

struct data
{
    char* palabra;
    char* nombreArchivo;
};

/*Valida que la palabra encontrada no sea parte de otra palabra,
y verifica que se considere como palabra válida en caso de que 
la sgte. letra sea punto o coma*/
int validez(size_t found, char* word, string palabra) 
{
    if (found == 0) {
        if (found + palabra.length() == strlen(word)) {
            return 1;
        } else if ((word[palabra.length()]==',' || word[palabra.length()]=='.')) {
            return 1;
        }
    }
    return 0;
}

/*Función llamada por el hilo en ejecución.*/
/*Recibe un string y */
void* do_some_work (struct data datos)
{
    std::string palabra(datos.palabra);
    FILE* file = fopen(datos.nombreArchivo,"r");
    char word[30];
    fscanf(file, "%s", word);
    while (1) {
        /* Do some useful things here...*/
        fscanf(file, "%s", word);
        std::string str(word);
        size_t found = str.find(palabra);
        if (validez(found, word, palabra)) {
            cout << "La palabra \"" << palabra << "\" fue encontrada en el texto!!!\n";
            fclose(file);
            break;
        }
        if (feof(file)) 
        {
            cout << "La palabra \"" << palabra << "\" NO fue encontrada!!!\n";
            fclose(file);
            throw ThreadExitException (/* thread’s return value = */ NULL);
        }
    }
    return NULL;
}

void* thread_function (void* args)
{;
    try {
        do_some_work (*(struct data*) args);
    }
    catch (ThreadExitException ex) {
        /* Some function indicated that we should exit the thread.*/
        printf("Thread finalizado por excepcion...\n");
        ex.DoThreadExit ();
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    char nombreArchivo[] = "archivo.txt"; 
    char palabra[20]; //Palabra a buscar
    pthread_t thread;
    struct data aux;
    printf("-------------------------------------------------------------------\n");
    printf( "Descripcion: Recibe como input de usuario un string a ser buscado\n"
            "dentro de un archivo txt. La idea de este ejercicio es no encontrar\n"
            "la palabra buscada, y asi disparar la excepcion que detiene\n"
            "el hilo.\n");
    printf("-------------------------------------------------------------------\n");
    printf("-------------------------------------------------------------------\n");
    FILE * archivo = NULL;
    archivo = fopen(nombreArchivo, "w");
    char text[] =           "In computer science, a thread of execution is the smallest sequence\n"
                            "of programmed instructions that can be managed independently by a\n"
                            "scheduler, which is typically a part of the operating system.\n"
                            "The implementation of threads and processes differs between\n"
                            "operating systems, but in most cases a thread is a component of a\n"
                            "process. The multiple threads of a given process may be executed\n"
                            "concurrently (via multithreading capabilities), sharing resources\n"
                            "such as memory, while different processes do not share these\n"
                            "resources. In particular, the threads of a process share its\n"
                            "executable code and the values of its dynamically allocated\n"
                            "variables and non-thread-local global variables at any given time.\n";
    printf("Texto del archivo:\n%s", text);
    printf("-------------------------------------------------------------------\n");
    printf("-------------------------------------------------------------------\n");
    fprintf(archivo, "%s", text);
    fclose(archivo);
    printf("Ingrese palabra a buscar: "); scanf("%s", palabra);
    printf("-------------------------------------------------------------------\n");
    aux.nombreArchivo = nombreArchivo;
    aux.palabra = palabra;
    pthread_create(&thread, NULL, &thread_function, &aux);
    pthread_join(thread, NULL);
    remove("archivo.txt");
    printf("-------------------------------------------------------------------\n");
    return 0;
}
/*Para compilar: g++ -o cxx-exit cxx-exit.cpp -lpthread*/
