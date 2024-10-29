/* Implementación del algoritmo de exclusión mutua de Peterson para 
   dos procesos, que utiliza banderas de interés y un turno para 
   controlar el acceso a la región crítica. */

#define FALSE 0
#define TRUE 1
#define N 2

int turno; 
int interesado[N]; 

void entrar_region(int proceso) {
    int otro = 1 - proceso; 
    interesado[proceso] = TRUE; 
    turno = proceso; 
    while (interesado[otro] == TRUE && turno == proceso) {
        // Espera si el otro proceso está interesado y es su turno
    }
}

void salir_region(int proceso) {
    interesado[proceso] = FALSE; 
}
