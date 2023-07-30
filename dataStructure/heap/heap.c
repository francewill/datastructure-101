#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

int left(int index)
{
    return (2 * index);
}

int right(int index)
{
    return (2 * index + 1);
}

int parent(int index)
{
    return (index / 2);
}

/*
 *  CREATE HEAP
 *  requirements: none
 *  results:
      initializes fields of the structure
      returns the created heap
*/
HEAP *createHeap(int maxSize)
{
    HEAP *H = (HEAP *)malloc(sizeof(HEAP));
    H->maxSize = maxSize;
    H->size = 0;
    H->heap = (int *)malloc(sizeof(int) * (maxSize + 1));
    return H;
}

/*
 *  IS FULL
 *  requirements: none
 *  results:
      return 1 if the heap is full
      otherwise return 0
*/
int isFull(HEAP *H)
{
    if (H->size == H->maxSize)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
 *  IS EMPTY
 *  requirements: none
 *  results:
      return 1 if the heap is empty
      otherwise return 0
*/
int isEmpty(HEAP *H)
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

/*
 *  CLEAR
 *  requirements:
      a non-null HEAP pointer
      a non-empty *heap
 *  results:
      deletes all the items in the heap
*/
void clear(HEAP *H)
{
}

/*
 *  INSERT
 *  requirements:
      a non-null HEAP pointer
      a non-full *heap
 *  results:
      inserts `key` to the MIN HEAP `heap`
*/
void insert(HEAP *H, int key)
{
    if (isFull(H))
    {
        printf("\nHeap is full!\n");
    }
    else
    {
        int *array = H->heap;
        int i = H->size + 1;
        array[i] = key;
        for (i; i != 1; i = parent(i))
        {
            if(H->size==0){
                continue;
            }
            if(key<array[parent(i)]){
                array[i] = array[parent(i)];
                array[parent(i)] = key;
            }
        }
        H->size++;
    }
}

/*
 *  DELETE M
 *  requirements:
      a non-null HEAP pointer
      a non-empty *heap
 *  results:
        removes the minimum value (root) from the MIN HEAP `heap`
      returns the deleted value
*/
int deleteM(HEAP *H)
{
}

/*
 *  HEAP SORT
 *  requirements:
      a non-null HEAP pointer
      a non-empty *heap
 *  results:
        returns an array containing the sorted (descending order) values of the MIN HEAP `heap`
        IMPORTANT: MUST NOT MODIFY ORIGINAL HEAP
*/
int *heapSort(HEAP *H)
{
}

void printHeapHelper(HEAP *H, int index, int tabs)
{
    if (index > H->size)
        return;
    else
    {
        printHeapHelper(H, right(index), tabs + 1);
        for (int i = 0; i < tabs; i++)
            printf("\t");
        printf("%d\n", H->heap[index]);
        printHeapHelper(H, left(index), tabs + 1);
    }
}

void printHeap(HEAP *H)
{
    if (H != NULL && H->size > 0)
    {
        printHeapHelper(H, 1, 0);
    }
    else
    {
        printf("Empty heap!\n");
    }
}

// IMPLEMENT FUNCTIONS HERE

int main()
{

    char command;
    int key, result, type;
    int *sorted;

    HEAP *H = createHeap(30);

    while (1)
    {
        scanf(" %c", &command);

        switch (command)
        {
        case '+':
            scanf("%d", &key);
            printf("Inserting key: %d...\n", key);
            insert(H, key);
            break;
        case '-':
            printf("Removing root from tree...\n");
            result = deleteM(H); // result is unused
            break;
        case 'p':
            printf("Printing the heap (rotated +90 degrees)...\n");
            printHeap(H);
            printf("\n");
            break;
        case 'E':
            printf("Heap %s empty.\n", isEmpty(H) ? "is" : "is not");
            break;
        case 'F':
            printf("Heap %s full.\n", isFull(H) ? "is" : "is not");
            break;
        case 'C':
            printf("Removing all contents...\n");
            clear(H);
            break;
        /* uncomment this for postlab
        case '~':
            printf("The sorted version of the heap:\n");
            sorted = heapSort(H);
            for(key=1; key <= H->size; key++)
                printf("%4d", sorted[key]);
            printf("\n");
            free(sorted);
            break;
        */
        case 'Q':
            free(H->heap);
            free(H);
            return 0;
        default:
            printf("Unknown command: %c\n", command);
        }
    }

    return 0;
}