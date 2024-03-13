#pragma once
#include <raylib.h>

class Tile {
    public:
        Tile(Vector2 position);
        void Draw();
        Rectangle getRect();
    private:
        Vector2 position;
};