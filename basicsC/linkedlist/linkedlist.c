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
void addPlaylist(playlist **head, int *checkChanges);
void addSong(playlist **head, int *checkChanges);
void removeSong(playlist **head, int *checkChanges);
void viewOnePlaylist(playlist *head);
void viweAll(playlist *head);
void deleteAll(playlist **head);
void save(playlist *head, int playlistNum, int checkChanges);
void load(playlist **head, int *playlistNum);

int main()
{
    playlist *head = NULL; // always make it null
    int playlistNum = 0;
    int checkChanges = 0;
    load(&head, &playlistNum);
    while (1)
    {
        char choice = menu();
        switch (choice)
        {
        case '1':
            addPlaylist(&head, &checkChanges);
            playlistNum++;
            break;
        case '2':
            addSong(&head, &checkChanges);
            break;
        case '3':
            removeSong(&head, &checkChanges);
            break;
        case '4':
            viewOnePlaylist(head);
            break;
        case '5':
            viweAll(head);
            break;
        case '6':
            save(head, playlistNum, checkChanges);
            deleteAll(&head);
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

void addPlaylist(playlist **head, int *checkChanges)
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
    *checkChanges = 1;
}

void addSong(playlist **head, int *checkChanges)
{
    char userChoicePlaylist[50];
    playlist *temp;
    if ((*head) == NULL) // check if head is null
    {
        printf("\nPlease add a playlist first!\n");
    }
    else // if not null then get user input
    {
        printf("\nChoose a Playlist: ");
        for (temp = (*head); temp != NULL; temp = temp->next)
        {
            printf("\n\t>>> %s", temp->name);
        }
        printf("\n\nEnter the name of the playlist: ");
        scanf(" %[^\n]s", userChoicePlaylist);
        for (temp = (*head); temp != NULL; temp = temp->next) // check if playlist exist
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
        else // incase temp is not null then playlist exist
        {
            char userSong[20];
            char userArtist[20];
            char userAlbum[20];
            song *new = (song *)malloc(sizeof(song));
            printf("\nEnter song title: ");
            scanf(" %[^\n]s", userSong);
            for (song *tempSong = temp->songHead; tempSong != NULL; tempSong = tempSong->nextSong) // check if user input already exist
            {
                if (strcmp(tempSong->title, userSong) == 0) // if there is same title automatically return and end the function
                {
                    printf("\nThis song already exist!\n");
                    return;
                }
            }
            strcpy(new->title, userSong); // else proceed
            printf("Enter song artist: ");
            scanf(" %[^\n]s", new->artist);
            printf("Enter song album: ");
            scanf(" %[^\n]s", new->album);

            if (temp->songHead == NULL || strcmp(temp->songHead->title, new->title) > 0) // insert at head
            {
                new->nextSong = temp->songHead;
                temp->songHead = new;
            }
            else // insert at tail or middle
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
            }
            temp->songCount++; // increment song count
            printf("\n%s is successfully added!\n", userSong);
            *checkChanges = 1;
        }
    }
}

void removeSong(playlist **head, int *checkChanges)
{
    char userChoicePlaylist[50];
    playlist *temp;

    if ((*head) == NULL) // check if playlists exist
    {
        printf("\nPlease add a playlist first!\n");
    }
    else
    {
        printf("\nChoose a Playlist: "); // get user input
        for (temp = (*head); temp != NULL; temp = temp->next)
        {
            printf("\n\t>>> %s", temp->name);
        }
        printf("\n\nEnter the name of the playlist: ");
        scanf(" %[^\n]s", userChoicePlaylist);
        for (temp = (*head); temp != NULL; temp = temp->next) // check if the userinput exist
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
        else // if it exist check if the playlist have songs
        {
            char userSongInput[20];
            char userArtistInput[20];
            if (temp->songHead == NULL)
            {
                printf("\nThis playlist don't have any songs!\n");
            }
            else // if there are songs then ask for title and artist
            {
                printf("\nHere are the songs available in %s:\n", temp->name);
                for (song *tempSong = temp->songHead; tempSong != NULL; tempSong = tempSong->nextSong)
                {
                    printf("\n>>> %s", tempSong->title);
                }
                printf("\nEnter song title to delete: ");
                scanf(" %[^\n]s", userSongInput);
                printf("\nEnter song artist to delete: ");
                scanf(" %[^\n]s", userArtistInput);
                song *tempSongCheck;
                for (tempSongCheck = temp->songHead; tempSongCheck != NULL; tempSongCheck = tempSongCheck->nextSong)
                {
                    if (strcmp(userSongInput, tempSongCheck->title) == 0 && strcmp(userArtistInput, tempSongCheck->artist) == 0)
                    {
                        break; // both artist and title must match
                    }
                }
                if (tempSongCheck == NULL)
                {
                    printf("\nYour input does not exist!\n");
                }
                else
                {
                    if (tempSongCheck == temp->songHead) // delete at head
                    {
                        temp->songHead = temp->songHead->nextSong;
                    }
                    else // delete at middle or tail
                    {
                        song *p;
                        for (p = temp->songHead; p->nextSong != tempSongCheck; p = p->nextSong)
                            ;
                        p->nextSong = tempSongCheck->nextSong;
                    }
                    free(tempSongCheck);
                    temp->songCount--;
                    *checkChanges = 1;
                    printf("\n%s successfully deleted!\n", userSongInput);
                }
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

void deleteAll(playlist **head) // delete all
{
    playlist *temp;
    song *tempSong;
    while ((*head) != NULL)
    {
        temp = (*head);
        while (temp->songHead != NULL)
        {
            tempSong = temp->songHead;
            temp->songHead = temp->songHead->nextSong;
            free(tempSong);
        }
        (*head) = (*head)->next;
        free(temp);
    }
}

void save(playlist *head, int playlistNum, int checkChanges)
{

    if (checkChanges)
    {
        FILE *fp = fopen("myplaylist.txt", "w");
        fprintf(fp, "%d\n", playlistNum); // print number of playlist
        for (playlist *temp = head; temp != NULL; temp = temp->next)
        {
            fprintf(fp, "%s\n", temp->name);      // name of playlist
            fprintf(fp, "%d\n", temp->songCount); // it's song count
            for (song *tempSong = temp->songHead; tempSong != NULL; tempSong = tempSong->nextSong)
            {
                fprintf(fp, "%s\n", tempSong->title); // details of song
                fprintf(fp, "%s\n", tempSong->artist);
                fprintf(fp, "%s\n", tempSong->album);
            }
        }
        printf("\nYour data is successfully saved!\n");
        fclose(fp);
    }
    else
    {
        printf("\nThere are no changes in your data!\n");
    }
}

void load(playlist **head, int *playlistNum)
{
    FILE *fp = fopen("myplaylist.txt", "r");
    if (fp != NULL)
    {
        fscanf(fp, " %d\n", playlistNum);  // get the number of playlist
        for (int i = 0; i < *playlistNum; i++)
        {
            playlist *new = (playlist *)malloc(sizeof(playlist));
            fscanf(fp, " %[^\n]s", new->name);  // transfer name of playlist to new
            fscanf(fp, "%d", &new->songCount);  // transfer song count to new
            new->songHead = NULL;  // set songhead to null
            if ((*head) == NULL)  // add at head
            {
                new->next = (*head);
                (*head) = new;
            }
            else  // add at tail
            {
                playlist *temp;
                for(temp = (*head); temp->next!=NULL;temp=temp->next);
                new->next = temp->next;
                temp->next = new;
            }

            if(new->songCount){
                for(int j = 0; j < new->songCount;j++){
                    song *newSong = (song *) malloc (sizeof(song));
                    fscanf(fp, " %[^\n]", newSong->title);  // get the information for song
                    fscanf(fp, " %[^\n]", newSong->artist);
                    fscanf(fp, " %[^\n]", newSong->album);

                    if(new->songHead==NULL){  // add at head 
                        newSong->nextSong = new->songHead;
                        new->songHead = newSong;
                    }else{  // add at tail
                        song *tempSong;
                        for(tempSong = new->songHead; tempSong->nextSong!=NULL; tempSong = tempSong->nextSong);
                        newSong->nextSong = tempSong->nextSong;
                        tempSong->nextSong = newSong;
                    }
                
                }
            }
            
        }
        printf("\nSuccessfully loaded the data!\n");
        fclose(fp);
    }
    else
    {
        printf("\nThere is no saved data!\n");
    }
}