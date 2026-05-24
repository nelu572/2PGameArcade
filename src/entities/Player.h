#pragma once

#include "../core/GameObject.h"
#include "raylib.h"

struct PlayerTuning
{
    float moveSpeed = 58.0f;
    float gravity = 420.0f;
    float jumpVelocity = 146.0f;
    float resizeDuration = 0.0f;
    Vector2 baseSize = { 10.0f, 14.0f };
    float sizeScales[3] = { 0.5, 1.0f, 2.5f };
};

class Player : public GameObject
{
public:
    void SetMovementBounds(Rectangle value) { movementBounds = value; }
    void SetPlatforms(const Rectangle* values, int valueCount)
    {
        platforms = values;
        platformCount = valueCount;
    }
    void SetOtherPlayer(const Player* value) { otherPlayer = value; }
    void SetControls(KeyboardKey leftKey, KeyboardKey rightKey, KeyboardKey jumpKey, KeyboardKey resizeKey)
    {
        moveLeftKey = leftKey;
        moveRightKey = rightKey;
        jumpKeyValue = jumpKey;
        resizeKeyValue = resizeKey;
    }
    void SetPosition(Vector2 value) { position = value; }
    void SetLabel(const char* value) { label = value; }
    void SetTuning(PlayerTuning value)
    {
        tuning = value;
        currentScale = tuning.sizeScales[sizeIndex];
        startScale = currentScale;
        targetScale = currentScale;
        resizeElapsed = 0.0f;
    }
    void SetFacingRight(bool value) { facingRight = value; }
    void SetTint(Color value) { tint = value; }

    Vector2 GetDrawSize() const
    {
        return {
            tuning.baseSize.x * currentScale,
            tuning.baseSize.y * currentScale
        };
    }

    Rectangle GetCollisionBounds() const
    {
        return GetBounds();
    }

    void Update() override
    {
        const float deltaTime = GetFrameTime();
        const int direction = static_cast<int>(IsKeyDown(moveRightKey)) - static_cast<int>(IsKeyDown(moveLeftKey));

        if (IsKeyPressed(resizeKeyValue))
        {
            TryStartResize();
        }

        const Vector2 previousSize = GetDrawSize();
        UpdateScale(deltaTime);
        const Vector2 currentSize = GetDrawSize();
        position.x -= (currentSize.x - previousSize.x) * 0.5f;
        position.y -= currentSize.y - previousSize.y;
        if (currentSize.x > previousSize.x || currentSize.y > previousSize.y)
        {
            ResolveResizeOverlap();
        }

        velocity.x = direction * tuning.moveSpeed;
        MoveAndCollide({ velocity.x * deltaTime, 0.0f });
        grounded = IsStandingOnGround();

        if (direction != 0) facingRight = direction > 0;

        if (IsKeyPressed(jumpKeyValue) && grounded)
        {
            velocity.y = -tuning.jumpVelocity;
            grounded = false;
        }

        velocity.y += tuning.gravity * deltaTime;
        MoveAndCollide({ 0.0f, velocity.y * deltaTime });
    }

    void Draw(const Rectangle& viewport) const override
    {
        (void)viewport;

        const Vector2 drawSize = GetDrawSize();
        DrawText(label, static_cast<int>(position.x), static_cast<int>(position.y - 9.0f), 8, WHITE);
        DrawPixelCharacter(drawSize);
    }

private:
    PlayerTuning tuning;
    Vector2 position = { 0.0f, 0.0f };
    Vector2 velocity = { 0.0f, 0.0f };
    float currentScale = 1.0f;
    float startScale = 1.0f;
    float targetScale = 1.0f;
    float resizeElapsed = 0.0f;
    float maxResizeCorrection = 4.0f;
    int sizeIndex = 1;
    bool facingRight = true;
    bool grounded = false;
    Color tint = WHITE;
    const char* label = "";
    Rectangle movementBounds = { 0.0f, 0.0f, 256.0f, 144.0f };
    const Rectangle* platforms = nullptr;
    int platformCount = 0;
    const Player* otherPlayer = nullptr;
    KeyboardKey moveLeftKey = KEY_NULL;
    KeyboardKey moveRightKey = KEY_NULL;
    KeyboardKey jumpKeyValue = KEY_NULL;
    KeyboardKey resizeKeyValue = KEY_NULL;

