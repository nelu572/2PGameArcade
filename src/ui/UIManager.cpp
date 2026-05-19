#include "UIManager.h"

void UIManager::Add(UIWidget& widget)
{
    widgets.push_back(&widget);
}

void UIManager::Clear()
{
    widgets.clear();
}

void UIManager::Update()
{
    for (UIWidget* widget : widgets)
    {
        if (widget == nullptr || !widget->visible) continue;
        widget->Update();
    }
}

void UIManager::Draw(const Rectangle& rootRect) const
{
    for (const UIWidget* widget : widgets)
    {
        if (widget == nullptr || !widget->visible) continue;
        widget->Draw(rootRect);
    }
}
