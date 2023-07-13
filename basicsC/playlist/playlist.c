#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int main(){
    typedef struct{
         char songTitle[30];
         char artist[30];
         char album[30];
    } song;
    
    typedef struct{
        char playlistName[30];
        int songCount;
        song arraySong[10];

    } playlist;
    return 0;
}