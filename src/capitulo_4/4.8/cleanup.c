#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  Listing 4.8 (cleanup.c) Program Fragment Demonstrating a Thread
    Cleanup Handler*/

/*Obs.: Este programa está incompleto, por eso le agregamos el código
        que le falta para ser funcional.*/

struct archivosNombres
{
    char* nombreArchivo1;
    char* nombreArchivo2;
};



/* Allocate a temporary buffer.*/
void* allocate_buffer (size_t size)
{
    return malloc (size);
}

/* Deallocate a temporary buffer.*/
void deallocate_buffer (void* buffer)
{
    free (buffer);
}

/*Función para hacer fflush, ya que fflush() es una función no estándar.*/
void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void* do_some_work (void* parameters)
{

    /* Allocate a temporary buffer.*/
    void* temp_buffer = allocate_buffer (1024);

    /* Register a cleanup handler for this buffer, to deallocate it in
    case the thread exits or is cancelled. */
    pthread_cleanup_push (deallocate_buffer, temp_buffer);

    /* Do some work here that might call pthread_exit or might be
    cancelled... */
    struct archivosNombres datos = *(struct archivosNombres*) parameters;
    FILE * archivo1 = fopen(datos.nombreArchivo1, "r");
    FILE * archivo2 = fopen(datos.nombreArchivo2, "w");    
    if (archivo1 == NULL || archivo2 == NULL) {
        printf("La ejecucion del hilo fue interrumpida...\n");
        pthread_exit(NULL); //la función fue interrumpida.
    } else {
        char* aux = malloc(sizeof(char)*100);
        fgets(aux, 100, archivo1);
        while(!feof(archivo1)) {
            fprintf(archivo2, "%s", aux);
            fgets(aux, 100, archivo1);
        }
        fclose(archivo1);
        fclose(archivo2);
    }

    /* Unregister the cleanup handler. Because we pass a nonzero value,
    this actually performs the cleanup by calling
    deallocate_buffer. */
    pthread_cleanup_pop (1);
}

char menu() {
    char opcion = ' ';
    printf("------------------------------------------------------\n");
    printf("Seleccione una opcion:\n"
            "a - Crear el archivo original\n"
            "b - Crear copia.\n"
            "c - Eliminar original.\n"
            "d - Eliminar copia.\n"
            "e - Cerrar programa\n");
    printf("Opcion: "); scanf("%c", &opcion);
    clean_stdin();
    printf("\n------------------------------------------------------\n");
    return opcion;
} 



int main(int argc, char const *argv[])
{
    printf("Descripción: En este programa, creamos una copia de un archivo txt dado.\n"
    "Si el archivo a copiar no existe, el thread se cancela en ejecución.\n"
    "El nombre del archivo es archivo1.txt.\n");
    char opcion;
    int seguir = 1;
    char* texto = malloc(sizeof(char)*1000);
    char nombre1[13] = "archivo1.txt";
    char nombre2[13] = "archivo2.txt";
    while (seguir == 1) 
    {
        opcion = menu();
        switch (opcion)
        {
        case 'a':
            printf("Creando (o agregando) linea en el archivo original...\n");
            FILE * archivo1 = fopen(nombre1, "a");
            printf("Ingrese texto para el archivo: \n");
            scanf("%[^\n]s",texto);
            fprintf(archivo1,"%s\n", texto);
            clean_stdin();
            printf("Archivo creado.\n");
            fclose(archivo1);
            break;
        case 'b': ;
            printf("Creando una copia...\n");
            pthread_t thread;
            struct archivosNombres datos;
            datos.nombreArchivo1 = nombre1; 
            datos.nombreArchivo2 = nombre2;
            pthread_create(&thread, NULL, &do_some_work, &datos);
            pthread_join(thread, NULL);
            break;
        case 'c':
            printf("Eliminando archivo1...\n");
            if (remove(nombre1) == 0) printf("Borrado exitosamente!\n");
            else printf("No se pudo eliminar!\n"); 
            break;
        case 'd':
            printf("Eliminando archivo2...\n");
            if (remove(nombre2) == 0) printf("Borrado exitosamente!\n");
            else printf("No se pudo eliminar!\n"); 
            break;
        case 'e':
            printf("Finalizando programa...\n");
            seguir = 0;
            break;
        default:
            printf("Opcion invalida!\n");
            break;
        }
        printf("------------------------------------------------------\n");
        printf("Presione ENTER para continuar...\n");
        clean_stdin();
    }

    return 0;
}
