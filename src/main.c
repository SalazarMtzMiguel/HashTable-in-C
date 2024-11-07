#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/HashTable.h"

void generarCadenaAleatoria(char *cadena, int longitud);

int main(void) {
    HashTable *hashTable = createHashTable();
    HashTable *hashTableU = createHashTable();

    srand(time(NULL));  // Inicializa la semilla para generar números aleatorios

    int longitud = 10;  // Longitud de la cadena aleatoria
    char cadena[longitud + 1];  // +1 para el carácter nulo '\0'
    char arrayStrings[100][11];

    for (int i = 0; i < 100; i++) {
        generarCadenaAleatoria(cadena, longitud);
        strcpy(arrayStrings[i], cadena);
        int i1=insert(hashTable, cadena, cadena);
        int i2=insertUniversal(hashTableU, cadena, cadena);
        printf("Insertando %s con hashing modulo: %d y hashing universal %d\n", cadena, i1, i2);
    }

    return 0;
}

void generarCadenaAleatoria(char *cadena, int longitud) {
    const char caracteres[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int numCaracteres = sizeof(caracteres) - 1;

    for (int i = 0; i < longitud; i++) {
        int indice = rand() % numCaracteres;  // Elige un índice aleatorio
        cadena[i] = caracteres[indice];      // Asigna el carácter correspondiente
    }
    cadena[longitud] = '\0';  // Añade el carácter de terminación de cadena
}