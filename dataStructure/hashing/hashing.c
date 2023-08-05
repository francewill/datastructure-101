
#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Function that prints the data of the hash table
void printTable(HASH_TABLE *H)
{
    if (isEmpty(H))
    {
        printf("*empty\n");
        return;
    }

    for (int index = 0; index < H->tableSize; index++)
    {
        printf("Cell#%d: ", index);
        if (H->list[index])
        {
            printf("%s\n", H->list[index]);
        }
        else
        {
            printf("*empty*\n");
        }
    }
}

/*
 *  function: createHashTable
 *  requirements:
 * non-zero integer (tableSize)
 *  results:
 * creates a hash table
 * initializes fields
 * initializes array of strings
 * returns a non null HASH_TABLE_PTR
 */
HASH_TABLE *createHashTable(uint tableSize)
{
    HASH_TABLE *H = (HASH_TABLE *)malloc(sizeof(HASH_TABLE));  
    H->tableSize = tableSize;  // max size
    H->size = 0;  // current size
    H->list = (STRING_ARRAY_PTR)malloc(sizeof(STRING) * tableSize);
    for (int i = 0; i < tableSize; i++)  // initialize the elements of list as null
    {
        H->list[i] = NULL;
    }
    return H;
}


uint isEmpty(HASH_TABLE *H)  // check if hash tablle is empty
{
    if (H->size == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint isFull(HASH_TABLE *H)  // check if hash table is full
{
    if (H->size == H->tableSize)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int asciiCounter(STRING word)  // a function that will count the total ascii of a string
{
    int total = 0;
    for (int i = 0; i < strlen(word); i++)  // for each character get it's equivalent ascii then add it to total
    {
        total = total + (int)(word[i]);
    }
    return total;
}

/*
 *  function: put
 *  requirements:
      * a non null HASH_TABLE_PTR
      * a non null NODE_PTR
      * non-full hash table
 *  results:
      * inserts node at the list at position identified by
        the hash value of the key.
*/
int secondHash(STRING key, int computedKey)  // function for our second hash function
{
    int ans = 23 - computedKey % strlen(key);
    return ans;
}

void put(HASH_TABLE *H, STRING key, STRING data)  // this is responsible for putting values in our hash map
{
    int i = 0, index, computedKey;
    if (isFull(H))  // check first if hash table is full
    {
        printf("\nHash tables is full!\n");
    }
    else
    {
        computedKey = asciiCounter(key);  // get the computed key by using the asciiCounter function
        index = ((computedKey % H->tableSize) + i * secondHash(key, computedKey)) % H->tableSize; // Calculate for index
        STRING temp = (STRING)malloc(sizeof(char) * strlen(data));  // create temp string holder
        strcpy(temp, data);
        if (H->list[index] == NULL)  // if null then automatically put it in the hashtable
        {
            H->list[index] = temp;
            printf("\nB\n");
        }
        else  // probes through the table so we can find next available space
        {
            do
            {
                i++;
                index = ((computedKey % H->tableSize) + i * secondHash(key, computedKey)) % H->tableSize;
            } while (H->list[index] != NULL); // just find the next available space
            H->list[index] = temp;  // when it got here expect that it already found an available space
        }
        H->size++;  // increase size
    }
}

/*
 *  function: find
 *  requirements:
 * a non null HASH_TABLE_PTR
 * a non null string
 * non empty string
 *  results:
 * finds the node identified by key
 * returns the string data if found
 * returns NULL if not found
 */
STRING find(HASH_TABLE *H, STRING key, STRING data)
{
    if (H->size == 0)
    {
        printf("\nHashmap is empty!\n");
    }
    else
    {
        int i = 0, index, computedKey;
        computedKey = asciiCounter(key);
        index = ((computedKey % H->tableSize) + i * secondHash(key, computedKey)) % H->tableSize;
        if (H->list[index] == NULL)
        {
            printf("\nAAAAAAAAAAA\n");
            return NULL;
        }
        else
        {
            if (strcmp(H->list[index], data) == 0)
            {
                return H->list[index];
            }
            else
            {
                printf("\nBBBBBBBBBBB\n");
                while (H->list[index] != NULL)
                {
                    if (strcmp(H->list[index], data) == 0)
                    {

                        printf("\nHERE IS YOUR SHIT: %s\n", H->list[index]);
                        return H->list[index];
                    }
                    else if (H->list[index] == NULL)
                    {
                        return NULL;
                    }
                    i++;
                    index = ((computedKey % H->tableSize) + i * secondHash(key, computedKey)) % H->tableSize;
                }
            }
        }
    }
}

/*
 *  function: erase
 *  requirements:
 * a non null HASH_TABLE_PTR
 * a non null string
 * non empty string
 *  results:
 * finds the node identified by key
 *   if found, delete the node and return the data
 *   otherwise, return NULL
 */
STRING erase(HASH_TABLE *H, STRING key, STRING data)
{
}

/*
 *  function: destroy
 *  requirements:
 * a non null HASH_TABLE_PTR
 *  results:
 * deletes all nodes
 * frees all allocated memory for nodes
 */
void destroy(HASH_TABLE *H)
{
}

int main()
{

    char command;
    STRING key;
    STRING data;
    STRING result;

    uint tsize;
    HASH_TABLE *H;

    // get table size then maxsize
    scanf("%d\n", &tsize);
    H = createHashTable(tsize);
    // assume max key size is 20
    key = (STRING)malloc(sizeof(char) * 20);
    key[0] = '\0';
    // assume max data size is 100
    data = (STRING)malloc(sizeof(char) * 100);
    data[0] = '\0';

    while (1)
    {
        scanf(" %c", &command);

        switch (command)
        {
        case '+':
            scanf(" k:%s d:%s", key, data);
            printf("Inserting data %s with key %s\n", data, key);
            put(H, key, data);
            break;
        case '-':
            scanf(" k:%s d:%s", key, data);
            printf("Deleting data with key %s\n", key);
            result = erase(H, key, data);
            // result is unused. print if u want
            break;
        case '?':
            scanf(" k:%s d:%s", key, data);
            printf("Searching data with key: %s. Location: %p\n", key, find(H, key, data));
            // (nil) means NULL pointer
            break;
        case 'p':
            printf("Hash Table: \n");
            printTable(H);
            printf("\n");
            break;
        case 'E':
            printf("Hash table %s empty.\n", isEmpty(H) ? "is" : "is not");
            break;
        case 'F':
            printf("Hash table %s full.\n", isFull(H) ? "is" : "is not");
            break;
        case 'C':
            printf("Deleting all contents.\n");
            destroy(H);
            break;
        case 'Q':
            free(key);
            free(data);
            destroy(H); // ensure deletion
            free(H->list);
            free(H);
            return 0;
        default:
            printf("Unknown command: %c\n", command);
        }
    }

    return 0;
}
