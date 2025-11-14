#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


double objective_function(double x) {
    return (2 * sin(x)) + (pow(x, 2) / 100);
}


double *linspace(double start, double end, int num_points) {
    double *array = (double*)malloc(num_points * sizeof(double));
    double step = (end - start) / (num_points - 1);

    for (int i = 0; i < num_points; i++)
        array[i] = start + (i * step);

    return array;
}


void run_optimization(int num_points) {
    double lower_bound = -100.0;
    double upper_bound =  100.0;
    double *x_values = linspace(lower_bound, upper_bound, num_points);

    double x_star = x_values[0];
    double y_star = objective_function(x_star);

    for (size_t i = 0; i < num_points; i++) {
        if (objective_function(x_values[i]) < y_star) {
            x_star = x_values[i];
            y_star = objective_function(x_values[i]);
        }
    }

    free(x_values);
}

int main() {

    const int n_tests = 100;
    const int num_points = 100000;

    FILE *fp = fopen("results_brute_force.csv", "w");
    fprintf(fp, "num_points,elapsed_time\n");

    struct timespec begin, end; 
    for (int i = 1; i <= n_tests; i++) {

        clock_gettime(CLOCK_REALTIME, &begin);
        run_optimization(num_points * i);
        clock_gettime(CLOCK_REALTIME, &end);
        
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        double elapsed = seconds + nanoseconds*1e-9;

        fprintf(fp, "%d,%f\n", num_points*i, elapsed);
        printf("Test %d: %f seconds\n", num_points*i, elapsed);
    }

    fclose(fp);

    return 0;
}