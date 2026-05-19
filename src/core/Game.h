#pragma once

#include "../ui/UIManager.h"
#include "../ui/UIText.h"

class Game
{
public:
    void Run();

private:
    UIManager ui;
    UIText titleLabel;

    void ConfigureUI();
    void Update();
    void Draw();
};
