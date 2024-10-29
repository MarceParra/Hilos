#include <stdio.h>          // Incluir la biblioteca estándar para funciones de entrada/salida
#include <pthread.h>       // Incluir la biblioteca para manejar hilos (threads)

/*
 * Los mutex (exclusión mutua) permiten que solo un hilo acceda a un recurso compartido a la vez, 
 * garantizando la sincronización y evitando condiciones de carrera. 
 * Este programa demuestra el uso de un mutex para controlar el acceso a una sección crítica.
 */
pthread_mutex_t lock;     // Declarar un mutex

// Función que ejecuta cada hilo
void* thread_function(void* arg) {
    pthread_mutex_lock(&lock); // Adquirir el mutex
    printf("Hilo %d está en la sección crítica.\n", *(int*)arg); // Mensaje de sección crítica
    pthread_mutex_unlock(&lock); // Liberar el mutex
    return NULL; // Terminar la función
}

int main() {
    pthread_t threads[5]; // Declarar un arreglo de hilos
    int thread_ids[5] = {0, 1, 2, 3, 4}; // Identificadores de hilos
    pthread_mutex_init(&lock, NULL); // Inicializar el mutex

    // Crear hilos
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    // Esperar a que terminen los hilos
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock); // Destruir el mutex
    return 0; // Finalizar el programa
}
