#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 10

// Función ejecutada por cada hilo
void *PrintHello(void *paramID) {
    int *id = (int *)paramID;
    printf("Hello world thread No. %d\n", *id);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t threadsID[NUM_THREADS];  // Arreglo de IDs de hilos
    int param[NUM_THREADS];            // Parámetros que se pasan a los hilos

    // Crear los hilos en un ciclo
    for (int t = 0; t < NUM_THREADS; t++) {
        printf("Main: creando el thread No. %d\n", t);
        param[t] = t;
        int rc = pthread_create(&threadsID[t], NULL, PrintHello, (void *)&param[t]);
        if (rc) {
            printf("ERROR: código de retorno desde pthread_create %d\n", rc);
            exit(-1);
        }
    }

    // Hacer join a los hilos en un ciclo separado
    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threadsID[t], NULL);
    }

    pthread_exit(NULL);  // Finaliza el hilo principal
}