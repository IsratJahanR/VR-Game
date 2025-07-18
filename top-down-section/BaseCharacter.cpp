#include "BaseCharacter.h"
#include "raymath.h"
BaseCharacter::BaseCharacter()
{

}
void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}
Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width*scale,
        height*scale 
    };
}
void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;
    // Update Animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrame)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        // set worldPos = worldPos + velocity
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

    velocity = {};

    // Draw the character
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dst{getScreenPos().x, getScreenPos().y, scale * width, scale * height};

    DrawTexturePro(texture, source, dst, Vector2{}, 0.f, WHITE);
}
