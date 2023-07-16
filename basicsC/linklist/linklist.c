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
int asciiCounter(char *word);
void addPlaylist(playlist **head);
void viweAll(playlist *head);

int main()
{
    playlist *head = NULL;

    while (1)
    {
        char choice = menu();
        switch (choice)
        {
        case '1':
            addPlaylist(&head);
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
            viweAll(head);
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

int asciiCounter(char *word)
{
    int total = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        total += (int)word[i];
    }
    return total;
}

void addPlaylist(playlist **head)
{
    playlist *new = (playlist *)malloc(sizeof(playlist));
    printf("\nEnter playlist name: ");
    scanf(" %[^\n]s", new->name);
    if ((*head) == NULL || asciiCounter(new->name) < asciiCounter((*head)->name))
    {
        new->next = (*head);
        (*head) = new;
    }else{
        playlist *temp;
        for(temp = (*head); temp->next !=NULL; temp= temp->next){
            if(asciiCounter(temp->next->name)>asciiCounter(new->name)){
                break;
            }
        }
        new->next =temp->next;
        temp->next = new;

    }
}

void viweAll(playlist *head)
{
    if (head == NULL)
    {
        printf("\nPlease add a playlist first!\n");
    }
    else
    {
        for (playlist *temp = head; temp != NULL; temp = temp->next)
        {
            printf("\nPLAYLIST: %s\n", temp->name);
            printf("SONG COUNT: %d\n", temp->songCount);
        }
    }
}