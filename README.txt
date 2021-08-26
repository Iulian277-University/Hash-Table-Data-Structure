# Hash table data structure in C
Taiatu Iulian Marius - 312CB

For implementing this homework I used doubly circular linked lists
without having a node as sentinel, so it was needed to keep a pointer 
for the head of the list when iterating through.

PUT - Function 'InsertDomainInHT':
    I calculated the hash code for the domain.
    I checked if the list is empty
        If is empty
            Insert at the beginning of the list
        Else
            Check for the first element
                If the domain is already in the list (at first node)
                    Return from function
                Iterate through the list
                If I find the domain in the list
                    Return from the function
                Else
                    Call the function 'InsertDomainInList'
                        If the domain was inserted successfully in the list
                            We are good: Move to the next command from the input file
                        Else (The domain is already in the list - Don't insert it one more time)
                            Return from the function and free the memory allocated before

GET - Function 'GetDomain':
    I calculated the hash code for the domain.
    I iterated through the list and compared the domain with the domains in the list
        If it is in the list
            Return from the function with the value 1
        Else
            Return from the function with the value 0

REMOVE - Function 'RemoveDomain':
    I calculated the hash code for the domain.
    I iterated through the list and compared the domain with the domains in the list
        If I found the domain in the list
            Unlink the node from the list (keeping a pointer to that node)
            Free the memory
            Return from the function with the value 1
        Else
            Return from the function with the value 0

FIND - Function 'FindDomain':
    I calculated the hash code for the domain.
    I iterated through the list and compared the domain with the domains in the list
        If I found the domain in the list
            Return from the function with the value 1
        Else
            Return from the function with the value 0

PRINT - Function 'PrintHT':
    Print the lists from the hash table

PRINT_BUCKET - Function 'PrintBucket':
    Print a specific list (with the index in the hash table = idx_bucket)
    If idx_bucket >= number_of_lists_in_the_hash_table
        Return from the function
    Else if the list is empty
        Print 'empty'
    Else
        Print all the elements from the list
