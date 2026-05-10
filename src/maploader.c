#include "raylib.h"
#include <stdio.h>
#include "main.h"

void loadMap(void);
int initData();

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

void loadMap(){
    int drawnBoxes = 0;
    for (int hRows = 0; hRows < 28; hRows++){
        for (int vRows = 0; vRows < 36; vRows++){
            if(mapArray[hRows][vRows] == '1'){
                drawnBoxes += 1;
                DrawRectangle(hRows * 16, vRows * 16, 16, 16, BLUE);
            }
        }
    }
}