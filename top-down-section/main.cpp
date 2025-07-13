#include "raylib.h"
#include "raymath.h"


int main()
{
    // Initilize window size 
    const int width{384};
    const int height{384};
    InitWindow(width,height,"Stephen's Top Down!");


    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24X24.png");
    Vector2 mapPos{0.0,0.0};
   
  
    SetTargetFPS(50);

    while(!WindowShouldClose())
    {
        // delta time (time since last frame)
        const float dT{GetFrameTime()};
        //Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};

        if(IsKeyDown(KEY_A))direction.x-=1.0;
        if(IsKeyDown(KEY_D))direction.x+=1.0;
        if(IsKeyDown(KEY_W))direction.y-=1.0;
        if(IsKeyDown(KEY_S))direction.y+=1.0;

        if(Vector2Length(direction)!=0.0)
        {
            // set mapPos = mapPos - direction
            mapPos = Vector2Subtract(mapPos,Vector2Normalize(direction));

        }


        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);
        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}