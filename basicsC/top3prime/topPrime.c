#include<stdio.h>
int primeCheck(int divisor, int num);
void getInput(int *x, int *y);

int main(){
    int x, y, largest1, largest2, largest3;
    getInput(&x, &y);
  


    return 0;
}

int primeCheck(int divisor, int num){
    if(divisor == num) return 0; // prime number
    else if(num % divisor==0) return 1; // composite number
    else primeCheck(divisor+1,num);
}

void getInput(int *x, int *y){
    printf("\nEnter a value for x: ");
    scanf("%d", x);
    printf("\nEnter a value for y: ");
    scanf("%d", y);   
}