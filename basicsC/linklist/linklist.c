#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct song_tag
{
    char title[20];
    char artist[20];
    char album[20];
    struct song_tag *nextSong;
} song;
typedef struct playlist_tag
{
    char name[50];
    int songCount;
    song *songHead;
    struct playlist_tag *next;
} playlist;

char menu();

int main()
{
    playlist *head = NULL;
    while (1)
    {
        char choice = menu();
        switch (choice)
        {
        case '1':
            printf("\nThis is option 1");
            break;
        case '2':
            printf("\nThis is option 2");
            break;
        case '3':
            printf("\nThis is option 3");
            break;
        case '4':
            printf("\nThis is option 4");
            break;
        case '5':
            printf("\nThis is option 5");
            break;
        case '6':
            printf("\nThank you and goodbye!\n");
            exit(0);
        default:
            printf("\nInvalid choice!\n");
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
