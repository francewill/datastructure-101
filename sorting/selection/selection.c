#include<stdlib.h>
#include<stdio.h>
// selection sort
void selection(int *array, int size){
    int min,temp; 
    for(int i = 0; i < size; i++){
        min = i;
        for(int j = i+1; j< size;j++){
            if (array[min] > array[j]){
                min = j;
            }
        }
       temp = array[i];
       array[i]= array[min];
       array[min] = temp; 
    }
}

int main(){
    int array[10] = {11, 9, 15, 27, 30, 43, 100, 77, 93, 10}; 
    selection(array, 10);
    for(int i = 0; i < 10; i++){
        printf("%d ", array[i]);
    }
    return 0;
}