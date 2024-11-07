#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/HashTable.h"

void generarCadenaAleatoria(char *cadena, int longitud);

unsigned int stringToInt(const char *word);

void generarNumerosGaussianos(int *numeros, int cantidad, double mu, double sigma);

void guardarNumerosEnCSV(const char *filename, int key, int hash, int hashU, int writeHeader);

void generarCadenaAleatoria(char *cadena, int longitud) {
    const char caracteres[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int numCaracteres = sizeof(caracteres) - 1;

    for (int i = 0; i < longitud; i++) {
        int indice = rand() % numCaracteres; // Choose a random index
        cadena[i] = caracteres[indice]; // Assign the corresponding character
    }
    cadena[longitud] = '\0'; // Add the null terminator
}

unsigned int stringToInt(const char *word) {
    unsigned int sum = 0;
    while (*word) {
        sum += (unsigned int) (*word);
        word++;
    }
    return sum;
}

int main(void) {
    HashTable *hashTable = createHashTable();
    HashTable *hashTableU = createHashTable();

    srand(time(NULL)); // Initialize the seed for random number generation

    int longitud = 10; // Length of the random string
    char cadena[longitud + 1]; // +1 for the null character '\0'
    char arrayStrings[100][11];

    for (int i = 0; i < 100; i++) {
        generarCadenaAleatoria(cadena, longitud);
        strcpy(arrayStrings[i], cadena);
        unsigned int key = stringToInt(cadena);
        int i1 = insert(hashTable, key, cadena);
        int i2 = insertUniversal(hashTableU, key, cadena);
        printf("Insertando %s con key %d hashing modulo: %d y hashing universal: %d\n", cadena, key, i1, i2);
    }

    int numeros[1000];
    generarNumerosGaussianos(numeros, 1000, 50, 40);

    // Write header once
    guardarNumerosEnCSV("../tests/numeros.csv", 0, 0, 0, 1);
    hashTable = createHashTable();
    hashTableU = createHashTable();
    for (int i = 0; i < 1000; i++) {
        printf("%d, ", numeros[i]);
        int i1 = insert(hashTable, numeros[i], "numero");
        int i2 = insertUniversal(hashTableU, numeros[i], "numero");
        guardarNumerosEnCSV("../tests/numeros.csv", numeros[i], hash(numeros[i]), universal_hash(numeros[i]), 0);
    }
    printf("\n");

    printf("El maximo encadenamiento fue de: %d\n", maxEncadenamiento(hashTable));
    printf("El minimo encadenamiento fue de: %d\n", minEncadenamiento(hashTable));
    printf("El maximo encadenamiento fue de: %d\n", maxEncadenamiento(hashTableU));
    printf("El minimo encadenamiento fue de: %d\n", minEncadenamiento(hashTableU));

    printf("\n%s", "Imprimiendo tabla hash\n");
    printHashTable(hashTable);
    printf("\n%s", "Imprimiendo tabla hash\n");
    printHashTable(hashTableU);
    /*HashTable *hashTable3 = createHashTable();
    int i1 = insert(hashTable3, stringToInt("uno"), "uno");
    int i2 = insert(hashTable3, stringToInt("dos"), "dos");
    int i3 = insert(hashTable3, stringToInt("tres"), "tres");
    int i4 = insert(hashTable3, stringToInt("sod"), "sod");
    printHashTable(hashTable3);
    delete(hashTable3, stringToInt("uno"));
    printHashTable(hashTable3);
    printf("Si existe %s\n", search(hashTable3, stringToInt("dos")));
    delete(hashTable3, stringToInt("dos"));
    printHashTable(hashTable3);*/

    return 0;
}

void generarNumerosGaussianos(int *numeros, int cantidad, double mu, double sigma) {
    srand(time(NULL));
    for (int i = 0; i < cantidad; i++) {
        double u1 = (double) rand() / RAND_MAX;
        double u2 = (double) rand() / RAND_MAX;
        double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
        double gauss = mu + z0 * sigma;
        numeros[i] = ((int) round(gauss) < 0) ? (int) round(gauss) * -1 : (int) round(gauss);
    }
}

void guardarNumerosEnCSV(const char *filename, int key, int hash, int hashU, int writeHeader) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error abriendo el archivo CSV");
        return;
    }

    if (writeHeader) {
        fprintf(file, "Key,Hash,HashU\n");
    } else {
        fprintf(file, "%d,%d,%d\n", key, hash, hashU);
    }

    fclose(file);
}
