#pragma once

#include "raylib.h"

enum class UIAutoSize
{
    None,
    FitContent
};

class UITransform
{
public:
    Vector2 anchorMin = { 0.0f, 0.0f };
    Vector2 anchorMax = { 0.0f, 0.0f };
    Vector2 pivot = { 0.5f, 0.5f };
    Vector2 anchoredPosition = { 0.0f, 0.0f };
    Vector2 size = { 0.0f, 0.0f };
    UIAutoSize autoWidth = UIAutoSize::None;
    UIAutoSize autoHeight = UIAutoSize::None;

    Rectangle Resolve(const Rectangle& parentRect, Vector2 contentSize = { 0.0f, 0.0f }) const;
};
