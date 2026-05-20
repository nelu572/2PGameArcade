#pragma once

#include "../core/GameObject.h"
#include "UITransform.h"

class UIWidget : public GameObject
{
public:
    virtual ~UIWidget() = default;

    UITransform transform;

    virtual void Draw(const Rectangle& parentRect) const = 0;
};
