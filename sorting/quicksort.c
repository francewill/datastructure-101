#include <stdio.h>
#include <stdlib.h>

int partition(int *array, int start, int end)
{
    int pivot = array[start], i = start, j = end, temp;
    while (i < j)
    {
        do
        {
            i++;
        } while (array[i] <= pivot);
        do
        {
            j--;
        } while (array[j] > pivot);

        if (i < j)
        {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    temp = pivot;
    array[start] = array[j];
    array[j] = temp;
    return j;
}

void quicksortRecursion(int *array, int start, int end){
    int helper;
    if(start< end){
     
        helper = partition(array, start, end);
        quicksortRecursion(array, start, helper);
        quicksortRecursion(array, helper+1, end);
    }
    
}

void quicksort(int *array, int length){
    quicksortRecursion(array, 0, length);
    
}

int main()
{

    int *array = (int *)malloc(sizeof(int) * 10);
    array[0] = 10;
    array[1] = 16;
    array[2] = 8;
    array[3] = 12;
    array[4] = 15;
    array[5] = 6;
    array[6] = 3;
    array[7] = 9;
    array[8] = 5;
    array[9] = 99999;
    // for( int i = 0; i< 9; i++){
    //     array[i] = rand() % (99 + 1 - 0) + 0;
    // }
    quicksort(array, 9);
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", array[i]);
    }
    return 0;
}