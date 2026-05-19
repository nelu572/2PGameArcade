#pragma once

#include <vector>

#include "UIWidget.h"

class UIManager
{
public:
    void Add(UIWidget& widget);
    void Clear();
    void Update();
    void Draw(const Rectangle& rootRect) const;

private:
    std::vector<UIWidget*> widgets;
};
