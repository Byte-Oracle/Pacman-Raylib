#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void loadMap(void);
int initData();

Rectangle *walls = NULL;
int wallsCount = 0;

int initMapData() {
    FILE *dataFile = fopen("data/test.txt", "rb");
    if (dataFile == NULL) return 1;

    for (int vRows = 0; vRows < 36; vRows++){
        for (int hRows = 0; hRows < 28; hRows++){
            int c = fgetc(dataFile);

            if (c == EOF){
                mapArray[hRows][vRows] = '0';
            }else if(c == '\n' || c == '\r'){
                hRows--;
            } else{
                mapArray[hRows][vRows] = (char)c;
            }
        }
    }
    printf("Map Data Loaded!\n");
    fclose(dataFile);
    return 0;
}

void addWall(Rectangle newWall){
    walls = (Rectangle *)realloc(walls, (wallsCount + 1) * sizeof(Rectangle));
    walls[wallsCount] = newWall;
    wallsCount++;
}

void loadMap(){
    int drawnBoxes = 0;
    for (int hRows = 0; hRows < 28; hRows++){
        for (int vRows = 0; vRows < 36; vRows++){
            if(mapArray[hRows][vRows] == '1'){
                Rectangle newWall = {hRows * 16, vRows * 16, 16, 16};
                addWall(newWall);
                drawnBoxes += 1;
                DrawRectangleRec(newWall, BLUE);
            }
        }
    }
}