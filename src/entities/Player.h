#pragma once

#include "../core/GameObject.h"
#include "raylib.h"

class Player : public GameObject
{
public:
    void SetTexture(const Texture2D* value) { texture = value; }
    void SetMovementBounds(Rectangle value) { movementBounds = value; }
    void SetControls(KeyboardKey leftKey, KeyboardKey rightKey)
    {
        moveLeftKey = leftKey;
        moveRightKey = rightKey;
    }
    void SetPosition(Vector2 value) { position = value; }
    void SetLabel(const char* value) { label = value; }
    void SetSpeed(float value) { speed = value; }
    void SetScale(float value) { scale = value; }
    void SetFacingRight(bool value) { facingRight = value; }
    void SetTint(Color value) { tint = value; }

    Vector2 GetDrawSize() const
    {
        if (texture != nullptr && texture->id != 0)
        {
            return {
                texture->width * scale,
                texture->height * scale
            };
        }

        return { 64.0f, 64.0f };
    }

    void Update() override
    {
        const float deltaTime = GetFrameTime();
        const Vector2 drawSize = GetDrawSize();
        const float minX = movementBounds.x;
        const float maxX = movementBounds.x + movementBounds.width - drawSize.x;
        const int direction = static_cast<int>(IsKeyDown(moveRightKey)) - static_cast<int>(IsKeyDown(moveLeftKey));

        // 첫 플레이 버전에서는 좌우 이동만 처리한다.
        position.x += direction * speed * deltaTime;

        if (position.x < minX) position.x = minX;
        if (position.x > maxX) position.x = maxX;

        if (direction != 0) facingRight = direction > 0;
    }

    void Draw(const Rectangle& viewport) const override
    {
        (void)viewport;

        const Vector2 drawSize = GetDrawSize();
        DrawText(label, static_cast<int>(position.x), static_cast<int>(position.y - 10.0f), 8, WHITE);

        if (texture != nullptr && texture->id != 0)
        {
            Rectangle source = {
                0.0f,
                0.0f,
                static_cast<float>(texture->width),
                static_cast<float>(texture->height)
            };

            // source 너비를 음수로 주면 별도 텍스처 없이 좌우 반전할 수 있다.
            if (!facingRight)
            {
                source.width *= -1.0f;
            }

            const Rectangle destination = {
                position.x,
                position.y,
                drawSize.x,
                drawSize.y
            };

            DrawTexturePro(*texture, source, destination, { 0.0f, 0.0f }, 0.0f, tint);
            return;
        }

        DrawRectangleV(position, drawSize, SKYBLUE);
    }

private:
    const Texture2D* texture = nullptr;
    Vector2 position = { 0.0f, 0.0f };
    float speed = 320.0f;
    float scale = 8.0f;
    bool facingRight = true;
    Color tint = WHITE;
    const char* label = "";
    Rectangle movementBounds = { 0.0f, 0.0f, 256.0f, 144.0f };
    KeyboardKey moveLeftKey = KEY_NULL;
    KeyboardKey moveRightKey = KEY_NULL;
};
