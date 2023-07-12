#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isPalindrome(char *word);

int main()
{
    char userInput[50];
    while (1)
    {
        printf("\nEnter a string: ");
        scanf("%s", userInput);
        for (int i = 0; i < strlen(userInput); i++)
        {
            if (isupper(userInput[i]))
            {
                userInput[i] = tolower(userInput[i]);
            }
        }

        if (strcmp(userInput, "exit") == 0)
        {
            printf("Goodbye!\n");
            break;
        }
        else
        {
            printf("\nResult : %d", isPalindrome(userInput));
        }
    }
    return 0;
}

int isPalindrome(char *word)
{
    int length = strlen(word);
    int endTracker = 1;
    for (int i = 0; i < length / 2; i++)
    {
        if (word[i] == word[(length - endTracker)])
        {
            endTracker++;
            continue;
        }
        else return 0;
 
    }
    return 1;
}