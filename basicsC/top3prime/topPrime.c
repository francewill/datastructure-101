#include<stdio.h>
#include<stdlib.h>
int primeCheck(int divisor, int num);
void getInput(int *x, int *y);
void swapValues(int *x, int *y);
void getLargest(int x,int y, int *large1,int *large2, int *large3);
void printLargest(int large1,int large2, int large3);

int main(){
    int x, y, largest1, largest2, largest3;
    getInput(&x, &y);
    swapValues(&x,&y);
    getLargest(x, y, &largest1, &largest2, &largest3);
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
        printf("\nInvalid Range!\n");
        exit(0);
    }else{
        *x = tempX;
        *y = tempY;
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

void getLargest(int x,int y, int *large1,int *large2, int *large3){
    int count = 0;
    *large1=0;
    *large2=0;
    *large3=0;
    if(x<1){
        x = 2;
    }

    for(int end = y; end>=x;end--){

        if(primeCheck(2, end)==0){
            if(count == 0){
                count++;   
                *large1 = end;
            }else if(count == 1){
                count++;  
                *large2 = end;
            }else if(count == 2){
                count++;  
                *large3 = end;
            }else{
          
                break;
            }
               
        }

    }
    printLargest(*large1, *large2, *large3);
}

void printLargest(int large1,int large2, int large3){
    if(large1 == 0 && large2 == 0 && large3 == 0){
        printf("\nNo prime numbers found.\n");
    }else if(large2 == 0 && large3 == 0){
        printf("\nThere is one prime number: %d\n", large1);
       
    }else if(large3 == 0){
        printf("\nThere are two prime numbers: %d %d\n", large1, large2);
    }else{
        printf("\nThe three largest prime numbers are: %d %d %d\n", large1,large2,large3);
    }
    
    
}