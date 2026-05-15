#include "raylib.h"
#include "main.h"
#include "maploader.h"
#include <stdio.h>

void updatePlayer(void);
void drawPlayer(void);

Color playerDebugColor = {255, 0, 0, 50};
Vector2 playerPos = {100, 90};
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

    /**
     * Braindead easy, funny I struggled to come up with this.
     * Game just runs the collision ahead of time and if it collides don't move the player
     */
    Rectangle hitWall;
    Vector2 futureLocation = {  
                                playerPos.x + playerDir.x * GetFrameTime() * speed, 
                                playerPos.y + playerDir.y * GetFrameTime() * speed
                            };
    Rectangle futurePlayerRect = {futureLocation.x-16, futureLocation.y-16, 32, 32};
    bool canMove = true;
    for(int i = 0; i < wallsCount; i++){
        colliding = CheckCollisionRecs(futurePlayerRect, walls[i]);
        if(colliding){
            hitWall = walls[i];
            canMove = false;
            break;
        }
    }
    if(canMove){
        playerPos.x += playerDir.x * GetFrameTime() * speed;
        playerPos.y += playerDir.y * GetFrameTime() * speed;
        playerRect = (Rectangle){playerPos.x-16, playerPos.y-16, 32, 32};
    }
}

void drawPlayer(){
    DrawCircleV(playerPos, 16, YELLOW);
    if(showDebug){
        DrawRectangleRec(playerRect, playerDebugColor);
    }
}