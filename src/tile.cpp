#include "tile.hpp"

Tile::Tile(Vector2 position)
{
    this -> position = position;
}

//Step 7. Implementing tiles as rect. Hover on DrawRectangle() method to know its arguments
void Tile::Draw() {
    DrawRectangle(position.x, position.y, 4, 4, DARKBROWN);
}

Rectangle Tile::getRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 4;
    rect.height = 4;
    return rect;
}
