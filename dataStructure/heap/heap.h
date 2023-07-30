// ___  ____    _  _ ____ ___    ____ ___  _ ___    ___ _  _ _ ____    ____ _ _    ____ 
// |  \ |  |    |\ | |  |  |     |___ |  \ |  |      |  |__| | [__     |___ | |    |___ 
// |__/ |__|    | \| |__|  |     |___ |__/ |  |      |  |  | | ___]    |    | |___ |___ 
//

#ifndef _HEAP_H_
#define _HEAP_H_

typedef struct heap_tag {
  int *heap;
  int size;
  int maxSize;
} HEAP;


/*
 *  PRINT HEAP
 *  requirements:
      a non-null HEAP pointer
      a non-empty *heap
 *  results:
      prints the heap (rotated +90 degrees)...
*/

void printHeap(HEAP *H);


/*
 *  CREATE HEAP
 *  requirements: none
 *  results:
      initializes fields of the structure
      returns the created heap
*/
HEAP* createHeap(int maxSize);


/*
 *  IS FULL
 *  requirements: none
 *  results:
      return 1 if the heap is full
      otherwise return 0
*/
int isFull(HEAP *H);


/*
 *  IS EMPTY
 *  requirements: none
 *  results:
      return 1 if the heap is empty
      otherwise return 0
*/
int isEmpty(HEAP *H);


/*
 *  CLEAR
 *  requirements:
      a non-null HEAP pointer
      a non-empty *heap
 *  results:
      deletes all the items in the heap
*/
void clear(HEAP *H);


/*
 *  INSERT
 *  requirements:
      a non-null HEAP pointer
      a non-full *heap
 *  results:
      inserts `key` to the MIN HEAP `heap`
*/
void insert(HEAP *H, int key);


/*
 *  DELETE M
 *  requirements:
      a non-null HEAP pointer
      a non-empty *heap
 *  results:
	    removes the minimum value (root) from the MIN HEAP `heap`
      returns the deleted value
*/
int deleteM(HEAP *H);


/*
 *  HEAP SORT
 *  requirements:
      a non-null HEAP pointer
      a non-empty *heap
 *  results:
 	    returns an array containing the sorted (descending order) values of the MIN HEAP `heap`
	    IMPORTANT: MUST NOT MODIFY ORIGINAL HEAP
*/
int *heapSort(HEAP *H);

#endif