#include "Game.h"
#include "raylib.h"

void Game::Run()
{
    InitWindow(1280, 720, "2PG Arcade");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update


        // Draw
        BeginDrawing();

        ClearBackground(BLACK);

        const char* title = "2PG ARCADE";
        const int fontSize = 50;
        const int textX = (GetScreenWidth() - MeasureText(title, fontSize)) / 2;
        const int textY = (GetScreenHeight() - fontSize) / 2;

        DrawText(title, textX, textY, fontSize, WHITE);

        EndDrawing();
    }

    CloseWindow();
}