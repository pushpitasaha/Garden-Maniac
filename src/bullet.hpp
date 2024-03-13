#pragma once
#include <raylib.h>

class Bullet {
    public:
        Bullet(Vector2 position, int speed);
        void Update();
        void Draw();
        Rectangle getRect();
        bool active;
    private:
        Vector2 position;
        int speed;
};