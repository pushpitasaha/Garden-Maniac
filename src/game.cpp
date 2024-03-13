#include "game.hpp"
#include <iostream>
#include <fstream>

Game::Game()
{
    //Step 15. Loading the audio
    bgmusic = LoadMusicStream("audio/bgmusic.mp3");
    impactSound = LoadSound("audio/impact.wav");
    PlayMusicStream(bgmusic);
    InitGame();
}

Game::~Game() {
    Animal::UnloadImages();
    UnloadMusicStream(bgmusic);
    UnloadSound(impactSound);
}

void Game::Update() {
    if(run) {

        double currentTime = GetTime();

        //Step 9. How’s the bat getting spawned? Paste the if-statement below.
        if(currentTime - timeLastSpawn > batSpawnInterval) {
            bat.Spawn();
            timeLastSpawn = GetTime();
            batSpawnInterval = GetRandomValue(9, 18);
        }

        for(auto& bullet: shroom.bullets) {
            bullet.Update();
        }

        MoveAnimals();

       AnimalShootBullet();

        for(auto& bullet: animalBullets) {
            bullet.Update();
        }

        DeleteInactiveBullets();
        
        bat.Update();

        CheckForCollisions();
    } else {
        if(IsKeyDown(KEY_ENTER)){
            Reset();
            InitGame();
        }
    }
}

void Game::Draw() {
    shroom.Draw();

    for(auto& bullet: shroom.bullets) {
        bullet.Draw();
    }

    for(auto& diamond: diamonds) {
        diamond.Draw();
    }

    for(auto& animal: animals) {
        animal.Draw();
    }

    for(auto& bullet: animalBullets) {
        bullet.Draw();
    }

    bat.Draw();
}

//Step 5. Event Handling
void Game::HandleInput() {
    if(run){
        if(IsKeyDown(KEY_LEFT)) {
            shroom.MoveLeft();
        } else if (IsKeyDown(KEY_RIGHT)){
            shroom.MoveRight();
        } else if (IsKeyDown(KEY_SPACE)) {
            shroom.FireBullet();
        }
    }
}

void Game::DeleteInactiveBullets()
{
    for(auto it = shroom.bullets.begin(); it != shroom.bullets.end();){
        if(!it -> active) {
            it = shroom.bullets.erase(it);
        } else {
            ++ it;
        }
    }

    for(auto it = animalBullets.begin(); it != animalBullets.end();){
        if(!it -> active) {
            it = animalBullets.erase(it);
        } else {
            ++ it;
        }
    }
}

//After learning about grids, come here
std::vector<Diamond> Game::CreateDiamonds()
{
    int diamondWidth = Diamond::grid[0].size() * 4;

    //Step 8. Explaining the gap: Placing 3 diamonds
    float gap = (GetScreenWidth() - (3 * diamondWidth))/4;

    for(int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gap + i * diamondWidth;
        diamonds.push_back(Diamond({offsetX, float(GetScreenHeight() - 200)}));
    }
    return diamonds;
}

//Step 10: create animals method is implemented here. snake, bluebird, and pig has the type of 1, 2, and 3.
std::vector<Animal> Game::CreateAnimals()
{
    std::vector<Animal> animals;
    for(int row = 0; row < 5; row++) {
        for(int column = 0; column < 15; column++) {

            int animalType;
            if(row == 0) {
                animalType = 3;
            } else if (row == 1 || row == 2) {
                animalType = 2;
            } else {
                animalType = 1;
            }

            float x = 75 + column * 42;
            float y = 110 + row * 42;
            animals.push_back(Animal(animalType, {x, y}));
        }
    }
    return animals;
}

void Game::MoveAnimals() {
    for(auto& animal: animals) {
        if(animal.position.x + animal.animalImages[animal.type - 1].width > GetScreenWidth() - 25) {
            animalsDirection = -1;
            MoveDownAnimals(4);
        }
        if(animal.position.x < 25) {
            animalsDirection = 1;
            MoveDownAnimals(4);
        }

        animal.Update(animalsDirection);
    }
}

void Game::MoveDownAnimals(int distance)
{
    for(auto& animal: animals) {
        animal.position.y += distance;
    }
}

