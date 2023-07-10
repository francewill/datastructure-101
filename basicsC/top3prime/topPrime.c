#include<stdio.h>
int primeCheck(int divisor, int num);
void getInput(int *x, int *y);
void swapValues(int *x, int *y);

int main(){
    int x, y, largest1, largest2, largest3;
    getInput(&x, &y);
    swapValues(&x,&y);



  
    return 0;
}

int primeCheck(int divisor, int num){
    if(divisor == num) return 0; // prime number
    else if(num % divisor==0) return 1; // composite number
    else primeCheck(divisor+1,num);
}

void getInput(int *x, int *y){
    int tempX, tempY;
    printf("\nEnter a value for x: ");
    scanf("%d", &tempX);
    printf("\nEnter a value for y: ");
    scanf("%d", &tempY); 

    if(tempX <=1 && tempY <=1){
        printf("\nInvalid Range!");
    }else{
        *x = tempX;
        *y = tempY;
        printf("\n here is your number x = %d y = %d", *x,*y);
    }

}

void swapValues(int *x, int *y){
   int temp; 
   if(*x > *y){
        
        //printf("\nBefore x = %d and y = %d", *x,*y); 
        temp = *x;
        *x = *y;
        *y=temp;
        //printf("\nUpdated x = %d and y = %d", *x,*y); 
    }
}