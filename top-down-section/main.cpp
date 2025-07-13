#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include "raylib.h"

int main()
{
    // Initilize window size
    const int winWidth{384};
    const int winHeight{384};
    InitWindow(winWidth, winHeight, "Stephen's Top Down!");

    // Draw map
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24X24.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character knight(winWidth, winHeight);

    Prop props[2]{
        Prop{Vector2{600.f,300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f,500.f}, LoadTexture("nature_tileset/Log.png")}
    };

    Enemy goblin{
        Vector2{0.f,0.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };
    goblin.setTarget(&knight);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        //Draw the pops
        for(auto prop: props)
        {
            prop.Render(knight.getWorldPos());
        }
        
        knight.tick(GetFrameTime());
        //Check Map Bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + winWidth > map.width * mapScale ||
            knight.getWorldPos().y + winHeight > map.height * mapScale

        )
        {
            knight.undoMovement();
        }
         
        for(auto prop: props)
        {
            if(CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()),knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }
        goblin.tick(GetFrameTime());
        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}