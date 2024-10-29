#include <stdio.h>          // Incluir la biblioteca estándar para funciones de entrada/salida
#include <pthread.h>       // Incluir la biblioteca para manejar hilos (threads)
#include <semaphore.h>      // Incluir la biblioteca para semáforos

/*
 * Los semáforos controlan el acceso a múltiples recursos, 
 * permitiendo un número limitado de hilos que accedan a la sección crítica al mismo tiempo.
 * Este programa ilustra el uso de un semáforo para gestionar el acceso a recursos compartidos.
 */
sem_t semaphore;           // Declarar un semáforo

// Función que ejecuta cada hilo
void* thread_function(void* arg) {
    sem_wait(&semaphore); // Decrementar el semáforo (esperar si es 0)
    printf("Hilo %d está en la sección crítica.\n", *(int*)arg); // Mensaje de sección crítica
    sem_post(&semaphore); // Incrementar el semáforo (liberar)
    return NULL; // Terminar la función
}

int main() {
    pthread_t threads[5]; // Declarar un arreglo de hilos
    int thread_ids[5] = {0, 1, 2, 3, 4}; // Identificadores de hilos
    sem_init(&semaphore, 0, 2); // Inicializar el semáforo permitiendo 2 accesos simultáneos

    // Crear hilos
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    // Esperar a que terminen los hilos
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore); // Destruir el semáforo
    return 0; // Finalizar el programa
}
