#include "raylib.h"

struct Anim
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};
bool isOnGround(Anim data, int windowHeight)
{
    return data.pos.y>=windowHeight-data.rec.height;
}

bool checkCollision(Rectangle r1, Rectangle r2)
{
 return true;
}

Anim updateAnim(Anim Data, float deltaTIme, int maxFrame)
{
     Data.runningTime+=deltaTIme;
     if(Data.runningTime>=Data.updateTime)
     {
        Data.runningTime = 0.0;
        Data.rec.x = Data.frame*Data.rec.width;
        Data.frame++;
        Data.frame%=maxFrame;
                
    }
    return Data;
}

int main()
{
    // Initilize window size 
    int windowDim[2] = {512, 380};
   
    InitWindow(windowDim[0],windowDim[1],"Dapper Dasher!");

    //Nebula Texture
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    int nebulaeSize = 5;
    Anim nebulae[nebulaeSize]{};
    for(int i=0;i<nebulaeSize;i++)
    {
        //nebulae[i].rec{0.0, 0.0, nebula.width/8, nebula.height/8};
        nebulae[i].rec.x = 0.0; nebulae[i].rec.y = 0.0; nebulae[i].rec.width = nebula.width/8; nebulae[i].rec.height = nebula.height/8;
        //nebulae[i].pos{windowDim[0]+i*200,windowDim[1]-nebula.height/8};
        nebulae[i].pos.x = windowDim[0]+i*300;  nebulae[i].pos.y = windowDim[1]-nebula.height/8;
        nebulae[i].frame=0;
        nebulae[i].updateTime=1.0/16.0;
        nebulae[i].runningTime=0.0;
    }

    float finishLine{nebulae[nebulaeSize-1].pos.x};
    //Scarfy Texture
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Anim scarfyData{
        {0.0, 0.0, scarfy.width/6, scarfy.height}, //Rectangle rec
        {windowDim[0]/2 - scarfy.width/6,windowDim[1]/2 - scarfy.height}, // Vector2 pos
        0, // int frame
        1.0/12.0, // float updateTime
        0 // float runningTime
    };
    int nebVel{-200};
    int velocity{0};
    const int gravity{1'000}; //acceleration due to gravity (pixels/s)/s
    bool isInAir{}; //is the rectangle in air????
    const int jumpVel{-600}; //jump velocity (pixel/s)

    
    //Texture Variables
    Texture background = LoadTexture("textures/far-buildings.png");
    float bgX{};
    Texture midground = LoadTexture("textures/back-buildings.png");
    float mgX{};
    Texture foreground = LoadTexture("textures/foreground.png");
    float fgX{};

    bool collision{};
    SetTargetFPS(50);

    while(!WindowShouldClose())
    {
        // delta time (time since last frame)
        const float dT{GetFrameTime()};
        //Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);
 
        bgX -=20*dT;
        if(bgX <= -background.width*2)bgX = 0.0;

        mgX -= 40*dT;
        if(mgX <= -midground.width*2)mgX = 0.0;

        fgX -= 80*dT;
        if(fgX <= -foreground.width*2)fgX = 0.0; 

        //Set Background 
        Vector2 bgPos{bgX,0.0};
        DrawTextureEx(background,bgPos, 0.0, 2.0, WHITE);
        Vector2 bg1Pos{bgX+background.width*2,0.0};
        DrawTextureEx(background,bg1Pos, 0.0, 2.0, WHITE);

        Vector2 mgPos{mgX,0.0};
        DrawTextureEx(midground,mgPos, 0.0, 2.0, WHITE);
        Vector2 mg1Pos{mgX+midground.width*2,0.0};
        DrawTextureEx(midground,mg1Pos, 0.0, 2.0, WHITE);

        Vector2 fgPos{fgX,0.0};
        DrawTextureEx(foreground,fgPos, 0.0, 2.0, WHITE);
        Vector2 fg1Pos{fgX+foreground.width*2,0.0};
        DrawTextureEx(foreground,fg1Pos, 0.0, 2.0, WHITE);

        //perform ground check
        if(isOnGround(scarfyData,windowDim[1]))
        {
            velocity = 0;
            isInAir = false;
        } 
        else 
        {
            //rectangle is on the air  //apply gravity
            velocity +=gravity*dT;
            isInAir = true;
        }

        //Jump check
        if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity +=jumpVel;
        }
        //Update nebula Position
        for(int i = 0;i<nebulaeSize;i++)
        {
            nebulae[i].pos.x +=nebVel*dT;
        }
        finishLine += nebVel*dT;

        //Update scarfy position
        scarfyData.pos.y +=velocity*dT;

        //Update scarfy animation
        if(!isInAir){
           scarfyData = updateAnim(scarfyData, dT, 5);   
        }
        //Update nebula animation frame
        for(int i = 0;i<nebulaeSize;i++)
        {
            nebulae[i] = updateAnim(nebulae[i], dT, 8);
        }
        for(Anim nebula : nebulae)
        {
            float pad{50};
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width -2*pad,
                nebula.rec.height-2*pad
            };
            Rectangle scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height
            };
            if(CheckCollisionRecs(nebRec,scarfyRec))
            { 
                collision = true;
            }
        }
        if(collision)
        {
            // lose the game 
            DrawText("Game Over! ", windowDim[0]/4, windowDim[1]/2, 40, RED);

        }
        else if(scarfyData.pos.x>=finishLine)
        {
            //win the game
            DrawText("You Win! ", windowDim[0]/4, windowDim[1]/2, 40, RED);
        }
        else 
        {
            //Draw nabula
            for(int i = 0;i<nebulaeSize; i++)
            {
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, BLUE);
            }
            
            //Draw scarfy
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

            
        }
        //Stop Drawing
        EndDrawing();
        
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(midground);
    CloseWindow();
}