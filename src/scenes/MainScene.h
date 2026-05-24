#pragma once

#include <array>
#include <vector>

#include "../core/GameObject.h"
#include "../core/Scene.h"
#include "../entities/Player.h"
#include "../ui/UIText.h"
#include "raylib.h"

class MainScene : public Scene
{
public:
    void Initialize(const Rectangle& viewport) override
    {
        sceneViewport = viewport;

        ConfigurePlayers();

        // 업데이트와 그리기 순서를 명시해서 씬 구성이 예측 가능하게 유지되도록 한다.
        gameObjects.clear();
        RegisterObject(playerOne);
        RegisterObject(playerTwo);
    }

    void Update() override
    {
        for (GameObject* gameObject : gameObjects)
        {
            if (gameObject == nullptr || !gameObject->active) continue;
            gameObject->Update();
        }
    }

    void Draw(const Rectangle& viewport) const override
    {        
        DrawRectangleRec(viewport, { 13, 18, 24, 255 });
        DrawLevel();

        for (const GameObject* gameObject : gameObjects)
        {
            if (gameObject == nullptr || !gameObject->visible) continue;
            gameObject->Draw(viewport);
        }
    }

    void Shutdown() override
    {
        gameObjects.clear();
    }

private:
    Rectangle sceneViewport = { 0.0f, 0.0f, 256.0f, 144.0f };
    Player playerOne;
    Player playerTwo;
    std::vector<GameObject*> gameObjects;
    std::array<Rectangle, 8> platforms = {
        Rectangle{ 0.0f, 136.0f, 256.0f, 8.0f },
        Rectangle{ 0.0f, 0.0f, 6.0f, 144.0f },
        Rectangle{ 250.0f, 0.0f, 6.0f, 144.0f },
        Rectangle{ 44.0f, 112.0f, 34.0f, 6.0f },
        Rectangle{ 110.0f, 96.0f, 38.0f, 6.0f },
        Rectangle{ 178.0f, 78.0f, 34.0f, 6.0f },
        Rectangle{ 92.0f, 128.0f, 10.0f, 8.0f },
        Rectangle{ 154.0f, 120.0f, 14.0f, 16.0f }
    };

    void ConfigurePlayers()
    {
        PlayerTuning playerTuning;
        playerTuning.moveSpeed = 58.0f;
        playerTuning.gravity = 420.0f;
        playerTuning.jumpVelocity = 146.0f;
        playerTuning.resizeDuration = 0.0f;
        playerTuning.baseSize = { 10.0f, 14.0f };
        playerTuning.sizeScales[0] = 0.75f;
        playerTuning.sizeScales[1] = 1.0f;
        playerTuning.sizeScales[2] = 1.45f;

        playerOne.SetTuning(playerTuning);
        playerOne.SetMovementBounds(sceneViewport);
        playerOne.SetPlatforms(platforms.data(), static_cast<int>(platforms.size()));
        playerOne.SetOtherPlayer(&playerTwo);
        const Vector2 playerSize = playerOne.GetDrawSize();
        const float floorY = sceneViewport.height - playerSize.y - 8.0f;

        playerOne.SetControls(KEY_A, KEY_D, KEY_W, KEY_S);
        playerOne.SetPosition({ 24.0f, floorY });
        playerOne.SetFacingRight(true);
        playerOne.SetTint({ 91, 202, 235, 255 });
        playerOne.SetLabel("P1");

        playerTwo.SetTuning(playerTuning);
        playerTwo.SetMovementBounds(sceneViewport);
        playerTwo.SetPlatforms(platforms.data(), static_cast<int>(platforms.size()));
        playerTwo.SetOtherPlayer(&playerOne);
        playerTwo.SetControls(KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN);
        playerTwo.SetPosition({
            sceneViewport.width - playerSize.x - 24.0f,
            floorY
        });
        playerTwo.SetFacingRight(false);
        playerTwo.SetTint({ 244, 170, 87, 255 });
        playerTwo.SetLabel("P2");
    }

    void RegisterObject(GameObject& gameObject)
    {
        gameObjects.push_back(&gameObject);
    }

    void DrawLevel() const
    {
        for (const Rectangle& platform : platforms)
        {
            DrawRectangleRec(platform, { 62, 70, 82, 255 });
            DrawRectangle(
                static_cast<int>(platform.x),
                static_cast<int>(platform.y),
                static_cast<int>(platform.width),
                2,
                { 104, 116, 130, 255 }
            );
        }

        DrawRectangleRec({ 224.0f, 116.0f, 18.0f, 20.0f }, { 53, 132, 96, 255 });
        DrawRectangleLinesEx({ 224.0f, 116.0f, 18.0f, 20.0f }, 2.0f, { 121, 220, 150, 255 });
    }
};
