#include <pthread.h>  // Incluir la biblioteca para trabajar con hilos (Pthreads)
#include <stdio.h>    // Incluir la biblioteca para funciones de entrada/salida estándar
#include <stdlib.h>   // Incluir la biblioteca para funciones de utilidad como exit()

#define NUMERO_DE_HILOS 10  // Definir una constante para el número de hilos a crear

// Función que se ejecutará en cada hilo
void *imprimir_hola_mundo(void *tid) {
    /* Esta función imprime el identificador del hilo y después termina. */
    // Convertir tid a un entero y luego imprimirlo
    printf("Hola mundo. Saludos del hilo %d\n", (int)(long)tid);
    pthread_exit(NULL); // Terminar el hilo actual
}

int main(int argc, char *argv[]) {
    /* El programa principal crea 10 hilos y después termina. */
    pthread_t hilos[NUMERO_DE_HILOS]; // Array para almacenar los identificadores de los hilos
    int estado, i; // Variables para almacenar el estado de creación del hilo y el índice del bucle

    // Crear un bucle para crear los hilos
    for(i = 0; i < NUMERO_DE_HILOS; i++) {
        printf("Aquí main. Creando hilo %d\n", i); // Mensaje que indica que se está creando un hilo
        // Crear un nuevo hilo; pasar la dirección del hilo, atributos (NULL para valores por defecto),
        // la función a ejecutar y el identificador del hilo como argumento
        estado = pthread_create(&hilos[i], NULL, imprimir_hola_mundo, (void *)(long)i);
        
        // Comprobar si hubo un error al crear el hilo
        if (estado != 0) {
            printf("Ups. pthread_create devolvió el código de error %d\n", estado); // Mensaje de error
            exit(-1); // Salir del programa si hay un error
        }
    }

    // Esperar a que cada hilo termine antes de salir del programa
    for(i = 0; i < NUMERO_DE_HILOS; i++) {
        pthread_join(hilos[i], NULL); // Esperar a que el hilo i termine
    }

    exit(0); // Salir del programa con éxito
}
