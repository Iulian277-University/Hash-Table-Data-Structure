/* Taiatu Iulian Marius - 312CB */
#include "hashTable.h"

HTable *InitHashTable(size_t max_lists, TFHash hash_code_func)
{
    // Allocate memoty for entire hash table struct
    HTable *hashTable = NULL;
    hashTable = (HTable *) calloc(sizeof(HTable), 1);
    if(hashTable == NULL)
    {
        printf("Allocation error for hash table\n");
        return NULL;
    }

    // Allocate memoty for the array of lists
    hashTable->lists_array = (TList *) calloc(max_lists, sizeof(TList));
    if(hashTable->lists_array == NULL)
    {
        printf("Allocation error for the array of lists\n");
        free(hashTable);
        return NULL;
    }

    // Complete the fields of the hash table struct
    hashTable->max_lists = max_lists;
    hashTable->hash_code_func = hash_code_func;

    return hashTable;
}

int HashCodeGenerator(void *element, int max_lists)
{
    // Cast the (void *) to TDomain
	TDomain *key_name = (TDomain *) element;
    key_name->name = ((TDomain *) element)->name;
    key_name->ip = ((TDomain *) element)->ip;

    // Calculate the hash code
    int ch_ascii_sum = 0;
    for(int i=0; i<strlen(key_name->name); ++i)
        ch_ascii_sum += key_name->name[i];

    return (ch_ascii_sum % max_lists);
}

// PRINT
void PrintHT(HTable *hashTable, TF showEl, FILE *ptr)
{
    TList cell, aux;
    for(int i=0; i<hashTable->max_lists; ++i)
    {
        cell = hashTable->lists_array[i];
        if(cell != NULL)
        {
            fprintf(ptr, "%d: ", i);
            aux = cell;
            showEl(aux->info, ptr);
            for(aux = cell->next; aux != cell; aux = aux->next)
                showEl(aux->info, ptr);
            fprintf(ptr, "\n");
        }
    }
}

// PRINT_BUCKET
void PrintBucket(HTable *hashTable, TF showEl, int idx_bucket, FILE *ptr)
{
    TList cell, aux;
    if(idx_bucket >= hashTable->max_lists)
        return;
    cell = hashTable->lists_array[idx_bucket];
    if(cell == NULL)
    {
        fprintf(ptr, "VIDA\n");
        return;
    }

    aux = cell;
    showEl(aux->info, ptr);
    for(aux = cell->next; aux != cell; aux = aux->next)
        showEl(aux->info, ptr);
    fprintf(ptr, "\n");
    
}

// FIND
int FindDomain(HTable *hashTable, void *element)
{
    int code = HashCodeGenerator(element, hashTable->max_lists);
    
    TList cell, aux;
    cell = hashTable->lists_array[code];

    if(cell == NULL)
        return 0;
    
    // First element
    aux = cell;
    if(strcmp(((TDomain *)aux->info)->name, ((TDomain *)element)->name) == 0)
        return 1;
    // The following elements
    for(aux = cell->next; aux != cell; aux = aux->next)
    {
        if(strcmp(((TDomain *)aux->info)->name, ((TDomain *)element)->name) == 0)
            return 1;
    }

    return 0;
}

// GET
int GetDomain(HTable *hashTable, void *domain, FILE *ptr)
{
    int code = HashCodeGenerator(domain, hashTable->max_lists);
    TList cell, aux;
    cell = hashTable->lists_array[code];

    // Empty list
    if(cell == NULL)
    {
        fprintf(ptr, "NULL\n");
        return 0;
    }

    // First element
    aux = cell;
    if(strcmp(((TDomain *)aux->info)->name, ((TDomain *)domain)->name) == 0)
    {
        fprintf(ptr, "%s\n", ((TDomain *)aux->info)->ip);
        return 1;
    }

    // The following elements
    for(aux = cell->next; aux != cell; aux = aux->next)
    {
        if(strcmp(((TDomain *)aux->info)->name, ((TDomain *)domain)->name) == 0)
        {
            fprintf(ptr, "%s\n", ((TDomain *)aux->info)->ip);
            return 1;
        }
    }

    fprintf(ptr, "NULL\n");
    return 0;
}

// PUT
int InsertDomainInHT(HTable *hashTable, void *domain, TFCmp cmpFunc)
{
    // Calculate the hash code for the domain
    int code = hashTable->hash_code_func(domain, hashTable->max_lists);
    TList cell, aux;
    cell = hashTable->lists_array[code];

    // Empty list
    if(cell == NULL)
    {
        // The domain was allocated before the function
        int res = InsertDomainInList(&hashTable->lists_array[code], (void *)domain);
        return res;
    }

    // Check for first element
    if(cmpFunc(cell->info, domain) == 1) 
        return -1; // It's already in the list
    
    // The following elements
    for(aux = cell->next; aux != cell; aux = aux->next)
    {
        if(cmpFunc(aux->info, domain) == 1) // It's already in the list
            return -1;
    }

    // If isn't in the list insert it
    int res = InsertDomainInList(&hashTable->lists_array[code], (void *)domain);
    if(res == 0) // Couldn't insert the domain in the list
        return -1;

    return res;
}

// REMOVE
int RemoveDomain(HTable *hashTable, void *el)
{
    // Find the domain first
    int code = HashCodeGenerator(el, hashTable->max_lists);
    
    TList cell, aux;
    cell = hashTable->lists_array[code];

    if(cell == NULL)
        return 0;
    
    // First element
    aux = cell;
    if(strcmp(((TDomain *)aux->info)->name, ((TDomain *)el)->name) == 0)
    {
        // Unlink the node from the list
        aux->next->prev = aux->prev;
        aux->prev->next = aux->next;

        // Change the beginning of the list
        if(aux->next != aux)
            hashTable->lists_array[code] = aux->next;
        else  // Only one domain in the list
            hashTable->lists_array[code] = NULL;

        // Free the memory
        free(((TDomain *)aux->info)->name);
        free(((TDomain *)aux->info)->ip);
        free((TDomain *)aux->info);
        free((TDomain *)aux);

        return 1;
    }

    // For the following elements
    for(aux = cell->next; aux != cell; aux = aux->next)
    {
        if(strcmp(((TDomain *)aux->info)->name, ((TDomain *)el)->name) == 0)
        {
            // Unlink the node from the list
            aux->next->prev = aux->prev;
            aux->prev->next = aux->next;

            // Free the memory
            free(((TDomain *)aux->info)->name);
            free(((TDomain *)aux->info)->ip);
            free((TDomain *)aux->info);
            free((TDomain *)aux);
            
            return 1;
        }
    }

    return 0;
}

void DestroyHT(HTable **hashTable)
{
    TList *cell, el, aux;

    // For each list
    for (cell = (*hashTable)->lists_array; cell < (*hashTable)->lists_array + (*hashTable)->max_lists; cell++)
    {
        // Free memory for first element in the list
        el = *cell;
        if(el != NULL)
        {
            aux = el;
            el = el->next;
            free(((TDomain *)aux->info)->name);
            free(((TDomain *)aux->info)->ip);
            free((TDomain *)aux->info);
            free(aux);
        }
        // For the others elements in the list
        while(el != *cell)
        {
            aux = el;
            el = el->next;
            free(((TDomain *)aux->info)->name);
            free(((TDomain *)aux->info)->ip);
            free((TDomain *)aux->info);
            free(aux);
        }
    }
    free((*hashTable)->lists_array);
    free(*hashTable);
    *hashTable = NULL;
}
