//
// Created by Mikec on 06/11/2024.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H
#define M 100

typedef struct Node {
    int key;
    char *value;
    struct Node *next;
}Node;


typedef struct HashTable {
    Node *table[100];
} HashTable;


unsigned int hash(int key);
unsigned int universal_hash(int x);
HashTable* createHashTable();
int insert(HashTable *hashTable,int key, char *value);
int insertUniversal(HashTable *hashTable,int key, char *value);
char* search(HashTable *hashTable, int key);
char* searchUniversal(HashTable *hashTable, int key);
void delete(HashTable *hashTable, int key);
void deleteUniversal(HashTable *hashTable, int key);
void printHashTable(HashTable *hashTable);
int maxEncadenamiento(HashTable *hashTable);
int minEncadenamiento(HashTable *hashTable);



#endif //HASHTABLE_H
