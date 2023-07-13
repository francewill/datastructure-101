#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

char menu();
void addPlaylist(playlist *set, int index);

int main()
{
    playlist setOfPlaylist[10];
    int countPlaylist = 0;

    while (1)
    {
        char choice = menu();
        switch (choice)
        {
        case '1':
            addPlaylist(setOfPlaylist, countPlaylist);
            countPlaylist++;
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
            printf("\nThank you and goodbye!\n");
            break;
        default:
            printf("\nInvalid input!\n");
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

void addPlaylist(playlist *set, int index)
{
    char userInput[30];
    printf("\nEnter your playlist name: ");
    scanf("%s", userInput);
    for(int i = 0; i<index; i++){
        if(strcmp(userInput, set[i].playlistName)==0){
            printf("\nYou can't add a playlist with same name!\n");
            return;
        }
    }
    strcpy(set[index].playlistName, userInput);

}