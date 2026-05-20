#pragma once

#include "raylib.h"

class GameObject
{
public:
    virtual ~GameObject() = default;

    bool active = true;
    bool visible = true;

    // 월드 오브젝트와 UI 오브젝트가 매 프레임 동작을 갱신하는 지점.
    virtual void Update() {}
    // 현재 화면 영역을 넘겨서 UI와 월드 오브젝트가 같은 인터페이스를 쓰도록 한다.
    virtual void Draw(const Rectangle& viewport) const = 0;
};
