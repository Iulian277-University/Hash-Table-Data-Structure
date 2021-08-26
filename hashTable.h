/* Taiatu Iulian Marius - 312CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doublyLinkedList.h"

#ifndef _HASH_TABLE_
#define _HASH_TABLE_

typedef int (* TFHash)(void *, int); // Function to calculate the hash code
typedef void (* TF)(void *, FILE *); // Function to print an element
typedef int (*TFCmp)(void *, void *); // Function to compare 2 elements

typedef struct
{
    size_t max_lists; // Maxim max_lists lists
    TFHash hash_code_func; // Function to calulate the hash code 
    TList *lists_array; // Array of lists
}HTable;


HTable *InitHashTable(size_t max_lists, TFHash hash_code_func); // Create a hash table
int HashCodeGenerator(void *element, int max_lists); // Generate a hash code
int FindDomain(HTable *hashTable, void *element); // Find a domain in a hash table
int GetDomain(HTable *hashTable, void *domain, FILE *ptr); // Return the domain if it's in the hash table
int RemoveDomain(HTable *hashTable, void *el); // Remove a domain from the hash table
int InsertDomainInHT(HTable *hashTable, void *domain, TFCmp cmpFunc); // Insert an elemenent in the hash table
void PrintHT(HTable *hashTable, TF showEl, FILE *ptr); // Print the entire hash table
void PrintBucket(HTable *hashTable, TF showEl, int idx_bucket, FILE *ptr); // Print a specific list from the hash table
void DestroyHT(HTable **hashTable); // Destroy the hash table

#endif