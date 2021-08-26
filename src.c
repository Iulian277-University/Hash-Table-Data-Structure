/* Taiatu Iulian Marius - 312CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doublyLinkedList.h"
#include "hashTable.h"

#define LINE_LENGTH 100

int main(int argc, char *argv[])
{
    int max_lists = atoi(argv[1]);
    char *input_file_name = argv[2];
    char *output_file_name = argv[3];

    HTable *hash_table = NULL;
    hash_table = (HTable *) InitHashTable(max_lists, HashCodeGenerator);
    if(hash_table == NULL)
        return -1;

    FILE *input_file = NULL;
    input_file = fopen(input_file_name, "r");
    if(input_file == NULL)
        return -1; // Couldn't open the input file
        
    FILE *output_file = NULL;
    output_file = fopen(output_file_name, "w");
    if(output_file == NULL)
        return -1; // Couldn't open the output file

    char *buffer = NULL;
    buffer = (char *) calloc(LINE_LENGTH, sizeof(char));
    if(buffer == NULL)
        return -1; // Error of allocation

    char *command = NULL;
    command = (char *) calloc(LINE_LENGTH, sizeof(char));
    if(command == NULL)
        return -1; // Error of allocation

    char *key = NULL;
    key = (char *) calloc(LINE_LENGTH, sizeof(char));
    if(key == NULL)
        return -1; // Error of allocation

    char *value = NULL;
    value = (char *) calloc(LINE_LENGTH, sizeof(char));
    if(value == NULL)
        return -1; // Error of allocation

    int index_bucket;

    // Read from input file line by line
    while(!feof(input_file))
    {
        if(fgets(buffer, LINE_LENGTH, input_file) == NULL)
            break;
        if(buffer[0] == '\n')
            break;
        if(buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';

        char *token = strtok(buffer, " ");
        strcpy(command, token);
        
        if(strcmp(command, "put") == 0)
        {
            token = strtok(NULL, " ");
            strcpy(key, token);
            token = strtok(NULL, " ");
            strcpy(value, token);
            // printf("Command: %s || Key: %s || Value: %s\n", command, key, value);

            TDomain *domain_to_insert = (TDomain *) malloc(sizeof(TDomain));
            domain_to_insert->name = (char *) malloc(LINE_LENGTH * sizeof(char));
            domain_to_insert->ip = (char *) malloc(LINE_LENGTH * sizeof(char));

            strcpy(domain_to_insert->name, key);
            strcpy(domain_to_insert->ip, value);

            int res_insert = InsertDomainInHT(hash_table, (void *) domain_to_insert, CompareDomains);
            if(res_insert == -1)
            {
                free(domain_to_insert->name);
                free(domain_to_insert->ip);
                free(domain_to_insert);
            }
            
        }
        else if(strcmp(command, "get") == 0)
        {
            token = strtok(NULL, " ");
            strcpy(key, token);
            // printf("Command: %s || Key: %s\n", command, key);

            TDomain *domain_to_get = malloc(sizeof(TDomain));
            if(domain_to_get == NULL)
                return -1;
            domain_to_get->name = (char *) malloc(LINE_LENGTH * sizeof(char));
            if(domain_to_get == NULL)
            {
                free(domain_to_get);
                return -1;
            }
            strcpy(domain_to_get->name, key); 
            GetDomain(hash_table, (void *) domain_to_get, output_file);
            free(domain_to_get->name);
            free(domain_to_get);
        }
        else if(strcmp(command, "remove") == 0)
        {
            token = strtok(NULL, " ");
            strcpy(key, token);
            // printf("Command: %s || Key: %s\n", command, key);

            TDomain *domain_to_remove = malloc(sizeof(TDomain));
            if(domain_to_remove == NULL)
                return -1;
            domain_to_remove->name = (char *) malloc(LINE_LENGTH * sizeof(char));
            if(domain_to_remove == NULL)
            {
                free(domain_to_remove);
                return -1;
            }
            strcpy(domain_to_remove->name, key); 
            RemoveDomain(hash_table, (void *) domain_to_remove);
            free(domain_to_remove->name);
            free(domain_to_remove);
        }
        else if(strcmp(command, "find") == 0)
        {
            token = strtok(NULL, " ");
            strcpy(key, token);
            // printf("Command: %s || Key: %s\n", command, key);

            TDomain *domain_to_find = malloc(sizeof(TDomain));
            if(domain_to_find == NULL)
                return -1;
            domain_to_find->name = (char *) malloc(LINE_LENGTH * sizeof(char));
            if(domain_to_find == NULL)
            {
                free(domain_to_find);
                return -1;
            }
            strcpy(domain_to_find->name, key); 

            if(FindDomain(hash_table, (void *)domain_to_find))
                fprintf(output_file, "True\n");
            else
                fprintf(output_file, "False\n");
            free(domain_to_find->name);
            free(domain_to_find);
        }
        else if(strcmp(command, "print") == 0)
        {
            // printf("Command: %s\n", command);
            PrintHT(hash_table, ShowDomain, output_file);
        }
        else if(strcmp(command, "print_bucket") == 0)
        {
            token = strtok(NULL, " ");
            strcpy(value, token);
            if(value[strlen(value) - 1] == '\n')
                value[strlen(value) - 1] = '\0';
            index_bucket = atoi(value);
            // printf("Command: %s || Value: %s\n", command, value);
            PrintBucket(hash_table, ShowDomain, index_bucket, output_file);
        }
        
    }

    DestroyHT(&hash_table);

    free(buffer);
    free(command);
    free(key);
    free(value);

    fclose(input_file);
    fclose(output_file);
    
    return 0;
}
