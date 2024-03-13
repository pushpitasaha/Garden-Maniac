#pragma once
#include <raylib.h>
#include "bullet.hpp"
#include <vector>

class Shroom{
    public:
        Shroom();
        ~Shroom();
        void Draw();
        void MoveLeft();
        void MoveRight();
        void FireBullet();
        Rectangle getRect();
        void Reset();
        std::vector<Bullet> bullets;

    private:
        Texture2D image;
        Vector2 position;
        double lastFireTime;
        Sound bulletSound;
};