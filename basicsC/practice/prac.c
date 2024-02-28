#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct song_tag{
    char title[50];
    char writer[50];
    char genre[50];
    struct song_tag *nextSong;

}SONGS;
typedef struct playlist_tag{
    char playlistName[50];
    int numSong;
    SONGS *songHead;
    struct playlist_tag *next;
    

}PLAYLIST;

char menu(){
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

int main(){

    PLAYLIST *head = NULL;
    int playlistNum = 0;

    while(1){
        char choice = menu();
        switch(choice){
            case '1':
                printf("\n1\n");
        }
    }
    return 0;
}