    Rectangle GetBounds() const
    {
        const Vector2 drawSize = GetDrawSize();
        return { position.x, position.y, drawSize.x, drawSize.y };
    }

    void UpdateScale(float deltaTime)
    {
        if (currentScale == targetScale) return;
        if (tuning.resizeDuration <= 0.0f)
        {
            currentScale = targetScale;
            return;
        }

        const float duration = tuning.resizeDuration;
        resizeElapsed += deltaTime;
        float progress = resizeElapsed / duration;
        if (progress > 1.0f) progress = 1.0f;

        currentScale = startScale + (targetScale - startScale) * progress;
    }

    void TryStartResize()
    {
        const int nextSizeIndex = (sizeIndex + 1) % 3;
        const float nextScale = tuning.sizeScales[nextSizeIndex];

        if (nextScale > currentScale && (HasOpposingResizeTrap(nextScale) || !CanFitScale(nextScale)))
        {
            return;
        }

        sizeIndex = nextSizeIndex;
        startScale = currentScale;
        targetScale = nextScale;
        resizeElapsed = 0.0f;
    }

    bool CanFitScale(float nextScale) const
    {
        const float offsets[] = { 0.0f, -1.0f, 1.0f, -3.0f, 3.0f, -6.0f, 6.0f, -10.0f, 10.0f };

        for (float offset : offsets)
        {
            const Rectangle candidate = BuildResizeCandidate(nextScale, offset);
            if (!OverlapsAnySolid(candidate))
            {
                return true;
            }
        }

        return false;
    }

    Rectangle BuildResizeCandidate(float nextScale, float offsetX) const
    {
        const Vector2 oldSize = GetDrawSize();
        const Vector2 newSize = {
            tuning.baseSize.x * nextScale,
            tuning.baseSize.y * nextScale
        };
        const float centerX = position.x + oldSize.x * 0.5f;
        const float footY = position.y + oldSize.y;

        Rectangle candidate = {
            centerX - newSize.x * 0.5f + offsetX,
            footY - newSize.y,
            newSize.x,
            newSize.y
        };

        if (candidate.x < movementBounds.x)
        {
            candidate.x = movementBounds.x;
        }

        const float maxX = movementBounds.x + movementBounds.width - candidate.width;
        if (candidate.x > maxX)
        {
            candidate.x = maxX;
        }

        if (candidate.y < movementBounds.y)
        {
            candidate.y = movementBounds.y;
        }

        return candidate;
    }

    bool HasOpposingResizeTrap(float nextScale) const
    {
        const float offsets[] = { 0.0f, -1.0f, 1.0f, -3.0f, 3.0f, -6.0f, 6.0f, -10.0f, 10.0f };
        const int steps = 6;

        for (int step = 1; step <= steps; ++step)
        {
            const float progress = static_cast<float>(step) / static_cast<float>(steps);
            const float sampleScale = currentScale + (nextScale - currentScale) * progress;
            bool hasNonTrappedCandidate = false;

            for (float offset : offsets)
            {
                const Rectangle candidate = BuildResizeCandidate(sampleScale, offset);
                if (!HasOpposingSideCollision(candidate))
                {
                    hasNonTrappedCandidate = true;
                    break;
                }
            }

            if (!hasNonTrappedCandidate)
            {
                return true;
            }
        }

        return false;
    }

