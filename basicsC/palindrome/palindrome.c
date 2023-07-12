#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int isPalindrome(char *word);

int main(){
    char userInput[50];
    while(1){
        printf("\nEnter a string: ");
        scanf("%s", userInput);
        for(int i = 0;i<strlen(userInput);i++){
            if(isupper(userInput[i])){
                userInput[i] = tolower(userInput[i]);
            }
        }

        if(strcmp(userInput,"exit")==0){
            printf("Goodbye!\n");
            break;
        }else{
            printf("Check\n");
        }
    }
    return 0;
}

