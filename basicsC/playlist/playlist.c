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
int addPlaylist(playlist *set, int index);
int addSong(playlist *set, int index);
void removeSong(playlist *set, int index);
void viweAll(playlist *set, int index);
void viewOnePlaylist(playlist *set, int index);
void save(playlist *set, int index);
void load(playlist *set, int *index);

int main()
{
    playlist setOfPlaylist[10];
    int countPlaylist = 0;
    int status;
    load(setOfPlaylist,&countPlaylist);
    while (1)
    {
        char choice = menu();
        switch (choice)
        {
        case '1':
            if (addPlaylist(setOfPlaylist, countPlaylist))
            {
                printf("\nPlaylist successfully added!\n");
                countPlaylist++;
            }
            else
            {
                printf("\nYou can't add a playlist with same name!\n");
            }
            break;
        case '2':
            status = addSong(setOfPlaylist, countPlaylist);
            if (status == 1)
            {
                printf("\nSong successfully added to the playlist!\n");
            }
            else if (status == 0)
            {
                printf("\nSong already exist!\n");
            }
            else if (status == 2)
            {
                printf("\nPlease add a playlist first!\n");
            }
            else if (status == 3)
            {
                printf("\nPlease enter a valid playlist!\n");
            }

            break;
        case '3':
            removeSong(setOfPlaylist, countPlaylist);
            break;
        case '4':
            viewOnePlaylist(setOfPlaylist, countPlaylist);
            break;
        case '5':
            viweAll(setOfPlaylist, countPlaylist);
            break;
        case '6':
            save(setOfPlaylist, countPlaylist);
            printf("\nThank you and goodbye!\n");
            exit(0);
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

int addPlaylist(playlist *set, int index)
{
    char userInput[30];
    printf("\nEnter your playlist name: ");
    scanf(" %[^\n]s", userInput);
    for (int i = 0; i < index; i++)
    {
        if (strcmp(userInput, set[i].playlistName) == 0)
        {
            return 0;
        }
    }
    strcpy(set[index].playlistName, userInput);
    set[index].songCount = 0;
    return 1;
}

int addSong(playlist *set, int index)
{
    int playlistChoice;
    char title[30];
    char artist[30];
    char album[30];

    if (index == 0)
    {
        return 2;
    }
    else
    {
        printf("\nHere are the available playlist:");
        for (int i = 0; i < index; i++)
        {
            printf("\n\t[%d] %s", i, set[i].playlistName);
        }
        printf("\nEnter playlist number: ");
        scanf("%d", &playlistChoice);
        if (playlistChoice > index - 1 || playlistChoice < 0)
        {
            return 3;
        }
        else
        {
            if (set[playlistChoice].songCount == 10)
            {
                printf("\nYou already have 10 songs!\n");
            }
            else
            {
                printf("\nEnter song title: ");
                scanf(" %[^\n]s", title);
                for (int i = 0; i < set[playlistChoice].songCount; i++)
                {
                    if (strcmp(title, set[playlistChoice].arraySong[i].songTitle) == 0)
                    {
                        return 0;
                    }
                }
                strcpy(set[playlistChoice].arraySong[set[playlistChoice].songCount].songTitle, title);
                printf("\nEnter song artist: ");
                scanf(" %[^\n]s", set[playlistChoice].arraySong[set[playlistChoice].songCount].artist);
                printf("\nEnter song album: ");
                scanf(" %[^\n]s", set[playlistChoice].arraySong[set[playlistChoice].songCount].album);
                set[playlistChoice].songCount++;
                return 1;
            }
        }
    }
}

void removeSong(playlist *set, int index)
{
    int playlistChoice;
    int removeSongChoice;
    char deletedSong[30];

    if (index == 0)
    {
        printf("\nPlease add a playlist first!\n");
    }
    else
    {
        printf("\nHere are the available playlist:");
        for (int i = 0; i < index; i++)
        {
            printf("\n\t[%d] %s", i, set[i].playlistName);
        }
        printf("\nEnter playlist number: ");
        scanf("%d", &playlistChoice);
        if (set[playlistChoice].songCount == 0)
        {
            printf("\nPlease add a song first!\n");
        }
        else
        {
            printf("\nHere are the songs in %s:", set[playlistChoice].playlistName);
            for (int i = 0; i < set[playlistChoice].songCount; i++)
            {
                printf("\n[%d]", i);
                printf("\n\tSONG TITLE: %s", set[playlistChoice].arraySong[i].songTitle);
                printf("\n\tSONG ARTIST: %s", set[playlistChoice].arraySong[i].artist);
                printf("\n\tSONG ALBUM: %s\n", set[playlistChoice].arraySong[i].album);
            }
            printf("\nEnter the number of the song you want to delete: ");
            scanf("%d", &removeSongChoice);
            if (removeSongChoice < 0 || removeSongChoice > set[playlistChoice].songCount - 1)
            {
                printf("\nPlease enter a valid song!\n");
            }
            else
            {
                strcpy(deletedSong, set[playlistChoice].arraySong[removeSongChoice].songTitle);

                for (int i = removeSongChoice; i < set[playlistChoice].songCount; i++)
                {
                    strcpy(set[playlistChoice].arraySong[i].songTitle, set[playlistChoice].arraySong[i + 1].songTitle);
                    strcpy(set[playlistChoice].arraySong[i].artist, set[playlistChoice].arraySong[i + 1].artist);
                    strcpy(set[playlistChoice].arraySong[i].album, set[playlistChoice].arraySong[i + 1].album);
                }
                set[playlistChoice].songCount--;
                printf("\n%s is successfully deleted!\n", deletedSong);
            }
        }
    }
}

void viweAll(playlist *set, int index)
{
    if (index == 0)
    {
        printf("\nPlease add a playlist first!\n");
    }
    else
    {
        for (int i = 0; i < index; i++)
        {
            printf("\nPLAYLIST: %s", set[i].playlistName);
            printf("\nSONG COUNT: %d\n", set[i].songCount);
        }
    }
}

void viewOnePlaylist(playlist *set, int index)
{
    int playlistChoice;
    if (index == 0)
    {
        printf("\nPlease add a playlist first!\n");
    }
    else
    {
        printf("\nPlease select a Playlist:");
        for (int i = 0; i < index; i++)
        {
            printf("\n\t [%d] %s", i, set[i].playlistName);
        }
        printf("\n>>> ");
        scanf("%d", &playlistChoice);
        if (playlistChoice > index - 1 || playlistChoice < 0)
        {
            printf("\nPlease enter a valid playlist!\n");
        }
        else if (set[playlistChoice].songCount == 0)
        {
            printf("\nPlease add a song first for this playlist!\n");
        }
        else
        {
            printf("\nPLAYLIST: %s", set[playlistChoice].playlistName);
            printf("\nSONG COUNT: %d\n", set[playlistChoice].songCount);
            for (int i = 0; i < set[playlistChoice].songCount; i++)
            {
                printf("\n\tSONG TITLE: %s", set[playlistChoice].arraySong[i].songTitle);
                printf("\n\tSONG ARTIST: %s", set[playlistChoice].arraySong[i].artist);
                printf("\n\tSONG ALBUM: %s\n", set[playlistChoice].arraySong[i].album);
            }
        }
    }
}

void save(playlist *set, int index)
{
    FILE *fp = fopen("myplaylist.txt", "w");

    fprintf(fp, "%d\n", index);
    for (int i = 0; i < index; i++)
    {
        fprintf(fp, "%s\n", set[i].playlistName);
        fprintf(fp, "%d\n", set[i].songCount);
        for (int j = 0; j < set[i].songCount; j++)
        {
            fprintf(fp, "%s\n", set[i].arraySong[j].songTitle);
            fprintf(fp, "%s\n", set[i].arraySong[j].artist);
            fprintf(fp, "%s\n", set[i].arraySong[j].album);
        }
    }
    printf("\nSuccessfully saved the data!\n");
    fclose(fp);
}

void load(playlist *set, int *index)
{
    FILE *fp = fopen("myplaylist.txt", "r");
    if (fp == NULL)
    {
        printf("\n\nNo saved data!\n");
    }
    else
    {
        fscanf(fp, "%d\n", index);
        for (int i = 0; i < (*index); i++)
        {
            fscanf(fp, " %[^\n]s", set[i].playlistName);
            fscanf(fp, "%d\n", &set[i].songCount);
            for (int j = 0; j < set[i].songCount; j++)
            {
                fscanf(fp, " %[^\n]s", set[i].arraySong[j].songTitle);
                fscanf(fp, " %[^\n]s", set[i].arraySong[j].artist);
                fscanf(fp, " %[^\n]s", set[i].arraySong[j].album);
            }
        }
        printf("\nSuccessfully load the data!\n");
        fclose(fp);
    }
}