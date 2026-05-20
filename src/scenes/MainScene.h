#pragma once

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
        playerTexture = LoadTexture("assets/player.png");
        SetTextureFilter(playerTexture, TEXTURE_FILTER_POINT);

        ConfigureUI();
        ConfigurePlayers();

        // 업데이트와 그리기 순서를 명시해서 씬 구성이 예측 가능하게 유지되도록 한다.
        gameObjects.clear();
        RegisterObject(playerOne);
        RegisterObject(playerTwo);
        RegisterObject(titleLabel);
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
        DrawText("Move each player left and right", 8, 8, 8, Fade(RAYWHITE, 0.7f));
        DrawRectangle(
            static_cast<int>(viewport.x),
            static_cast<int>(viewport.y + viewport.height - 8.0f),
            static_cast<int>(viewport.width),
            8,
            Fade(DARKGRAY, 0.8f)
        );

        for (const GameObject* gameObject : gameObjects)
        {
            if (gameObject == nullptr || !gameObject->visible) continue;
            gameObject->Draw(viewport);
        }
    }

    void Shutdown() override
    {
        if (playerTexture.id != 0)
        {
            UnloadTexture(playerTexture);
            playerTexture = {};
        }

        gameObjects.clear();
    }

private:
    Rectangle sceneViewport = { 0.0f, 0.0f, 256.0f, 144.0f };
    UIText titleLabel;
    Texture2D playerTexture = {};
    Player playerOne;
    Player playerTwo;
    std::vector<GameObject*> gameObjects;

    void ConfigureUI()
    {
        titleLabel.text = "2PG ARCADE";
        titleLabel.fontSize = 16;
        titleLabel.color = WHITE;
        titleLabel.transform.anchorMin = { 0.5f, 0.07f };
        titleLabel.transform.anchorMax = { 0.5f, 0.07f };
        titleLabel.transform.pivot = { 0.5f, 0.5f };
        titleLabel.transform.autoWidth = UIAutoSize::FitContent;
        titleLabel.transform.autoHeight = UIAutoSize::FitContent;
    }

    void ConfigurePlayers()
    {
        playerOne.SetTexture(&playerTexture);
        playerOne.SetScale(1.0f);
        playerOne.SetMovementBounds(sceneViewport);

        // 스케일이 적용된 스프라이트 크기를 기준으로 시작 위치와 바닥 높이를 맞춘다.
        const Vector2 playerSize = playerOne.GetDrawSize();
        const float floorY = sceneViewport.height - playerSize.y - 8.0f;

        playerOne.SetControls(KEY_A, KEY_D);
        playerOne.SetPosition({ 24.0f, floorY });
        playerOne.SetSpeed(48.0f);
        playerOne.SetFacingRight(true);
        playerOne.SetTint(WHITE);
        playerOne.SetLabel("P1  A / D");

        playerTwo.SetTexture(&playerTexture);
        playerTwo.SetMovementBounds(sceneViewport);
        playerTwo.SetControls(KEY_LEFT, KEY_RIGHT);
        playerTwo.SetPosition({
            sceneViewport.width - playerSize.x - 24.0f,
            floorY
        });
        playerTwo.SetSpeed(48.0f);
        playerTwo.SetScale(1.0f);
        playerTwo.SetFacingRight(false);
        playerTwo.SetTint(WHITE);
        playerTwo.SetLabel("P2  <- / ->");
    }

    void RegisterObject(GameObject& gameObject)
    {
        gameObjects.push_back(&gameObject);
    }
};
