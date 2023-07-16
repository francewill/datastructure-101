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
void addPlaylist(playlist **head);
void addSong(playlist **head);
void removeSong(playlist **head);
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
            addSong(&head);
            break;
        case '3':
            removeSong(&head);
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

char menu() // menu function
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

void addPlaylist(playlist **head)
{
    char userInput[50];
    playlist *new = (playlist *)malloc(sizeof(playlist));
    printf("\nEnter playlist name: ");
    scanf(" %[^\n]s", userInput);
    for (playlist *temp = (*head); temp != NULL; temp = temp->next) // check if playlist already exist
    {
        if (strcmp(temp->name, userInput) == 0)
        {
            printf("\nThis playlist already exist!\n");
            return; // don't continue if userinput already exist
        }
    }
    strcpy(new->name, userInput);                                // if playlist is unique then copy it and pass the value to new
    new->songCount = 0;                                          // set songCount to 0
    new->songHead = NULL;                                        // song head to null since new playlist don't have any songs
    if ((*head) == NULL || strcmp(new->name, (*head)->name) < 0) // add at head
    {
        new->next = (*head);
        (*head) = new;
    }
    else // add at middle or tail
    {
        playlist *temp;
        for (temp = (*head); temp->next != NULL; temp = temp->next)
        {
            if (strcmp(temp->next->name, new->name) > 0)
            {
                break;
            }
        }
        new->next = temp->next;
        temp->next = new;
    }
    printf("\nPlaylist successfully added!\n");
}

void addSong(playlist **head)
{
    char userChoicePlaylist[50];
    playlist *temp;
    if ((*head) == NULL)
    {
        printf("\nPlease add a playlist first!\n");
    }
    else
    {
        printf("\nChoose a Playlist: ");
        for (temp = (*head); temp != NULL; temp = temp->next)
        {
            printf("\n\t>>> %s", temp->name);
        }
        printf("\n\nEnter the name of the playlist: ");
        scanf(" %[^\n]s", userChoicePlaylist);
        for (temp = (*head); temp != NULL; temp = temp->next)
        {
            if (strcmp(temp->name, userChoicePlaylist) == 0)
            {
                break;
            }
        }
        if (temp == NULL)
        {
            printf("\n%s does not exist!\n", userChoicePlaylist);
        }
        else
        {
            char userSong[20];
            char userArtist[20];
            char userAlbum[20];
            song *new = (song *)malloc(sizeof(song));
            printf("\nEnter song title: ");
            scanf(" %[^\n]s", userSong);
            for (song *tempSong = temp->songHead; tempSong != NULL; tempSong = tempSong->nextSong)
            {
                if (strcmp(tempSong->title, userSong) == 0)
                {
                    printf("\nThis song already exist!\n");
                    return;
                }
            }
            strcpy(new->title, userSong);
            printf("Enter song artist: ");
            scanf(" %[^\n]s", new->artist);
            printf("Enter song album: ");
            scanf(" %[^\n]s", new->album);

            if (temp->songHead == NULL || strcmp(temp->songHead->title, new->title) > 0)
            {
                new->nextSong = temp->songHead;
                temp->songHead = new;
                temp->songCount++;
                printf("\n%s is successfully added!\n", userSong);
            }
            else
            {
                song *checker;
                for (checker = temp->songHead; checker->nextSong != NULL; checker = checker->nextSong)
                {
                    if (strcmp(new->title, checker->nextSong->title) < 0)
                    {
                        break;
                    }
                }
                new->nextSong = checker->nextSong;
                checker->nextSong = new;
                temp->songCount++;
                printf("\n%s is successfully added!\n", userSong);
            }
        }
    }
}

void removeSong(playlist **head)
{
    char userChoicePlaylist[50];
    playlist *temp;
  
    if ((*head) == NULL)
    {
        printf("\nPlease add a playlist first!\n");
    }
    else
    {
        printf("\nChoose a Playlist: ");
        for (temp = (*head); temp != NULL; temp = temp->next)
        {
            printf("\n\t>>> %s", temp->name);

        }
        printf("\n\nEnter the name of the playlist: ");
        scanf(" %[^\n]s", userChoicePlaylist);
        for (temp = (*head); temp != NULL; temp = temp->next)
        {
            if (strcmp(temp->name, userChoicePlaylist) == 0)
            {
                break;
            }
        }
        if (temp == NULL)
        {
            printf("\n%s does not exist!\n", userChoicePlaylist);
        }
        else
        {
            if(temp->songHead == NULL){
                printf("\nThis playlist don't have any songs!\n");
            }else{
                printf("\nThis playlist have songs\n");
            }
        }
    }
}
void viewOnePlaylist(playlist *head)
{
    char userInput[50];
    playlist *temp;

    if (head == NULL)
    {
        printf("\nPlease add a playlist first!\n");
    }
    else
    {
        printf("\nEnter the the Playlist name you want to view:");
        for (temp = head; temp != NULL; temp = temp->next)
        {
            printf("\n\t>>> %s", temp->name);
   
        }
        printf("\n\nEnter playlist name: ");
        scanf(" %[^\n]s", userInput);

        for (temp = head; temp != NULL; temp = temp->next) // check if user input does not exist
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
        else // if userinput exist then print the specific playlist
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
                    printf("\n\tSONG ALBUM: %s\n", tempSong->album);
                }
            }
        }
    }
}
void viweAll(playlist *head) // show all playlist
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