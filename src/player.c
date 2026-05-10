#include "raylib.h"
#include "main.h"
#include "maploader.h"
#include <stdio.h>
#include <math.h>

void updatePlayer(void);
void drawPlayer(void);

Color playerDebugColor = {255, 0, 0, 50};
Vector2 playerPos = {90, 90};
Vector2 playerDir = {0, 0};
Rectangle playerRect;
bool colliding;


float speed = 100.0;
float collisionDir;

void updatePlayer(){
    //Hacky asf, idk what I'm doing.
    //Player can only move in one direction at a time so hacky code prevents diags.
    playerInput.x = 0;
    playerInput.y = 0;
    collisionDir = 0;
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

    bool canMoveX = true;
    bool canMoveY = true;
    Rectangle hitWall;
    
    /*
    TODO: Note for me later so I don't forget what the solution is.

    I basically have to check for both the X and Y axis for will the player WILL be and then if they collide
    0 out the player movement in that direction

    My brain is a bit too fried to finish this up right now
    */

    for(int i = 0; i < wallsCount; i++){
        colliding = CheckCollisionRecs(playerRect, walls[i]);
        if(colliding){
            hitWall = walls[i];
            /*
            Was a bit too complicated and needless when I should be able to predict the collisions. Keeping this here for now just in case
            Inb4 this was the right solution all along...

            float playerCenterX = playerRect.x + playerRect.width / 2;
            float playerCenterY = playerRect.y + playerRect.height / 2;
            float wallCenterX = hitWall.x + hitWall.width / 2;
            float wallCenterY = hitWall.y + hitWall.height / 2;
            float colX = (wallCenterX - playerCenterX);
            float colY = (wallCenterY - playerCenterY);
            collisionDir = ((atan2(colY, colX) * 180/PI));
            */

            if(playerDir.x != 0) canMoveX = false;
            if(playerDir.y != 0) canMoveY = false;
            printf("Collision Direction: %f \n", collisionDir);
            break;
        }
    }
    if(canMoveX) playerPos.x += GetFrameTime() *playerDir.x * speed;
    if(canMoveY) playerPos.y += GetFrameTime() *playerDir.y * speed;
    playerRect = (Rectangle){playerPos.x-16, playerPos.y-16, 32, 32};
}

void drawPlayer(){
    DrawCircleV(playerPos, 16, YELLOW);
    if(showDebug){
        DrawRectangleRec(playerRect, playerDebugColor);
    }
}