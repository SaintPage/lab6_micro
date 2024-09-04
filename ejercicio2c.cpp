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
    pthread_t threadID;  // ID del hilo
    int param;

    // Crear el hilo y hacer join dentro del mismo ciclo
    for (int t = 0; t < NUM_THREADS; t++) {
        printf("Main: creando el thread No. %d\n", t);
        param = t;
        int rc = pthread_create(&threadID, NULL, PrintHello, (void *)&param);
        if (rc) {
            printf("ERROR: código de retorno desde pthread_create %d\n", rc);
            exit(-1);
        }
        pthread_join(threadID, NULL);
    }

    pthread_exit(NULL);  // Finaliza el hilo principal
}