#include "Game.h"
#include "raylib.h"

void Game::ConfigureUI()
{
    ui.Clear();

    titleLabel.text = "2PG ARCADE";
    titleLabel.fontSize = 50;
    titleLabel.color = WHITE;
    titleLabel.transform.anchorMin = { 0.5f, 0.5f };
    titleLabel.transform.anchorMax = { 0.5f, 0.5f };
    titleLabel.transform.pivot = { 0.5f, 0.5f };
    titleLabel.transform.autoWidth = UIAutoSize::FitContent;
    titleLabel.transform.autoHeight = UIAutoSize::FitContent;

    ui.Add(titleLabel);
}

void Game::Update()
{
    ui.Update();
}

void Game::Draw()
{
    const Rectangle screenRect = {
        0.0f,
        0.0f,
        static_cast<float>(GetScreenWidth()),
        static_cast<float>(GetScreenHeight())
    };

    ClearBackground(BLACK);
    ui.Draw(screenRect);
}

void Game::Run()
{
    InitWindow(1280, 720, "2PG Arcade");
    ConfigureUI();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Update
        Update();


        // Draw
        BeginDrawing();

        Draw();

        EndDrawing();
    }

    CloseWindow();
}
