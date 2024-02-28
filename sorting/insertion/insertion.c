#include <stdio.h>
#include <stdlib.h>

void insertion(int *array, int size)
{
    int sorted,temp;

    for(int i = 1; i < size; i++){
        if(array[i]<array[i-1]){
            for(int j = i; j>0;j--){
                if(array[j]>array[j-1]){
                    break;
                }
                temp = array[j];
                array[j]= array[j-1];
                array[j-1]= temp;
            }
        }
    }
}

int main()
{
    int array[11] = {101,11, 9, 15, 27, 30, 43, 100, 77, 93, 10};
    insertion(array,11);
    for(int i= 0; i<11;i++){
        printf("%d ", array[i]);
    }
    return 0;
}