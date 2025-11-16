#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// Funcion que crea un arreglo de enteros ordenados de 0 a n-1
// Parametro: n_elements - cantidad de elementos del arreglo
// Retorna: puntero al arreglo creado dinamicamente
int *create_array(size_t n_elements) {
    int *array = (int*)malloc(n_elements * sizeof(int));
    for (size_t i = 0; i < n_elements; i++)
        array[i] = i;

    return array;
}

// Implementacion del algoritmo de busqueda binaria
// Este algoritmo divide el espacio de busqueda a la mitad en cada iteracion
// Complejidad temporal: O(log n)
// Parametros:
//   - n_elements: cantidad total de elementos en el rango de busqueda
//   - target: valor objetivo que se desea encontrar
// Retorna: indice donde se encuentra el elemento o -1 si no se encuentra
size_t binary_search(size_t n_elements, int target) {
    size_t left = 0;               // Limite izquierdo del rango de busqueda
    size_t right = n_elements - 1; // Limite derecho del rango de busqueda

    // Mientras el rango de busqueda sea valido
    while (left <= right) {
        usleep(1); // Pausa de 1 microsegundo para simular operacion costosa
        size_t mid = left + (right - left) / 2; // Calcula el punto medio

        // Si el punto medio es igual al objetivo, lo encontramos
        if (mid == target)
            return mid;
        // Si el punto medio es menor, buscamos en la mitad derecha
        else if (mid < target)
            left = mid + 1;
        // Si el punto medio es mayor, buscamos en la mitad izquierda
        else
            right = mid - 1;
    }

    return -1; // Retorna -1 si no se encuentra el elemento
}

// Funcion principal que ejecuta las pruebas de rendimiento
int main() {

    // Configuracion de parametros para las pruebas
    const int n_tests = 1000000;         // Numero de pruebas a ejecutar
    const size_t n_elements = 100000;    // Cantidad base de elementos
    const size_t target = n_elements - 7; // Elemento objetivo a buscar
    
    // Abre archivo CSV para guardar resultados
    FILE *fp = fopen("../datos/results_binary_search.csv", "w");
    fprintf(fp, "n_elements,elapsed_time\n"); // Encabezado del CSV
    
    struct timespec begin, end; // Estructuras para medir tiempo
    
    // Ejecuta n_tests pruebas con diferentes tamanios de entrada
    for (int i = 1; i <= n_tests; i++) {
        size_t current_n_elements = n_elements * i; // Incrementa el tamanio

        // Registra tiempo inicial
        clock_gettime(CLOCK_REALTIME, &begin);
        size_t result = binary_search(current_n_elements, target); // Ejecuta busqueda
        // Registra tiempo final
        clock_gettime(CLOCK_REALTIME, &end);
        
        // Calcula tiempo transcurrido en segundos
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        double elapsed = seconds + nanoseconds*1e-9;

        // Guarda resultados en archivo CSV
        fprintf(fp, "%zu,%f\n", current_n_elements, elapsed);
        printf("Elements: %lu, Time: %f seconds, Found at index: %lu\n", current_n_elements, elapsed, result);

    }
    fclose(fp);

    return 0;
}