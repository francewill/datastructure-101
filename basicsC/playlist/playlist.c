#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char menu();

int main()
{
    typedef struct
    {
        char songTitle[30];
        char artist[30];
        char album[30];
    } song;

    typedef struct
    {
        char playlistName[30];
        int songCount;
        song arraySong[10];

    } playlist;

    while (1)
    {
        char choice = menu();
        switch (choice)
        {
            case '1':
                printf("\nYou choose 1");
                break;
            case '2':
                printf("\nYou choose 2");
                break;
            case '3':
                printf("\nYou choose 3");
                break;
            case '4':
                printf("\nYou choose 4");
                break;
            case '5':
                printf("\nYou choose 5");
                break;
            case '6':
                printf("\nYou choose 6");
                break;
            default:
                printf("\nInvalid input!");
        }
    }

    return 0;
}
char menu()
{
    char choice;
    printf("\n======= MENU =======");
    printf("\n[1] Add Playlist");
    printf("\n[2] Add Song to Playlist");
    printf("\n[3] Remove Song from Playlist");
    printf("\n[4] View a Playlist");
    printf("\n[5] View All Data");
    printf("\n[6] Exit");
    printf("\n\nEnter your choice: ");
    scanf(" %c", &choice);
    return choice;
}