#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int partition(int *array, int start, int end)  // this will divide the array and responsible for swapping
{
    int pivot = array[start], i = start, j = end, temp;
    while (i < j)  // loop until i does not pass j
    {
        do
        {
            i++; // increment i until  we found a number lesser than pivot
        } while (array[i] <= pivot);
        do
        {
            j--;  // decrement until we found a  number greater than pivot
        } while (array[j] > pivot);

        if (i < j)  // check if i is less than j
        {
            temp = array[i];  // swap the values
            array[i] = array[j];
            array[j] = temp;
        }
    }
    temp = pivot;  // after the loop swap the pivot and the j
    array[start] = array[j];
    array[j] = temp;
    return j;
}

void quicksortRecursion(int *array, int start, int end)  // recursion for quicksort
{
    int helper;
    if (start < end)  // always check if we
    {

        helper = partition(array, start, end); // divide the array
        quicksortRecursion(array, start, helper);  // this is for the left side
        quicksortRecursion(array, helper + 1, end);  // this is for the right side
    }
}

void quicksort(int *array, int length)
{
    quicksortRecursion(array, 0, length);
}

int main()
{

    int *array = (int *)malloc(sizeof(int) * 10);
    array[9] = 99999;
    // random numbers
    srand ( time(NULL) );
    for( int i = 0; i< 9; i++){
        array[i] = rand() % (99 + 1 - 0) + 0;
    }

    quicksort(array, 9);  // call the quicksort function

    for (int i = 0; i < 10; i++)
    {
        printf("%d ", array[i]);
    }
    return 0;
}