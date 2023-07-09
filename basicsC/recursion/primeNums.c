#include <stdio.h>
int primeCheck(int divisor, int num);
int main()
{
    int userInput;
    char continueLoop;
    printf("\nWelcome!");
    while (1)
    {
        printf("\nEnter a positive number: ");
        scanf("%d", &userInput);
        if (userInput < 2)
        {
            printf("\nNo prime number values present.");
        }
        else
        {
            printf("The prime numbers from 1 to %d are:", userInput);
            for (int startCounter = 2; startCounter <= userInput; startCounter++)
            {
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
}

int primeCheck(int divisor, int num){
    if(divisor==num) return 0;
    else if(num % divisor==0) return 1;
    else primeCheck(divisor+1,num);

}