/* Taiatu Iulian Marius - 312CB */
#include "doublyLinkedList.h"

void ShowDomain(void *element, FILE *ptr)
{
    TDomain *domain = (TDomain *) element;
    fprintf(ptr, "%s ", domain->ip);
}

int CompareDomains(void *e1, void *e2)
{
    TDomain *domain1 = (TDomain *) e1;
    TDomain *domain2 = (TDomain *) e2;

    if(strcmp(domain1->name, domain2->name)) // Different names
        return 0;
    if(strcmp(domain1->ip, domain2->ip)) // Different IPs
        return 0;

    return 1; // The same
}

int InsertDomainInList(TList *List, void *domain)
{
    TDomain *domain_to_insert = (TDomain *) domain;
    TList aux = (TList) malloc(sizeof(TCell));
    if(aux == NULL)
        return -1;

    // Empty list
    if(*List == NULL)
    {
        *List = aux;
        (*List)->info = (void *) domain;
        (*List)->next = *List;
        (*List)->prev = *List;
        return 1;
    }

    // For the first element
    TList cell = *List;
    if(strcmp(domain_to_insert->name, ((TDomain *)cell->info)->name) < 0)
    {
        // Insert at the beginning of the list
        aux->info = (void *) domain;
        aux->next = cell;
        aux->prev = cell->prev;
        cell->prev->next = aux;
        cell->prev = aux;
        *List = aux;

        return 1;
    }

    // Compare the domain starting from the second element
    cell = *List;
    TList element = cell->next; 
    while(element->next != cell && strcmp(domain_to_insert->name, ((TDomain *)element->info)->name) > 0)
        element = element->next;

    
    if(strcmp(domain_to_insert->name, ((TDomain *)element->info)->name) < 0)
        element = element->prev; // For inserting before the element

    // Insert after the element (or element->prev)
    aux->info = (void *) domain;
    aux->next = element->next;
    element->next->prev = aux;
    aux->prev = element;
    element->next = aux;

    return 1;
}
