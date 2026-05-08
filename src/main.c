#include "raylib.h"
#include "player.h"
#include "maploader.h"

Vector2 playerInput = {0, 0};
char mapArray[28][36];

void DrawDebug(void);
void PlayerMove(void);

int main(void){
	bool showDebug = true;
	bool playerEnabled = true;
	
	//Double the native Pacman resolution because modern displays duh
	const Vector2 screenSize = {448, 576};

	InitWindow(screenSize.x, screenSize.y, "PacClone");
	SetTargetFPS(60);

	initMapData();
	
	
	while(!WindowShouldClose()){
		if(playerEnabled){updatePlayer();}
		
		BeginDrawing();
			loadMap();
			if(playerEnabled){drawPlayer();}

			//Always debug render at end so it draws over everything
			if(showDebug){DrawDebug();}	
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

void DrawDebug(){
	ClearBackground(BLACK);
	DrawText(TextFormat("PX: %.0f PY: %.0f", playerInput.x, playerInput.y), 0, 0, 10, LIGHTGRAY);
}