void Game::AnimalShootBullet()
{
    double currentTime = GetTime();
    if(currentTime - timeLastAnimalFired >= animalBulletShootInterval && !animals.empty()) {
        int randomIndex = GetRandomValue(0, animals.size() - 1);
        Animal& animal = animals[randomIndex];
        animalBullets.push_back(Bullet({animal.position.x + animal.animalImages[animal.type -1].width/2, 
                                    animal.position.y + animal.animalImages[animal.type - 1].height}, 6));
        timeLastAnimalFired = GetTime();
    }
}

//Step11. Check for each collision cases
void Game::CheckForCollisions()
{
    //Case: 1 Shroom's Bullets x Animal -> Score++
    for(auto& bullet: shroom.bullets) {
        auto it = animals.begin();
        while(it != animals.end()){
            if(CheckCollisionRecs(it -> getRect(), bullet.getRect()))
            {
                PlaySound(impactSound);
                if(it -> type == 1) {
                    score += 50;
                } else if (it -> type == 2) {
                    score += 200;
                } else if(it -> type == 3) {
                    score += 500;
                }
                checkForHighscore();

                it = animals.erase(it);
                bullet.active = false;
            } else {
                ++it;
            }
        }
    //Case 2. Diamond x Shroom's Bullet -> Erase
        for(auto& diamond: diamonds){
            auto it = diamond.tiles.begin();
            while(it != diamond.tiles.end()){
                if(CheckCollisionRecs(it -> getRect(), bullet.getRect())){
                    it = diamond.tiles.erase(it);
                    bullet.active = false;
                } else {
                    ++it;
                }
            }
        }

        if(CheckCollisionRecs(bat.getRect(), bullet.getRect())){
            bat.alive = false;
            bullet.active = false;
            score += 1000;
            checkForHighscore();
            PlaySound(impactSound);
        }
    }

    //case 3. Animal's Bullet x Shroom -> lives--
    for(auto& bullet: animalBullets) {
        if(CheckCollisionRecs(bullet.getRect(), shroom.getRect())){
            bullet.active = false;
            lives --;
            if(lives == 0) {
                GameOver();
            }
        }
    //Case 4. Diamond x Animal's Bullets -> erase
          for(auto& diamond: diamonds){
            auto it = diamond.tiles.begin();
            while(it != diamond.tiles.end()){
                if(CheckCollisionRecs(it -> getRect(), bullet.getRect())){
                    it = diamond.tiles.erase(it);
                    bullet.active = false;
                } else {
                    ++it;
                }
            }
        }
    }

    //Case 5. Animal Collision with Diamond -> erase
    for(auto& animal: animals) {
        for(auto& diamond: diamonds) {
            auto it = diamond.tiles.begin();
            while(it != diamond.tiles.end()) {
                if(CheckCollisionRecs(it -> getRect(), animal.getRect())) {
                    it = diamond.tiles.erase(it);
                } else {
                    it ++;
                }
            }
        }
        //Case 6. Animals touches Shroom -> GameOver
        if(CheckCollisionRecs(animal.getRect(), shroom.getRect())) {
            GameOver();
        }
    }
}

//Step 11. Gameover State = stop running. The update method and event handling only happens if run is true.
void Game::GameOver()
{
    run = false;
}

void Game::InitGame()
{
    diamonds = CreateDiamonds();
    animals = CreateAnimals();
    animalsDirection = 1;
    timeLastAnimalFired = 0.0;
    timeLastSpawn = 0.0;
    lives = 3;
    score = 0;
    highscore = loadHighscoreFromFile();
    run = true;
    batSpawnInterval = GetRandomValue(10, 20);
}

//Step 14. if current score is greater than prev highscore then we update the high score.
void Game::checkForHighscore()
{
    if(score > highscore) {
        highscore = score;
        saveHighscoreToFile(highscore);
    }
}

void Game::saveHighscoreToFile(int highscore)
{
    std::ofstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()) {
        highscoreFile << highscore;
        highscoreFile.close();
    } else {
        std::cerr << "Failed to save highscore to file" << std::endl;
    }
}

int Game::loadHighscoreFromFile() {
    int loadedHighscore = 0;
    std::ifstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()) {
        highscoreFile >> loadedHighscore;
        highscoreFile.close();
    } else {
        std::cerr << "Failed to load highscore from file." << std::endl;
    }
    return loadedHighscore;
}

void Game::Reset() {
    shroom.Reset();
    animals.clear();
    animalBullets.clear();
    diamonds.clear();
}
