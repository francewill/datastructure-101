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
void viewOnePlaylist(playlist *head);
void viweAll(playlist *head);

int main()
{
    playlist *head = NULL; // always make it null 

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
            viewOnePlaylist(head);
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

char menu()  // menu function
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
        total += (int)word[i];  // add all ascii value of the string
    }
    return total;
}

void addPlaylist(playlist **head)
{
    char userInput[50];
    playlist *new = (playlist *)malloc(sizeof(playlist));
    printf("\nEnter playlist name: ");
    scanf(" %[^\n]s", userInput);
    for (playlist *temp = (*head); temp != NULL; temp = temp->next)  // check if playlist already exist
    {
        if (strcmp(temp->name, userInput) == 0)
        {
            printf("\nThis playlist already exist!\n");
            return;  // don't continue if userinput already exist
        }
    }
    strcpy(new->name, userInput); // if playlist is unique then copy it and pass the value to new
    new->songCount = 0;  // set songCount to 0
    new->songHead = NULL;  // song head to null since new playlist don't have any songs
    if ((*head) == NULL || asciiCounter(new->name) < asciiCounter((*head)->name)) // add at head
    {
        new->next = (*head);
        (*head) = new;
    }
    else  // add at middle or tail
    {
        playlist *temp;
        for (temp = (*head); temp->next != NULL; temp = temp->next)
        {
            if (asciiCounter(temp->next->name) > asciiCounter(new->name))
            {
                break;
            }
        }
        new->next = temp->next;
        temp->next = new;
    }
    printf("\nPlaylist successfully added!\n");
}

void viewOnePlaylist(playlist *head)
{
    char userInput[50];
    playlist *temp;
    int count = 1;
    if (head == NULL)
    {
        printf("\nPlease add a playlist first!\n");
    }
    else
    {
        printf("\nEnter the the Playlist name you want to view:");
        for (temp = head; temp != NULL; temp = temp->next)
        {
            printf("\n\t[%d] %s", count, temp->name);
            count++;
        }
        printf("\nEnter playlist name: ");
        scanf("%s", userInput);

        for (temp = head; temp != NULL; temp = temp->next)  // check if user input does not exist
        {
            if (strcmp(temp->name, userInput) == 0)
            {
                break;
            }
        }
        if (temp == NULL)
        {
            printf("\n%s does not exist!\n", userInput);
        }
        else  // if userinput exist then print the specific playlist
        {
            if (temp->songCount == 0)
            {
                printf("\n%s currently don't have any songs!\n", temp->name);
            }
            else
            {
                printf("\nPLAYLIST: %s", temp->name);
                printf("\nSONG COUNT: %d", temp->songCount);
                for (song *tempSong = temp->songHead; tempSong != NULL; tempSong = tempSong->nextSong)
                {
                    printf("\n\n\tSONG TITLE: %s", tempSong->title);
                    printf("\n\tSONG ARTIST: %s", tempSong->artist);
                    printf("\n\tSONG ALBUM: %s", tempSong->album);
                }
            }
        }
    }
}
void viweAll(playlist *head)  // show all playlist
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