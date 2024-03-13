#include "animal.hpp"

Texture2D Animal::animalImages[3] = {};

Animal::Animal(int type, Vector2 position)
{
    this -> type = type;
    this -> position = position;

    if(animalImages[type -1].id == 0){

    switch (type) {
        case 1:
            animalImages[0] = LoadTexture("assets/snake.png");
            break;
        case 2:
            animalImages[1] = LoadTexture("assets/pig.png");
            break;
        case 3: 
            animalImages[2] = LoadTexture("assets/bluebird.png");
            break;
        default:
            animalImages[0] = LoadTexture("assets/snake.png");
            break;
    }
}
}

void Animal::Draw() {
    DrawTextureV(animalImages[type - 1], position, WHITE);
}

int Animal::GetType() {
    return type;
}

void Animal::UnloadImages()
{
    for(int i = 0; i < 4; i++) {
        UnloadTexture(animalImages[i]);
    }
}

Rectangle Animal::getRect()
{
    return {position.x, position.y,
    float(animalImages[type - 1].width),
    float(animalImages[type - 1].height)
    };
}

void Animal::Update(int direction) {
    position.x += direction;
}
