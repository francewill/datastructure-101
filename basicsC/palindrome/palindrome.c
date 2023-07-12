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
            if (islower(userInput[i]))
            {
                userInput[i] = toupper(userInput[i]);
            }
        }

        if (strcmp(userInput, "EXIT") == 0)
        {
            printf("Goodbye!\n");
            break;
        }
        else
        {
            if (isPalindrome(userInput))
            {
                printf("\n%s is a palindrome!\n",userInput);
            }
            else
            {
                printf("\n%s is not a palindrome!\n",userInput);
            }
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
        else
            return 0;
    }
    return 1;
}