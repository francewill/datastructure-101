#include<stdio.h>
#include<stdlib.h>

void bubblesort(int *array, int size){
    int temp;
    for(int i = 0;i<size;i++){
        for(int j =0; j<size-i;j++){
            if(array[j]>array[j+1]){
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}
int main(){
    int array[11] = {101,11, 9, 15, 27, 30, 43, 100, 77, 93, 10};
    bubblesort(array,11);
    for(int i= 0; i<11;i++){
        printf("%d ", array[i]);
    }
    return 0;
}