//
// Created by Mikec on 06/11/2024.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H
#define M 100;

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
unsigned int stringToInt(const char *word);
int insert(HashTable *hashTable,char* word, char *value);
int insertUniversal(HashTable *hashTable,char* word, char *value);
char* search(HashTable *hashTable, char* word);
char* searchUniversal(HashTable *hashTable, char* word);
void delete(HashTable *hashTable, char* word);
void deleteUniversal(HashTable *hashTable, char* word);



#endif //HASHTABLE_H
