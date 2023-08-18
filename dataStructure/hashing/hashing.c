
#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

HASH_TABLE *rehashing(HASH_TABLE **H);

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
            printf("%s\n", H->list[index]->data);
        }
        else
        {
            printf("*empty*\n");
        }
    }
}

NODE *createNode(STRING key, STRING data)
{
    NODE *temp = (NODE *)malloc(sizeof(NODE));
    temp->key = (STRING)malloc(sizeof(char) * strlen(key));
    temp->data = (STRING)malloc(sizeof(char) * strlen(data));
    strcpy(temp->key, key);
    strcpy(temp->data, data);
    return temp;
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
    H->tableSize = tableSize; // max size
    H->size = 0;              // current size
    H->list = (NODE **)malloc(sizeof(NODE *) * tableSize);

    for (int i = 0; i < tableSize; i++) // initialize the elements of list as null
    {
        NODE *temp = NULL;
        H->list[i] = temp;
    }

    return H;
}

uint isEmpty(HASH_TABLE *H) // check if hash tablle is empty
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

uint isFull(HASH_TABLE *H) // check if hash table is full
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

int asciiCounter(STRING word) // a function that will count the total ascii of a string
{
    int total = 0;
    for (int i = 0; i < strlen(word); i++) // for each character get it's equivalent ascii then add it to total
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
int secondHash(STRING key, int computedKey) // function for our second hash function
{
    int ans = 23 - computedKey % strlen(key);
    return ans;
}

void put(HASH_TABLE *H, STRING key, STRING data) // this is responsible for putting values in our hash map
{
    int i = 0, index, computedKey;
    if (isFull(H)) // check first if hash table is full
    {
        printf("\nHash tables is full!\n");
    }
    else
    {
        computedKey = asciiCounter(key);                                                          // get the computed key by using the asciiCounter function
        index = ((computedKey % H->tableSize) + i * secondHash(key, computedKey)) % H->tableSize; // Calculate for index
        // STRING temp = (STRING)malloc(sizeof(char) * strlen(data));                                // create temp string holder
        // strcpy(temp, data);

        NODE *temp = createNode(key, data);

        if (H->list[index] == NULL) // if null then automatically put it in the hashtable
        {
            H->list[index] = temp;
        }
        else // probes through the table so we can find next available space
        {
            do
            {
                i++;
                index = ((computedKey % H->tableSize) + i * secondHash(key, computedKey)) % H->tableSize;
            } while (H->list[index] != NULL && strcmp(H->list[index]->data, "*empty*") != 0); // just find the next available space
            H->list[index] = temp;                                                            // when it got here expect that it already found an available space
        }
        H->size++; // increase size
    }
    rehashing(&H);
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
    if (isEmpty(H)) // check if empty
    {
        printf("\nHashmap is empty!\n");
    }
    else // as you can notice it is similar in put function
    {
        int i = 0, index, computedKey;
        computedKey = asciiCounter(key);
        index = ((computedKey % H->tableSize) + i * secondHash(key, computedKey)) % H->tableSize;
        if (H->list[index] == NULL || strcmp(H->list[index]->data, "*empty*") == 0) // if null then automatically send null since input does not exist
        {
            return NULL;
        }
        else
        {
            if (strcmp(H->list[index]->data, data) == 0) // compare the strings
            {
                return H->list[index]->data;
            }
            else // if not same then probe to the next position if that next position is null then input does not exist in hash table
            {
                while (H->list[index] != NULL && strcmp(H->list[index]->data, "*empty*") != 0)
                {
                    if (strcmp(H->list[index]->data, data) == 0)
                    {
                        return H->list[index]->data;
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
    int computedAscii, i = 0, index;
    if (isEmpty(H)) // check if empty
    {
        printf("\nHash table is empty!\n");
    }
    else
    {
        STRING toDel = find(H, key, data); // find the given node then store it to del
        if (toDel == NULL)                 // if null then it does not exist
        {
            printf("\nDoes not exist!\n");
            return NULL;
        }
        else
        {
            computedAscii = asciiCounter(key);                                                              // check the total ascii
            index = ((computedAscii % H->tableSize) + (i * secondHash(key, computedAscii))) % H->tableSize; // calculate the index
            int checker = strcmp(toDel, H->list[index]->data);                                              // check if same
            if (checker == 0)
            {
                strcpy(H->list[index]->data, "*empty*"); // if same then delete it using lazy deletion
            }
            else
            {

                do
                {

                    i++; // probe to the next space
                    index = ((computedAscii % H->tableSize) + (i * secondHash(key, computedAscii))) % H->tableSize;
                    checker = strcmp(toDel, H->list[index]->data);
                } while (checker != 0);
                strcpy(H->list[index]->data, "*empty*");
            }
            H->size--; // Decrement size
            return data;
        }
    }
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
    if (isEmpty(H))
    {
        printf("\nHash table is empty!\n");
    }
    else
    {
        for (int i = 0; i < H->tableSize; i++) // replace all nodes to null
        {
            if (H->list[i] != NULL)
            {
                if (strcmp(H->list[i]->data, "*empty*") != 0)
                {
                    NODE *temp = H->list[i];
                    free(temp);
                    H->list[i] = NULL;
                    H->size--;
                    printf("\nSize = %d\n", H->size);
                }
                else
                {
                    NODE *temp = H->list[i];
                    free(temp);
                    H->list[i] = NULL;
                }
            }
            else
            {
                continue;
            }
        }
    }
}
HASH_TABLE *rehashing(HASH_TABLE **H)
{
    int newSize;
    float loadFactor = (float)(*H)->size / (*H)->tableSize;
    if (loadFactor < 0.7) // 
    {
        return NULL;
    }
    else
    {
        // printf("\nRehashed\n");
        newSize = 1.3 * (*H)->tableSize;
        if(newSize%2==0){
            newSize++;
        }
        HASH_TABLE *temp = createHashTable(newSize);  // make a temporary hash table
        // printf("\nSIZE: %d\n", newSize);

        for (int i = 0; i < (*H)->tableSize; i++) // transfer all the data to temp
        {
            if ((*H)->list[i] != NULL)
            {
                if (strcmp((*H)->list[i]->data, "*empty*") != 0)
                {
                    put(temp, (*H)->list[i]->key, (*H)->list[i]->data);
                }
            }
            else
            {
                continue;
            }
        }

        return temp;
    }
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
            HASH_TABLE *temp = rehashing(&H);
            if (temp != NULL)  // rehashing!
            {
                destroy(H); 
                free(H->list);
                free(H);
                H = temp;
            }

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
