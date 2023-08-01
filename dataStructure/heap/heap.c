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
    for (int i = H->size; i != 0; i--) // Every element will be deleted
    {
        deleteM(H);
    }
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
    if (isFull(H)) // if heap is full
    {
        printf("\nHeap is full!\n");
    }
    else
    {
        int *array = H->heap;
        int i = H->size + 1;           // we use 1 indexing
        array[i] = key;                // always access the first available space which is after the last element
        for (i; i != 1; i = parent(i)) // percolate up
        {
            if (H->size == 0) // Just continue for the first element (root)
            {
                continue;
            }
            if (key < array[parent(i)]) // check the parent if less or more than key (min or max heap)
            {
                array[i] = array[parent(i)];
                array[parent(i)] = key;
            }
        }
        H->size++; // increase size
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
    int val;
    if (isEmpty(H)) // prompt heap is empty if no node is existing
    {
        printf("\nHeap is empty!\n");
        return 0;
    }
    else
    {
        val = H->heap[1];
        int *array = H->heap;
        if (H->size == 1) // if size is one then just decrease the size
        {
            H->size--;
            return val;
        }
        else
        {
            array[1] = array[H->size]; // swap the value of the root and the last element
            array[H->size] = val;
            if (H->size == 2) // just decrease the size if size is 2
            {
                H->size--;
            }
            else
            {
                int l, r, i = 1, indexCheck;
                if (H->size == 3) // if more than 2 then compare the left and right child
                {
                    if (array[left(1)] < array[1]) // for min heap if left child is less than the root then swap
                    {
                        H->size--;
                        l = array[left(1)];
                        array[left(1)] = array[1];
                        array[1] = l;
                    }
                    else // for the right child then just decrease the size
                    {
                        H->size--;
                    }
                }
                else // if more than 3 then get the left and right then use it for comparing
                {

                    H->size--;
                    l = array[left(i)];
                    r = array[right(i)];

                    while (left(i) <= H->size) // until THE node has left child just continue
                    {
                        l = array[left(i)];
                        r = array[right(i)];
                        if (l > array[i])  // If less child is greater than the element then check if it has right child
                        {
                            indexCheck = right(i);
                            if (indexCheck < H->size && r < array[i]) 
                            { // if there is right child and r < array[i] then switch
                                array[right(i)] = array[i];
                                array[i] = r;
                                i = right(i);
                            }
                            break;
                        }
                        else
                        {
                            indexCheck = right(i);  // check if node have right child and right is less than l
                            if (indexCheck < H->size && l > r)
                            {
                                array[right(i)] = array[i];  // switch with right child
                                array[i] = r;
                                i = right(i);
                            }
                            else
                            {
                                array[left(i)] = array[i];  // switch with left child
                                array[i] = l;
                                i = left(i);
                            }
                        }
                    }
                }
            }
        }
    }

    return val;
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
    if (isEmpty(H))
    {
        printf("\nHeap is empty!\n");
        return NULL;
    }
    else
    {
        HEAP *temp = createHeap(30);

        for (int i = 1; i <= H->size; i++) // Copy values of heap
        {
            insert(temp, H->heap[i]);
        }

        while (temp->size != 0)
        {
            deleteM(temp);
        }
        return temp->heap;
    }
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
            printf("\nDeleted: %d\n", result);
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

        case '~':
            printf("The sorted version of the heap:\n");
            sorted = heapSort(H);
            for (key = 1; key <= H->size; key++)
                printf("%4d", sorted[key]);
            printf("\n");
            free(sorted);
            break;

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