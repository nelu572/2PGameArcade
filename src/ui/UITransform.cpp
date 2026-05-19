#include "UITransform.h"

Rectangle UITransform::Resolve(const Rectangle& parentRect, Vector2 contentSize) const
{
    const Vector2 anchorTopLeft = {
        parentRect.x + (parentRect.width * anchorMin.x),
        parentRect.y + (parentRect.height * anchorMin.y)
    };

    const Vector2 anchorBottomRight = {
        parentRect.x + (parentRect.width * anchorMax.x),
        parentRect.y + (parentRect.height * anchorMax.y)
    };

    const Vector2 anchorRectSize = {
        anchorBottomRight.x - anchorTopLeft.x,
        anchorBottomRight.y - anchorTopLeft.y
    };

    Vector2 resolvedSize = {
        (anchorMin.x == anchorMax.x) ? size.x : anchorRectSize.x + size.x,
        (anchorMin.y == anchorMax.y) ? size.y : anchorRectSize.y + size.y
    };

    if (autoWidth == UIAutoSize::FitContent) resolvedSize.x = contentSize.x;
    if (autoHeight == UIAutoSize::FitContent) resolvedSize.y = contentSize.y;

    const Vector2 anchorReference = {
        anchorTopLeft.x + (anchorRectSize.x * pivot.x),
        anchorTopLeft.y + (anchorRectSize.y * pivot.y)
    };

    return {
        anchorReference.x + anchoredPosition.x - (resolvedSize.x * pivot.x),
        anchorReference.y + anchoredPosition.y - (resolvedSize.y * pivot.y),
        resolvedSize.x,
        resolvedSize.y
    };
}
