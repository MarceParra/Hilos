#include <stdio.h>          // Incluir la biblioteca estándar para funciones de entrada/salida
#include <pthread.h>       // Incluir la biblioteca para manejar hilos (threads)

/*
 * Los monitores son una estructura de sincronización que encapsulan datos y métodos, 
 * asegurando que solo un hilo acceda a la sección crítica a la vez.
 * Este programa implementa un monitor para gestionar el acceso a la sección crítica.
 */
typedef struct {
    pthread_mutex_t lock; // Mutex para la exclusión mutua
    pthread_cond_t cond;  // Variable de condición para sincronización
    int count;            // Contador de hilos en la sección crítica
} Monitor;

// Inicializar el monitor
Monitor monitor = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, 0};

// Función para entrar a la región crítica
void enter_region() {
    pthread_mutex_lock(&monitor.lock); // Adquirir el mutex
    while (monitor.count > 0) { // Esperar si hay hilos en la sección crítica
        pthread_cond_wait(&monitor.cond, &monitor.lock); // Esperar a que se libere
    }
    monitor.count++; // Incrementar el contador de hilos
    pthread_mutex_unlock(&monitor.lock); // Liberar el mutex
}

// Función para salir de la región crítica
void exit_region() {
    pthread_mutex_lock(&monitor.lock); // Adquirir el mutex
    monitor.count--; // Decrementar el contador de hilos
    pthread_cond_signal(&monitor.cond); // Notificar a un hilo que espera
    pthread_mutex_unlock(&monitor.lock); // Liberar el mutex
}

// Función que ejecuta cada hilo
void* thread_function(void* arg) {
    enter_region(); // Entrar a la sección crítica
    printf("Hilo %d está en la sección crítica.\n", *(int*)arg); // Mensaje de sección crítica
    exit_region(); // Salir de la sección crítica
    return NULL; // Terminar la función
}

int main() {
    pthread_t threads[5]; // Declarar un arreglo de hilos
    int thread_ids[5] = {0, 1, 2, 3, 4}; // Identificadores de hilos

    // Crear hilos
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    // Esperar a que terminen los hilos
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0; // Finalizar el programa
}
