#include <iostream>
#include <pthread.h>
#include <vector>

using namespace std;

// Estructura para pasar parámetros a la función de los hilos
struct FibonacciParams {
    int n;          // Índice del número de Fibonacci a calcular
    int result;     // Resultado de Fibonacci(n)
};

// Función para calcular el número de Fibonacci de forma recursiva
void* calcular_fibonacci(void* arg) {
    FibonacciParams* params = (FibonacciParams*) arg;
    int n = params->n;

    if (n == 0) {
        params->result = 0;
    } else if (n == 1) {
        params->result = 1;
    } else {
        int fib1 = 0, fib2 = 1, fibN = 0;
        for (int i = 2; i <= n; ++i) {
            fibN = fib1 + fib2;
            fib1 = fib2;
            fib2 = fibN;
        }
        params->result = fibN;
    }
    
    pthread_exit(nullptr);
}

int main() {
    int num;
    
    // Pedir al usuario un número entre 0 y 100
    do {
        cout << "Ingrese un número entre 0 y 100: ";
        cin >> num;
    } while (num < 0 || num > 100);
    
    vector<FibonacciParams> fib_params(num + 1);
    vector<pthread_t> threads(num + 1);
    int suma_total = 0;
    
    // Crear los hilos para calcular los números de Fibonacci
    for (int i = 0; i <= num; ++i) {
        fib_params[i].n = i;
        pthread_create(&threads[i], nullptr, calcular_fibonacci, (void*)&fib_params[i]);
    }
    
    // Esperar a que los hilos terminen y acumular los resultados
    for (int i = 0; i <= num; ++i) {
        pthread_join(threads[i], nullptr);
        cout << "F" << i << " = " << fib_params[i].result << endl;
        suma_total += fib_params[i].result;
    }
    
    // Imprimir la suma total de los números de Fibonacci encontrados
    cout << "La suma total de los números de Fibonacci hasta F" << num << " es: " << suma_total << endl;
    
    return 0;
}