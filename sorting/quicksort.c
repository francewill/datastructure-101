#include<stdio.h>
#include<stdlib.h>

int main(){

    int *array = (int *) malloc (sizeof(int)*10);
    array[9] = 99999;
    for( int i = 0; i< 10; i++){
        array[i] = rand() % (99 + 1 - 0) + 0; 
    }

    for(int i = 0; i < 10; i++){
        printf("%d ", array[i]);
    }
    return 0;
}