#include "bullet.hpp"
#include <iostream>

Bullet::Bullet(Vector2 position, int speed)
{
    this -> position = position;
    this -> speed = speed;
    active = true;
}

void Bullet::Draw() {
    if(active)
        DrawRectangle(position.x, position.y, 6, 6, DARKBROWN);
}

Rectangle Bullet::getRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 6;
    rect.height = 6;
    return rect;
}

//Step 6. What if bullet goes out of screen?
void Bullet::Update() {
    position.y += speed;
    if(active) {
        //if Bullet goes out of screen
        if(position.y > GetScreenHeight() - 100 || position.y < 25) {
            active = false; 
        }
    }
}
