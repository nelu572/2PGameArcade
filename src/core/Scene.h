#pragma once

#include "raylib.h"

class Scene
{
public:
    virtual ~Scene() = default;

    // Scene이 생성과 정리를 맡고, Game은 앱 생명주기만 관리한다.
    virtual void Initialize(const Rectangle& viewport) = 0;
    virtual void Update() = 0;
    virtual void Draw(const Rectangle& viewport) const = 0;
    virtual void Shutdown() = 0;
};
