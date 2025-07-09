#include "raylib.h"
#include<stdio.h>


int main()
{
    // Initilize window size 
    const int width{512};
    const int height{380};
    InitWindow(width,height,"Dapper Dasher!");


    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    Vector2 scarfyPos;
    scarfyPos.x = width/2 - scarfyRec.width;
    scarfyPos.y = height/2 - scarfyRec.height;

    
    //Rectangle Dimension
    int velocity{0};

    //acceleration due to gravity (pixels/frame)/frame
    const int gravity{1};

    //is the rectangle in air????
    bool isInAir{};

    //jump velocity
    const int jumpVel{-22};





    SetTargetFPS(50);

    while(!WindowShouldClose())
    {
        //Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        //perform ground check
        if(scarfyPos.y>=height-scarfyRec.height)
        {
            //rectangle is on the ground
            velocity = 0;
            isInAir = false;
        } 
        else 
        {
            //rectangle is on the air
            //apply gravity
            velocity +=gravity;
            isInAir = true;
        }

        //Jump check
        if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity +=jumpVel;
        }

        

        //Update position
        scarfyPos.y +=velocity;


        DrawTextureRec(scarfy, scarfyRec, scarfyPos, RED);

        //Stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}