#include "raylib.h"
#include "main.h"

void updatePlayer(void);
void drawPlayer(void);

Vector2 playerPos = {0, 0};
Vector2 playerDir = {0, 0};

float speed = 100.0;

void updatePlayer(){
    //Hacky asf, idk what I'm doing.
    //Player can only move in one direction at a time so hacky code prevents diags.
    playerInput.x = 0;
    playerInput.y = 0;
    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)){
        playerInput.x = 1;
    }
    else if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)){
        playerInput.x = -1;
    }
    if(playerInput.x == 0){
        if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
            playerInput.y = -1;
        }
        else if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
            playerInput.y = 1;
        }
    }

    if(playerInput.x != 0){
        playerDir.x = playerInput.x;
        playerDir.y = 0;
    }else if(playerInput.y != 0){
        playerDir.y = playerInput.y;
        playerDir.x = 0;
    }

    playerPos.x += GetFrameTime() *playerDir.x * speed;
    playerPos.y += GetFrameTime() *playerDir.y * speed;
}

void drawPlayer(){
    DrawCircleV(playerPos, 10, YELLOW);
}