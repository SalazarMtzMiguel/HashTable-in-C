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

unsigned int stringToInt(const char *word) {
    unsigned int sum = 0;
    while (*word) {
        sum += (unsigned int)(*word);
        word++;
    }
    return sum;
}

int insert(HashTable *hashTable,char* word, char *value) {
    unsigned int key = stringToInt(word);
    unsigned int index = hash(key);
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = strdup(value);
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
    return index;
}

int insertUniversal(HashTable *hashTable,char* word, char *value) {
    unsigned int key = stringToInt(word);
    unsigned int index = universal_hash(key);
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = strdup(value);
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
    return index;
}

char* search(HashTable *hashTable, char* word) {
    unsigned key = stringToInt(word);
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

char* searchUniversal(HashTable *hashTable, char* word) {
    unsigned key = stringToInt(word);
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

void delete(HashTable *hashTable, char* word) {
    unsigned int key = stringToInt(word);
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

void deleteUniversal(HashTable *hashTable, char* word) {
    unsigned int key = stringToInt(word);
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