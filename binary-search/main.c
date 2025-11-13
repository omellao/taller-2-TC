#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int *create_array(size_t n_elements) {
    int *array = (int*)malloc(n_elements * sizeof(int));
    for (size_t i = 0; i < n_elements; i++)
        array[i] = i;

    return array;
}


size_t binary_search(size_t n_elements, int target) {
    size_t left = 0;
    size_t right = n_elements - 1;

    while (left <= right) {
        usleep(1);
        size_t mid = left + (right - left) / 2;

        if (mid == target)
            return mid;
        else if (mid < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}


int main() {

    const int n_tests = 1000000;
    const size_t n_elements = 100000;
    const size_t target = n_elements - 7;
    
    FILE *fp = fopen("../datos/results_binary_search.csv", "w");
    fprintf(fp, "n_elements,elapsed_time\n");
    struct timespec begin, end; 
    for (int i = 1; i <= n_tests; i++) {
        size_t current_n_elements = n_elements * i;

        clock_gettime(CLOCK_REALTIME, &begin);
        size_t result = binary_search(current_n_elements, target);
        clock_gettime(CLOCK_REALTIME, &end);
        
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        double elapsed = seconds + nanoseconds*1e-9;

        fprintf(fp, "%zu,%f\n", current_n_elements, elapsed);
        printf("Elements: %lu, Time: %f seconds, Found at index: %lu\n", current_n_elements, elapsed, result);

    }
    fclose(fp);

    return 0;
}