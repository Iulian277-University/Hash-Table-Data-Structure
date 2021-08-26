/* Taiatu Iulian Marius - 312CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _DOUBLY_LINKED_LIST_
#define _DOUBLY_LINKED_LIST_

typedef struct node
{
    void *info;
    struct node *next, *prev;
}TCell, *TList;

typedef struct
{
    char *name;
    char *ip;
}TDomain;

void ShowDomain(void *element, FILE *ptr); // Print an element of type TDomain
int CompareDomains(void *e1, void *e2); // Compare 2 elements of type TDomain
int InsertDomainInList(TList *List, void *domain); // Insert a domain in the list

#endif