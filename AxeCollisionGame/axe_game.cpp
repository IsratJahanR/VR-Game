#include "raylib.h"
#include<stdio.h>


int main()
{
    int width{700};
    int height{500};
    InitWindow(width,height,"Hi this is iarat jahan Reshma");
    

    //Circle
    int circle_x{125};
    int circle_y{100};

    int radius{25};
    
    int circle_l_x{circle_x-radius};
    int circle_r_x{circle_x+radius};
    int circle_t_y{circle_y-radius};
    int circle_b_y{circle_y+radius};

    //Axe
    int axe_x{400};
    int axe_y{0};

    int axe_len{50};

    int axe_l_x{axe_x};
    int axe_r_x{axe_x+axe_len};
    int axe_t_y{axe_y};
    int axe_b_y{axe_y+axe_len};

    //Collision
    bool collision{false};

    int direction{10};

    SetTargetFPS(50);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if(circle_r_x<=axe_r_x && circle_l_x>=axe_l_x && circle_t_y>=axe_t_y && circle_b_y<=axe_b_y)collision=true;

        if(collision)
        {
            DrawText("Game Over",20,20,20,RED);
        }
        else 
        {
             DrawCircle(circle_x,circle_y,radius,BLUE);
            DrawRectangle(axe_x,axe_y,axe_len,axe_len,GREEN);

            axe_y+=direction;
            if(axe_y>height || axe_y<0)direction = -direction;

            
            if(IsKeyDown(KEY_D) && circle_x<width)
            {
                circle_x+=10;
            }
            if(IsKeyDown(KEY_A) && circle_x>0)
            {
                circle_x-=10;
            } 
            circle_l_x=circle_x-radius;
            circle_r_x=circle_x+radius;
            // circle_t_y=circle_y-radius;
            // circle_b_y=circle_y+radius;    

            // axe_l_x=axe_x;
            // axe_r_x=axe_x+axe_len;
            axe_t_y=axe_y;
            axe_b_y=axe_y+axe_len;

            printf("%d",circle_l_x);



        }

         
        EndDrawing();
    }
}