    bool HasOpposingSideCollision(Rectangle bounds) const
    {
        bool hitLeft = bounds.x <= movementBounds.x;
        bool hitRight = bounds.x + bounds.width >= movementBounds.x + movementBounds.width;
        bool hitTop = bounds.y <= movementBounds.y;
        bool hitBottom = bounds.y + bounds.height >= movementBounds.y + movementBounds.height;
        const Vector2 center = {
            bounds.x + bounds.width * 0.5f,
            bounds.y + bounds.height * 0.5f
        };

        for (int i = 0; i < platformCount; ++i)
        {
            const Rectangle platform = platforms[i];
            const bool overlapsX = bounds.x < platform.x + platform.width && bounds.x + bounds.width > platform.x;
            const bool overlapsY = bounds.y < platform.y + platform.height && bounds.y + bounds.height > platform.y;
            const float epsilon = 0.25f;

            if (overlapsY && bounds.x <= platform.x + platform.width && bounds.x >= platform.x + platform.width - epsilon)
            {
                hitLeft = true;
            }

            if (overlapsY && bounds.x + bounds.width >= platform.x && bounds.x + bounds.width <= platform.x + epsilon)
            {
                hitRight = true;
            }

            if (overlapsX && bounds.y <= platform.y + platform.height && bounds.y >= platform.y + platform.height - epsilon)
            {
                hitTop = true;
            }

            if (overlapsX && bounds.y + bounds.height >= platform.y && bounds.y + bounds.height <= platform.y + epsilon)
            {
                hitBottom = true;
            }

            if (!CheckCollisionRecs(bounds, platform)) continue;

            const Vector2 platformCenter = {
                platform.x + platform.width * 0.5f,
                platform.y + platform.height * 0.5f
            };

            if (platformCenter.x < center.x) hitLeft = true;
            if (platformCenter.x > center.x) hitRight = true;
            if (platformCenter.y < center.y) hitTop = true;
            if (platformCenter.y > center.y) hitBottom = true;
        }

        return (hitLeft && hitRight) || (hitTop && hitBottom);
    }

    bool OverlapsAnyPlatform(Rectangle bounds) const
    {
        for (int i = 0; i < platformCount; ++i)
        {
            if (CheckCollisionRecs(bounds, platforms[i])) return true;
        }

        return false;
    }

    bool OverlapsAnySolid(Rectangle bounds) const
    {
        if (OverlapsAnyPlatform(bounds)) return true;
        return otherPlayer != nullptr && CheckCollisionRecs(bounds, otherPlayer->GetCollisionBounds());
    }

    void ResolveResizeOverlap()
    {
        Rectangle bounds = GetBounds();
        if (!OverlapsAnySolid(bounds))
        {
            ClampToWorldX();
            ClampToWorldY();
            return;
        }

        float bestOffset = 0.0f;
        bool foundCorrection = false;
        const float step = 0.5f;

        for (float distance = step; distance <= maxResizeCorrection; distance += step)
        {
            const float directions[] = { -distance, distance };

            for (float offset : directions)
            {
                Rectangle candidate = bounds;
                candidate.x += offset;
                ClampCandidateX(candidate);

                if (!OverlapsAnySolid(candidate))
                {
                    bestOffset = candidate.x - bounds.x;
                    foundCorrection = true;
                    break;
                }
            }

            if (foundCorrection)
            {
                break;
            }
        }

        if (foundCorrection)
        {
            position.x += bestOffset;
        }
    }

    void ClampCandidateX(Rectangle& candidate) const
    {
        if (candidate.x < movementBounds.x)
        {
            candidate.x = movementBounds.x;
        }

        const float maxX = movementBounds.x + movementBounds.width - candidate.width;
        if (candidate.x > maxX)
        {
            candidate.x = maxX;
        }
    }

    void MoveAndCollide(Vector2 delta)
    {
        position.x += delta.x;
        ClampToWorldX();

        Rectangle bounds = GetBounds();
        if (delta.x != 0.0f)
        {
            for (int i = 0; i < platformCount; ++i)
            {
                ResolveHorizontalCollision(platforms[i], delta.x);
                bounds = GetBounds();
            }

            if (otherPlayer != nullptr)
            {
                ResolveHorizontalCollision(otherPlayer->GetCollisionBounds(), delta.x);
            }
        }

        position.y += delta.y;
        grounded = false;
        ClampToWorldY();

        bounds = GetBounds();
        if (delta.y == 0.0f) return;

        for (int i = 0; i < platformCount; ++i)
        {
            ResolveVerticalCollision(platforms[i], delta.y);
            bounds = GetBounds();
        }

        if (otherPlayer != nullptr)
        {
            ResolveVerticalCollision(otherPlayer->GetCollisionBounds(), delta.y);
        }
    }

