//
// CCID's: mies, vonlipin
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    SONG,
    PODCAST
} AudioType;


typedef struct {
    char* audio;
    char *creator;
    AudioType type;
} AudioData;

int A(AudioData *playlist, int *playlistLen, AudioType type, char *name, char *creatorName);
void P(AudioData* playlist, int playLen, char* name);
void R(AudioData* playlist, int* playLen, char* name);

int main(void){
    int playlistLen = 1;
    AudioData* playlist = (AudioData*)malloc(playlistLen * sizeof(AudioData));
    int run = 1;
    char* curLine = malloc(180 * sizeof(char));
    char audioName[100];
    char creatorName[30];
    char audioType[8];

    while (run) {
        fgets(curLine, 180, stdin);

        if (strncmp(curLine, "A", 1) == 0) {
            sscanf("A %s %s %s", audioType, audioName, creatorName);
            if (A(playlist, &playlistLen, *audioType, audioName, creatorName) == 0) {
                break;
            }

            while (getchar() != '\n'){}
        }
        else if (strncmp(curLine, "P", 1) == 0) {
            sscanf("P %s", audioName);
            P(playlist, playlistLen, audioName);

            while (getchar() != '\n'){}
        }
        else if (strncmp(curLine, "R", 1) == 0) {
            sscanf("R %s", audioName);
            R(playlist, &playlistLen, audioName);
        }
        else if (strncmp(curLine, "E", 1) == 0) {
            run = 0;
        }

    }

    free(playlist);
    free(curLine);
    return 0;
}

int A(AudioData *playlist, int *playlistLen, AudioType type, char *name, char *creatorName) {
    *playlistLen++;
    AudioData* temp = (AudioData*)realloc(playlist, *playlistLen * sizeof(AudioData));
    if (temp == NULL)
    {
        return 0;
    }
    playlist = temp;

    playlist[*playlistLen].audio = name;
    playlist[*playlistLen].creator = creatorName;
    playlist[*playlistLen].type = type;

    return 1;
}

void P(AudioData* playlist, int playLen, char* name){
    //search
    for(int i = 0; i< playLen; i++){
        if(strcmp((playlist + i)->audio, name)==0 && (playlist+i)->type == 1){
            printf("Playing %s hosted by %s\n", name, (playlist+i)->creator);
            break;
            }
        if(strcmp((playlist + i)->audio, name)==0){
            printf("Playing %s by %s\n", name, (playlist+i)->creator);
            break;
        }
    }
}

void R(AudioData* playlist, int* playLen, char* name){
    for(int i = 0; i < *playLen; i++){
        if(strcmp((playlist + i)->audio, name)==0 && (playlist+i)->type == 1){
            printf("Removed %s hosted by %s\n", name, (playlist+i)->creator);
            free(playlist + i);
            break;

            }
        else if(strcmp((playlist + i)->audio, name)==0){
            printf("Removed %s by %s\n", name, (playlist+i)->creator);
            free(playlist + i);
            break;
            }
        }
    *playLen--;
}


