#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estructura que representa una tabla hash
// La tabla hash almacena pares clave-valor con acceso en tiempo constante O(1)
struct HashTable {
    int size;   // Tamanio de la tabla
    int *table; // Arreglo que almacena los valores
};

// Funcion hash que mapea una clave a un indice en la tabla
// Utiliza el metodo de division: hash(key) = key mod size
// Complejidad temporal: O(1)
// Parametros:
//   - key: clave a mapear
//   - size: tamanio de la tabla hash
// Retorna: indice correspondiente en la tabla
size_t hash_function(int key, int size) {
    return key % size;
}

// Crea e inicializa una nueva tabla hash
// Reserva memoria dinamica para la estructura y el arreglo interno
// Parametro: size - tamanio de la tabla a crear
// Retorna: puntero a la tabla hash creada
struct HashTable* create_hash_table(int size) {
    struct HashTable *ht = (struct HashTable*)malloc(sizeof(struct HashTable));
    ht->size = size;
    ht->table = (int*)malloc(size * sizeof(int));
    return ht;
}

// Libera la memoria ocupada por una tabla hash
// Debe llamarse cuando ya no se necesita la tabla para evitar fugas de memoria
// Parametro: ht - puntero a la tabla hash a destruir
void destroy_hash_table(struct HashTable *ht) {
    free(ht->table); // Libera el arreglo interno
    free(ht);        // Libera la estructura
}

// Inserta una clave en la tabla hash
// Utiliza la funcion hash para determinar la posicion de insercion
// Complejidad temporal: O(1) en promedio
// Nota: Esta implementacion simple no maneja colisiones
// Parametros:
//   - ht: puntero a la tabla hash
//   - key: clave a insertar
void insert(struct HashTable *ht, int key) {
    size_t index = hash_function(key, ht->size); // Calcula el indice
    ht->table[index] = key;                       // Almacena la clave
}

// Funcion principal que ejecuta las pruebas de rendimiento
int main() {

    // Cantidad de elementos a insertar en la tabla
    size_t n_elements = 1000000;

    // Crea tabla hash con capacidad para n_elements
    struct HashTable *ht = create_hash_table(n_elements);

    // Abre archivo CSV para guardar resultados
    FILE *fp = fopen("../datos/results_hash_table.csv", "w");
    fprintf(fp, "n_elements,elapsed_time\n"); 

    // Inserta elementos uno por uno y mide el tiempo de cada insercion
    for (size_t i = 0; i < n_elements; i++) {
        struct timespec begin, end; // Estructuras para medir tiempo
        
        // Registra tiempo inicial
        clock_gettime(CLOCK_REALTIME, &begin);
        insert(ht, i); // Inserta elemento i en la tabla
        // Registra tiempo final
        clock_gettime(CLOCK_REALTIME, &end);

        // Calcula tiempo transcurrido en segundos con alta precision
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        double elapsed = seconds + nanoseconds*1e-9;
        
        // Guarda resultados en archivo CSV con 13 decimales de precision
        fprintf(fp, "%zu,%.13f\n", i, elapsed);
        printf("Inserted: %zu, Time: %.13f seconds\n", i, elapsed);
    }
    fclose(fp);

    destroy_hash_table(ht);
    return 0;
}