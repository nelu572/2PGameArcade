#include "UIText.h"

void UIText::Draw(const Rectangle& parentRect) const
{
    if (!visible) return;

    const Vector2 contentSize = {
        static_cast<float>(MeasureText(text, fontSize)),
        static_cast<float>(fontSize)
    };

    const Rectangle rect = transform.Resolve(parentRect, contentSize);

    DrawText(text, static_cast<int>(rect.x), static_cast<int>(rect.y), fontSize, color);
}
