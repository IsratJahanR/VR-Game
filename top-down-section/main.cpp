#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include "raylib.h"
#include<string>

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
        Vector2{800.f,300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")
    };

    Enemy slime{
        Vector2{500.f,700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")
    };

    Enemy* enemies[]{
        &goblin,
        &slime
    };
    for(auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }
   

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

        if(knight.getAlive())
        {
            std::string knightHealth = "Health : ";
            float healthVal = knight.getHealth();
            knightHealth.append(std::to_string(healthVal), 0, 5);

            DrawText(knightHealth.c_str(),55.f, 45.f, 40, RED);
        }
        else{
            DrawText("game Over!",55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }

        
        for(auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for(auto enemy : enemies)
            {
                if(CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
            
        }
        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}