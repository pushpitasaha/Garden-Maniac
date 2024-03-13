#include "shroom.hpp"

Shroom::Shroom()
{
    image = LoadTexture("assets/shroom.png");
    //Shroom coordinates
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height - 100;
    lastFireTime = 0.0;
    bulletSound = LoadSound("audio/bullet.wav");
}

Shroom::~Shroom() {
    UnloadTexture(image);
    UnloadSound(bulletSound);
}

//On Draw() method call Shroom shows up on screen
void Shroom::Draw() {
    DrawTextureV(image, position, WHITE);
}

//Step 4. Setting up shroom's Horizontal Movements Only
void Shroom::MoveLeft() {
    //think of how the x coord is changing
    position.x -= 6;
    //limiting area
    if(position.x < 25) {
        position.x = 25;
    }
}

void Shroom::MoveRight() {
    //think of how the x coord is changing
    position.x += 6;
    //limiting area
    if(position.x > GetScreenWidth() - image.width - 25) {
        position.x = GetScreenWidth() - image.width - 25;
    }
}

void Shroom::FireBullet()
{
    if(GetTime() - lastFireTime >= 0.35) {
        bullets.push_back(Bullet({position.x + image.width/2 - 2,position.y},-6));
        lastFireTime = GetTime();
        PlaySound(bulletSound);
    }
}

Rectangle Shroom::getRect()
{
    return {position.x, position.y, float(image.width), float(image.height)};
}

void Shroom::Reset()
{
    position.x = (GetScreenWidth() - image.width)/ 2.0f;
    position.y = GetScreenHeight() - image.height - 100;
    bullets.clear();
}
