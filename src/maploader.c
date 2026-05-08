#include "raylib.h"
#include <stdio.h>
#include "main.h"

void loadMap(void);
int initData();

int initMapData() {
    FILE *dataFile = fopen("data/test.txt", "rb");
    if (dataFile == NULL) return 1;

    for (int j = 0; j < 36; j++){
        for (int i = 0; i < 28; i++){
            int c = fgetc(dataFile);

            if (c == EOF){
                mapArray[i][j] = '0';
            }else if(c == '\n' || c == '\r'){
                i--;
            } else{
                mapArray[i][j] = (char)c;
            }
        }
    }
    printf("Map Data Loaded!\n");
    fclose(dataFile);
    return 0;
}

void loadMap(){
    int drawnBoxes = 0;
    for (int i = 0; i < 28; i++){
        for (int j = 0; j < 36; j++){
            if(mapArray[i][j] == '1'){
                drawnBoxes += 1;
                DrawRectangle(i * 16, j * 16, 16, 16, BLUE);
            }
        }
    }
}