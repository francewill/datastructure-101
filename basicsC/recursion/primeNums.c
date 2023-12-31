#include <stdio.h>
int primeCheck(int divisor, int num);
int main()
{
    int userInput;
    char continueLoop;
    printf("\nWelcome!");
    while (1)
    {
        printf("\nEnter a positive number: ");  // ask for user input
        scanf("%d", &userInput);
        if (userInput < 2)  // If less than 2 then automatically give a prompt
        {
            printf("\nNo prime number values present.");
        }
        else
        {
            printf("The prime numbers from 1 to %d are:", userInput);
            for (int startCounter = 2; startCounter <= userInput; startCounter++)  // loop for checking the prime numbers from 1 to user input
            {
                // print the prime numbers
                if(primeCheck(2,startCounter)==0){
                       printf(" %d", startCounter);
                }
            }
        }
        printf("\nDo you still want to continue?\n[1] Yes\n[2] No\n>>> ");
        scanf(" %c", &continueLoop);
        if (continueLoop == '1')
        {
            continue;
        }
        else if (continueLoop == '2')
        {
            break;
        }
        else
        {
            printf("\nInvalid Input! Will continue!\n");
        }
    }
    printf("\nGoodbye!\n");
    return 0;
}

int primeCheck(int divisor, int num){
    if(divisor==num) return 0;  // base case returning 0 means it's a prime numebr
    else if(num % divisor==0) return 1; // base case returning 1 means it's a composite number
    else primeCheck(divisor+1,num);  // recursive case just add 1 in the divisor if the arguments above is not satisfied. 

}