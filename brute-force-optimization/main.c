#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Funcion objetivo que se desea minimizar
// Formula: f(x) = 2*sin(x) + x^2/100
// Esta funcion tiene multiples minimos locales
// Parametro: x - valor de entrada
// Retorna: valor de la funcion evaluada en x
double objective_function(double x) {
    return (2 * sin(x)) + (pow(x, 2) / 100);
}

// Genera un arreglo de valores igualmente espaciados entre start y end
// Similar a la funcion linspace de NumPy/MATLAB
// Parametros:
//   - start: valor inicial del rango
//   - end: valor final del rango
//   - num_points: cantidad de puntos a generar
// Retorna: puntero al arreglo de valores generados
double *linspace(double start, double end, int num_points) {
    double *array = (double*)malloc(num_points * sizeof(double));
    double step = (end - start) / (num_points - 1); // Calcula el incremento entre puntos

    // Genera cada punto del arreglo
    for (int i = 0; i < num_points; i++)
        array[i] = start + (i * step);

    return array;
}

// Ejecuta optimizacion por fuerza bruta
// Este algoritmo evalua la funcion objetivo en todos los puntos del dominio
// y selecciona el que produce el menor valor
// Complejidad temporal: O(n) donde n es num_points
// Parametro: num_points - cantidad de puntos a evaluar en el dominio
void run_optimization(int num_points) {
    double lower_bound = -100.0; // Limite inferior del dominio
    double upper_bound =  100.0;  // Limite superior del dominio
    
    // Genera puntos igualmente espaciados en el dominio
    double *x_values = linspace(lower_bound, upper_bound, num_points);

    // Inicializa el mejor punto encontrado con el primer valor
    double x_star = x_values[0];
    double y_star = objective_function(x_star);

    // Itera sobre todos los puntos evaluando la funcion objetivo
    for (size_t i = 0; i < num_points; i++) {
        // Si encuentra un valor menor, actualiza el mejor punto
        if (objective_function(x_values[i]) < y_star) {
            x_star = x_values[i];
            y_star = objective_function(x_values[i]);
        }
    }

    free(x_values); // Libera memoria del arreglo
}

// Funcion principal que ejecuta las pruebas de rendimiento
int main() {

    // Configuracion de parametros para las pruebas
    const int n_tests = 100;       // Numero de pruebas a ejecutar
    const int num_points = 100000; // Cantidad base de puntos a evaluar

    // Abre archivo CSV para guardar resultados
    FILE *fp = fopen("results_brute_force.csv", "w");
    fprintf(fp, "num_points,elapsed_time\n");
    
    struct timespec begin, end; // Estructuras para medir tiempo
    
    // Ejecuta n_tests pruebas con diferentes cantidades de puntos
    for (int i = 1; i <= n_tests; i++) {

        // Registra tiempo inicial
        clock_gettime(CLOCK_REALTIME, &begin);
        run_optimization(num_points * i); // Ejecuta optimizacion
        // Registra tiempo final
        clock_gettime(CLOCK_REALTIME, &end);
        
        // Calcula tiempo transcurrido en segundos
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        double elapsed = seconds + nanoseconds*1e-9;

        // Guarda resultados en archivo CSV
        fprintf(fp, "%d,%f\n", num_points*i, elapsed);
        printf("Test %d: %f seconds\n", num_points*i, elapsed);
    }

    fclose(fp); 

    return 0;
}