#include<stdio.h>
int primeCheck(int divisor, int num);

int main(){
    return 0;
}

int primeCheck(int divisor, int num){
    if(divisor == num) return 0; // prime number
    else if(num % divisor==0) return 1; // composite number
    else primeCheck(divisor+1,num);
}