#pragma once

#include "UITransform.h"

class UIWidget
{
public:
    virtual ~UIWidget() = default;

    UITransform transform;
    bool visible = true;

    virtual void Update() {}
    virtual void Draw(const Rectangle& parentRect) const = 0;
};
