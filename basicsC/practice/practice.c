#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct song_tag
{
    char title[50];
    char artist[50];
    char genre[50];
    struct song_tag *nextSong;
} SONGS;

typedef struct playlist_tag
{
    int numSong;
    char namePlaylist[50];
    SONGS *songhead;
    struct playlist_tag *next;
} PLAYLIST;

char mainMenu()
{
    char choice;
    printf("\n===Menu===");
    printf("\n[1] Add playlist");
    printf("\n[2] Add song to playlist");
    printf("\n[3] Remove song to playlist");
    printf("\n[4] View a playlist");
    printf("\n[5] View all data");
    printf("\n[6] Exit");
    printf("\n\nEnter your choice: ");
    scanf(" %c", &choice);
    return choice;
}

void *createPlaylist(PLAYLIST **head, int *playlistNum)
{
    char userInput[50];
    PLAYLIST *p = (PLAYLIST *)malloc(sizeof(PLAYLIST));
    printf("\nEnter playlist: \n");
    scanf(" %[^\n]s", userInput);
    PLAYLIST *temp;
    for (temp = *head; temp != NULL; temp = temp->next)
    {
        if (strcmp(temp->namePlaylist, userInput) == 0)
        {
            break;
        }
    }
    if (temp == NULL)
    {
        strcpy(p->namePlaylist, userInput);
        p->numSong = 0;
        p->next = *head;
        p->songhead = NULL;
        *head = p;
        *playlistNum++;
    }
    else
    {
        printf("\nPlaylist already exist\n");
    }
}

void createSong(PLAYLIST **head)
{
    char userPlaylist[50];
    char userSong[50];
    printf("\nEnter your playlist where to add your song: \n");
    scanf(" %[^\n]s", userPlaylist);
    PLAYLIST *temp;
    for (temp = *head; temp != NULL; temp = temp->next)
    {
        if (strcmp(userPlaylist, temp->namePlaylist) == 0)
        {
            break;
        }
    }
    if (temp == NULL)
    {
        printf("\nYour playlist does not exxist\n");
    }
    else
    {
        printf("\nEnter your song title: \n");
        scanf(" %[^\n]s", userSong);
        SONGS *temp2;
        for(temp2 = temp->songhead; temp2!=NULL; temp2 = temp2->nextSong){
            if(strcmp(userSong, temp2->title)==0){
                break;
            }
        }
        if(temp2==NULL){
            SONGS *yourSong = (SONGS *) malloc (sizeof(SONGS));
            strcpy(yourSong->title,userSong);
            printf("\nEnter your artist: \n");
            scanf(" %[^\n]s",yourSong->artist);
            printf("\nEnter your genre: \n");
            scanf(" %[^\n]", yourSong->genre);
            yourSong->nextSong = temp->songhead;
            temp->songhead = yourSong;
            temp->numSong++;

        }else{
            printf("\nThis song already exist!\n");
        }
    }
}
void removeSong(PLAYLIST **head){
    if(*head==NULL){
        printf("\nThere are no playlist\n");
    }else{
        char userPlaylist[50];
        PLAYLIST *temp;
        for(temp = *head;temp!=NULL; temp = temp->next){
            printf("\n>>> %s",temp->namePlaylist);
        }        
        printf("\nWhere do you want to delete:");
        scanf(" %[^\n]s", userPlaylist);
        for(temp=*head;temp!=NULL; temp=temp->next){
            if(strcmp(userPlaylist,temp->namePlaylist)==0){
                break;
            }
        }
        if(temp==NULL){
            printf("\nThis playlist does not exist!\n");
        }else{
            for(SONGS *temp2 = temp->songhead;temp2!=NULL;temp2= temp2->nextSong){
                printf("\n>>> %s by %s", temp2->title,temp2->artist);
            }
        }
    }
}
void printAll(PLAYLIST *head)
{
    PLAYLIST *temp;
    int count = 1;
    for (temp = head; temp != NULL; temp = temp->next)
    {
        printf("\n[%d] %s", count, temp->namePlaylist);
        count++;
        printf("\nSongs = %d\n", temp->numSong);
        for (SONGS *temp2 = temp->songhead; temp2 != NULL; temp2 = temp2->nextSong)
        {
            printf("\n* %s\n", temp2->title);
        }
    }
}
int main()
{
    int playlistNum = 0;

    PLAYLIST *head = NULL;
    while (1)
    {
        char userChoice = mainMenu();
        switch (userChoice)
        {
        case '1':
            createPlaylist(&head, &playlistNum);
            break;
        case '2':
            createSong(&head);
            break;
        case '3':
            removeSong(&head);
            break;
        case '4':
            printf("\nHere are your data\n");
            printAll(head);
            break;
        case '5':
            printf("\nuser input = 5\n");
            break;
        case '6':
            printf("\nThank you for using our program\n");
            exit(0);
            break;
        default:
            printf("\nInvalid input0\n");
            break;
        }
    }

    return 0;
}