#pragma once

#include "UIWidget.h"

class UIText : public UIWidget
{
public:
    const char* text = "";
    int fontSize = 20;
    Color color = WHITE;

    void Draw(const Rectangle& parentRect) const override;
};
