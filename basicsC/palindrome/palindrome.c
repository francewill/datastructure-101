#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isPalindrome(char *word);

int main()
{
    char history[50][50];   // Only 50 palindromes 
    int inputCounter = 0;  // counter for our palindromes so we can store it properly
    char userInput[50];
    while (1)
    {
        printf("\nEnter a string: ");
        scanf("%s", userInput);
        for (int i = 0; i < strlen(userInput); i++)
        {
            if (islower(userInput[i]))
            {
                userInput[i] = toupper(userInput[i]);  // make it uppercase 
            }
        }

        if (strcmp(userInput, "EXIT") == 0)
        {
            printf("Goodbye!\n");
            printf("\nPalindrome history: \n");
            for (int i = 0; i < inputCounter; i++)  // print history
            {
                printf("%s\n", history[i]);
            }
            break;
        }
        else
        {
            if (isPalindrome(userInput))  // word is palindrome
            {
                printf("\n%s is a palindrome!\n", userInput);
                strcpy(history[inputCounter], userInput);
                inputCounter++;
            }
            else
            {
                printf("\n%s is not a palindrome!\n", userInput);
            }
        }
    }
    return 0;
}

int isPalindrome(char *word)
{
    int length = strlen(word);  // get the length of the word
    int endTracker = 1;  // this will be our tracker to the end(right side) character
    for (int i = 0; i < length / 2; i++)  
    {
        if (word[i] == word[(length - endTracker)])  // if the character from the left and right side are equal increment end tracker and continue comparing
        {
            endTracker++;
            continue;
        }
        else  // else return not palindrome
            return 0;
    }
    return 1; // return if word is palindrome
}