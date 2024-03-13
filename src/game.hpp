#pragma once
#include "shroom.hpp"
#include "diamond.hpp"
#include "animal.hpp"
#include "bat.hpp"

class Game {
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        bool run;
        int lives;
        int score;
        int highscore;
        Music bgmusic;
    private:
        void DeleteInactiveBullets();
        std::vector<Diamond> CreateDiamonds();
        std::vector<Animal> CreateAnimals();
        void MoveAnimals();
        void MoveDownAnimals(int distance); 
        void AnimalShootBullet();
        void CheckForCollisions();
        void GameOver();
        void Reset();
        void InitGame();
        void checkForHighscore();
        void saveHighscoreToFile(int highscore);
        int loadHighscoreFromFile();
        Shroom shroom;
        std::vector<Diamond> diamonds;
        std::vector<Animal> animals;
        int animalsDirection;
        std::vector<Bullet> animalBullets;
        constexpr static float animalBulletShootInterval = 0.35;
        float timeLastAnimalFired;
        Bat bat;
        float batSpawnInterval;
        float timeLastSpawn;
        Sound impactSound;
};