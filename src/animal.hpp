#pragma once
#include <raylib.h>

class Animal{
    public:
        Animal(int type, Vector2 position);
        void Update(int direction);
        void Draw();
        int GetType();
        static void UnloadImages();
        Rectangle getRect();
        static Texture2D animalImages[3];
        int type;
        Vector2 position;
    private:
};