    void ResolveHorizontalCollision(Rectangle solid, float deltaX)
    {
        Rectangle bounds = GetBounds();
        if (!CheckCollisionRecs(bounds, solid)) return;

        if (deltaX > 0.0f)
        {
            position.x = solid.x - bounds.width;
        }
        else if (deltaX < 0.0f)
        {
            position.x = solid.x + solid.width;
        }
    }

    void ResolveVerticalCollision(Rectangle solid, float deltaY)
    {
        Rectangle bounds = GetBounds();
        if (!CheckCollisionRecs(bounds, solid)) return;

        if (deltaY > 0.0f)
        {
            position.y = solid.y - bounds.height;
            velocity.y = 0.0f;
            grounded = true;
        }
        else if (deltaY < 0.0f)
        {
            position.y = solid.y + solid.height;
            velocity.y = 0.0f;
        }
    }

    void ClampToWorldX()
    {
        const Vector2 drawSize = GetDrawSize();
        const float minX = movementBounds.x;
        const float maxX = movementBounds.x + movementBounds.width - drawSize.x;

        if (position.x < minX) position.x = minX;
        if (position.x > maxX) position.x = maxX;
    }

    void ClampToWorldY()
    {
        const Vector2 drawSize = GetDrawSize();
        const float minY = movementBounds.y;
        const float maxY = movementBounds.y + movementBounds.height - drawSize.y;

        if (position.y < minY)
        {
            position.y = minY;
            velocity.y = 0.0f;
        }

        if (position.y > maxY)
        {
            position.y = maxY;
            velocity.y = 0.0f;
            grounded = true;
        }
    }

    bool IsStandingOnGround() const
    {
        Rectangle probe = GetBounds();
        probe.x += 1.0f;
        probe.width -= 2.0f;
        probe.y += probe.height;
        probe.height = 1.0f;

        const float worldBottom = movementBounds.y + movementBounds.height;
        if (probe.y + probe.height >= worldBottom) return true;

        for (int i = 0; i < platformCount; ++i)
        {
            if (CheckCollisionRecs(probe, platforms[i])) return true;
        }

        if (otherPlayer != nullptr && CheckCollisionRecs(probe, otherPlayer->GetCollisionBounds()))
        {
            return true;
        }

        return false;
    }

    void DrawPixelCharacter(Vector2 drawSize) const
    {
        const float unit = drawSize.y / 14.0f;
        const float left = position.x;
        const float top = position.y;
        const Color shadow = Fade(BLACK, 0.28f);
        const Color body = tint;
        const Color dark = ColorBrightness(tint, -0.35f);
        const Color light = ColorBrightness(tint, 0.25f);
        const float eyeX = facingRight ? left + unit * 6.0f : left + unit * 2.0f;

        DrawRectangleRec({ left + unit, top + unit * 3.0f, unit * 8.0f, unit * 9.0f }, body);
        DrawRectangleRec({ left + unit * 2.0f, top + unit, unit * 6.0f, unit * 3.0f }, body);
        DrawRectangleRec({ left, top + unit * 5.0f, unit, unit * 5.0f }, dark);
        DrawRectangleRec({ left + unit * 9.0f, top + unit * 5.0f, unit, unit * 5.0f }, light);
        DrawRectangleRec({ left + unit * 2.0f, top + unit * 12.0f, unit * 2.0f, unit * 2.0f }, dark);
        DrawRectangleRec({ left + unit * 6.0f, top + unit * 12.0f, unit * 2.0f, unit * 2.0f }, dark);
        DrawRectangleRec({ eyeX, top + unit * 3.0f, unit * 2.0f, unit * 2.0f }, BLACK);
        DrawRectangleRec({ left + unit * 2.0f, top + unit * 7.0f, unit * 6.0f, unit }, shadow);
    }
};
