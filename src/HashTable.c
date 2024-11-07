//
// Created by Mikec on 06/11/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/HashTable.h"

#define PRIMO 101
#define M 100

unsigned int hash(int key) {
    return key % M;
}

unsigned int universal_hash(int x) {
    return ((97 * x + 89) % PRIMO) % M;
}

HashTable* createHashTable() {
    HashTable *hashTable = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < M; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

int insert(HashTable *hashTable,int key, char *value) {
    unsigned int index = hash(key);
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = strdup(value);
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
    return index;
}

int insertUniversal(HashTable *hashTable,int key, char *value) {
    unsigned int index = universal_hash(key);
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = strdup(value);
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
    return index;
}

char* search(HashTable *hashTable,int key) {
    unsigned int index = hash(key);
    Node *node = hashTable->table[index];
    while (node != NULL) {
        if (node->key == key) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

char* searchUniversal(HashTable *hashTable,int key) {
    unsigned int index = universal_hash(key);
    Node *node = hashTable->table[index];
    while (node != NULL) {
        if (node->key == key) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

void delete(HashTable *hashTable,int key) {
    unsigned int index = hash(key);
    Node *node = hashTable->table[index];
    Node *prev = NULL;
    while (node != NULL && node->key != key) {
        prev = node;
        node = node->next;
    }
    if (node == NULL) {
        return; // Key not found
    }
    if (prev == NULL) {
        hashTable->table[index] = node->next;
    } else {
        prev->next = node->next;
    }
    free(node->value);
    free(node);
}

void deleteUniversal(HashTable *hashTable,int key) {
    unsigned int index = universal_hash(key);
    Node *node = hashTable->table[index];
    Node *prev = NULL;
    while (node != NULL && node->key != key) {
        prev = node;
        node = node->next;
    }
    if (node == NULL) {
        return; // Key not found
    }
    if (prev == NULL) {
        hashTable->table[index] = node->next;
    } else {
        prev->next = node->next;
    }
    free(node->value);
    free(node);
}
void printHashTable(HashTable *hashTable) {
    for (int i = 0; i < M; i++) {
        printf("Index %d: ", i);
        Node *node = hashTable->table[i];
        while (node != NULL) {
            printf("(%d, %s) -> ", node->key, node->value);
            node = node->next;
        }
        printf("NULL\n");
    }
}

int maxEncadenamiento(HashTable *hashTable) {
    int max = 0;
    for (int i = 0; i < M; i++) {
        int count = 0;
        Node *node = hashTable->table[i];
        while (node != NULL) {
            count++;
            node = node->next;
        }
        if (count > max) {
            max = count;
        }
    }
    return max;
}

int minEncadenamiento(HashTable *hashTable) {
    int min = M; // Start with the maximum possible value
    for (int i = 0; i < M; i++) {
        int count = 0;
        Node *node = hashTable->table[i];
        while (node != NULL) {
            count++;
            node = node->next;
        }
        if (count < min) {
            min = count;
        }
    }
    return min;
}