#include "raylib.h"
#include "main.h"
#include "maploader.h"
#include <stdio.h>

void updatePlayer(void);
void drawPlayer(void);

Color playerDebugColor = {255, 0, 0, 50};
Vector2 playerPos = {100, 150};
Vector2 playerDir = {0, 0};
Rectangle playerRect;
bool colliding;
int playerSize = 16;
int halfPlayerSize = 8;


float speed = 100.0;
float collisionDir;

//TODO: Works for now but in the original they do not allow the player to change direction if there is a wall in way letting the player just hold the direction
// and smoothly roll around corners
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
    float deltaTime = GetFrameTime();

    Vector2 delta = {playerDir.x * speed * deltaTime, playerDir.y * speed* deltaTime};
    Vector2 futureLocation = {  
                                playerPos.x + delta.x, 
                                playerPos.y + delta.y
                            };
    Rectangle futurePlayerRect = {futureLocation.x-(halfPlayerSize), futureLocation.y-(halfPlayerSize), playerSize, playerSize};
    bool collided = false;
    for(int i = 0; i < wallsCount; i++){
        if (CheckCollisionRecs(futurePlayerRect, walls[i])) {
            //Snaps player to wall with difference between player and wall allowing for perfect fits
            collided = true;
            if (delta.x > 0) {
                playerPos.x = walls[i].x - halfPlayerSize;
            } else if (delta.x < 0) {
                playerPos.x = walls[i].x + walls[i].width + halfPlayerSize;
            } else if (delta.y > 0) {
                playerPos.y = walls[i].y - halfPlayerSize;
            } else if (delta.y < 0) {
                playerPos.y = walls[i].y + walls[i].height + halfPlayerSize;
            }
            break;
        }
    }
    if(!collided){
        playerPos.x += delta.x;
        playerPos.y += delta.y;   
    }
    playerRect = (Rectangle){playerPos.x-halfPlayerSize, playerPos.y-halfPlayerSize, playerSize, playerSize};
}

void drawPlayer(){
    DrawCircleV(playerPos, halfPlayerSize, YELLOW);
    if(showDebug){
        DrawRectangleRec(playerRect, playerDebugColor);
    }
}