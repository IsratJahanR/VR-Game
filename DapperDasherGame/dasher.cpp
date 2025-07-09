#include "raylib.h"
#include<stdio.h>


int main()
{
    // Initilize window
    const int width{512};
    const int height{380};
    InitWindow(width,height,"Dapper Dasher!");
    
    //Rectangle Dimension
    const int w{50};
    const int h{80};
    int posY{height-h};
    int velocity{0};

    //acceleration due to gravity (pixels/frame)/frame
    const int gravity{1};

    //is the rectangle in air????
    bool isInAir{};





    SetTargetFPS(50);

    while(!WindowShouldClose())
    {
        //Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        //perform ground check
        if(posY>=height-h)
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

        if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity-=10;
        }

        

        //Update position
        posY +=velocity;


        DrawRectangle(width/2,posY,w,h,BLUE);

        //Stop Drawing
        EndDrawing();
    }
    CloseWindow();
}