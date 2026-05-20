#pragma once

#include "raylib.h"
#include "../scenes/MainScene.h"

class Game
{
public:
    void Run();

private:
    static constexpr int WindowWidth = 2560;
    static constexpr int WindowHeight = 1440;
    static constexpr int VirtualWidth = 256;
    static constexpr int VirtualHeight = 144;

    MainScene mainScene;
};
