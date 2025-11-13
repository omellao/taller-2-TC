#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct HashTable {
    int size;
    int *table;
};

size_t hash_function(int key, int size) {
    return key % size;
}

struct HashTable* create_hash_table(int size) {
    struct HashTable *ht = (struct HashTable*)malloc(sizeof(struct HashTable));
    ht->size = size;
    ht->table = (int*)malloc(size * sizeof(int));
    return ht;
}

void destroy_hash_table(struct HashTable *ht) {
    free(ht->table);
    free(ht);
}

void insert(struct HashTable *ht, int key) {
    size_t index = hash_function(key, ht->size);
    ht->table[index] = key;
}

int main() {

    size_t n_elements = 1000000;

    struct HashTable *ht = create_hash_table(n_elements); // A large prime number

    FILE *fp = fopen("../datos/results_hash_table.csv", "w");
    fprintf(fp, "n_elements,elapsed_time\n");

    for (size_t i = 0; i < n_elements; i++) {
        struct timespec begin, end;
        clock_gettime(CLOCK_REALTIME, &begin);
        insert(ht, i);
        clock_gettime(CLOCK_REALTIME, &end);

        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        double elapsed = seconds + nanoseconds*1e-9;
        fprintf(fp, "%zu,%.13f\n", i, elapsed);
        printf("Inserted: %zu, Time: %.13f seconds\n", i, elapsed);
    }
    fclose(fp);

    destroy_hash_table(ht);
    return 0;
}