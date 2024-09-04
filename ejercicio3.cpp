#include <iostream>
#include <pthread.h>
#include <vector>
#include <cmath>

// Estructura para almacenar los datos de cada hilo
struct ThreadData {
    int n;
    double result;
};

// Función que calculará cada término de la serie
void* calcular_termino(void* args) {
    ThreadData* data = static_cast<ThreadData*>(args);
    int n = data->n;
    data->result = pow(-1, n + 1) / static_cast<double>(n); // (-1)^(n+1) / n
    return nullptr; // Retorno corregido
}

int main() {
    int n_max;
    std::cout << "Ingrese el valor maximo de n a evaluar en la serie: ";
    std::cin >> n_max;

    std::vector<pthread_t> threads(n_max);    // Vector para almacenar los pthreads
    std::vector<ThreadData> thread_data(n_max); // Almacenar los resultados de cada hilo

    // Crear hilos
    for (int i = 0; i < n_max; ++i) {
        thread_data[i].n = i + 1;
        pthread_create(&threads[i], nullptr, calcular_termino, &thread_data[i]);
    }

    // Esperar a que los hilos terminen y sumar los resultados
    double suma_total = 0.0;
    for (int i = 0; i < n_max; ++i) {
        pthread_join(threads[i], nullptr);
        suma_total += thread_data[i].result;
    }

    // Imprimir el resultado de la suma de la serie
    std::cout << "El valor de la serie para n_max = " << n_max << " es: " << suma_total << std::endl;

    return 0;
}
