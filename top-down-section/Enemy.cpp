#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width / maxFrame;
    height = texture.height;
    speed = 3.5f;
}
void Enemy :: tick(float deltaTime)
{
    if(!getAlive())return;
    //get toTarget
    velocity = Vector2Subtract(target->getScreenPos(),getScreenPos());
    if(Vector2Length(velocity) < radius)velocity = {};
    BaseCharacter::tick(deltaTime);

    if(CheckCollisionRecs(target -> getCollisionRec(), getCollisionRec()))
    {
        target -> takeDamage(damagePerSec * deltaTime);
    }
}
Vector2 Enemy:: getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());

}