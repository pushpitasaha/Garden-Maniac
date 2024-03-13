#include <raylib.h>
#include "game.hpp"
#include <string>

std::string FormatWithLeadingZeros(int number, int width) {
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}

int main()
{ 
    //Step 3. Defining a new color using RGB values 
    Color lightbeige = {255, 249, 245, 255};
    int offset = 50;

    //Step 1: The Game Window Starts
    int windowWidth = 750;
    int windowHeight = 700;

    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "Garden Maniac");
    InitAudioDevice();

//Step 13. UI Elements. Paste the font code below.
    Font font = LoadFontEx("font/Valorax-lg25V.otf", 38, 0, 0);

    Texture2D shroomImage = LoadTexture("assets/shroom.png");

    SetTargetFPS(60);

    Game game;

    //Step 2: The Game Loop Starts
    while(WindowShouldClose() == false) {
        UpdateMusicStream(game.bgmusic);
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(lightbeige);
        DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, 2, DARKBROWN);
        DrawLineEx({25, 730}, {775, 730}, 3, DARKBROWN);

        if(game.run){
            DrawTextEx(font, "ROOKIE", {570, 740}, 34, 2, DARKBROWN);
        } else {
            DrawTextEx(font, "GAME OVER", {520, 740}, 34, 2, DARKBROWN);
        }
        float x = 50.0;
        for(int i = 0; i < game.lives; i ++) {
            DrawTextureV(shroomImage, {x, 745}, WHITE);
            x += 50;
        }

        //Step 13.a This is where fonts are drawn.
        DrawTextEx(font, "POINTS", {50, 15}, 34, 2, DARKBROWN);
        std::string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, DARKBROWN);

        DrawTextEx(font, "HIGHEST", {570, 15}, 34, 2, DARKBROWN);
        std::string highscoreText = FormatWithLeadingZeros(game.highscore, 5);
        DrawTextEx(font, highscoreText.c_str(), {570, 40}, 34, 2, DARKBROWN);

        game.Draw();
        EndDrawing();
    }

    //Step 1.a: Game Window ends here
    CloseWindow();
    CloseAudioDevice();
}
