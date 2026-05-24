#include "Game.h"
#include "raylib.h"

void Game::Run()
{
    InitWindow(WindowWidth, WindowHeight, "SIZE UP");

    const Rectangle virtualScreenRect = {
        0.0f,
        0.0f,
        static_cast<float>(VirtualWidth),
        static_cast<float>(VirtualHeight)
    };

    mainScene.Initialize(virtualScreenRect);

    Camera2D pixelPerfectCamera = {};
    pixelPerfectCamera.target = { 0.0f, 0.0f };
    pixelPerfectCamera.offset = { 0.0f, 0.0f };
    pixelPerfectCamera.rotation = 0.0f;
    pixelPerfectCamera.zoom = static_cast<float>(WindowWidth) / static_cast<float>(VirtualWidth);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        mainScene.Update();

        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(pixelPerfectCamera);

        mainScene.Draw(virtualScreenRect);

        EndMode2D();
        EndDrawing();
    }

    mainScene.Shutdown();
    CloseWindow();
}
