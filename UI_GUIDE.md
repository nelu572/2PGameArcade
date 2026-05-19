# UI 가이드

이 프로젝트는 `raylib` 위에 얇은 커스텀 UI 레이어를 올려서 사용합니다.

## 구성

- `UITransform`
  - UI 배치 계산 담당
  - `anchorMin`, `anchorMax`, `pivot`, `anchoredPosition`, `size` 지원
  - `UIAutoSize::FitContent`로 내용 기반 자동 크기 지원
- `UIWidget`
  - 모든 UI 요소의 베이스 클래스
  - `transform`, `visible` 보유
  - `Update()`, `Draw()` 인터페이스 제공
- `UIText`
  - 텍스트 전용 UI 위젯
  - 내부적으로 `DrawText()` 사용
- `UIManager`
  - UI 객체들을 등록해서 한 번에 `Update()` / `Draw()` 호출

## 현재 파일

- [src/ui/UITransform.h](C:/Project/2PGameArcade/src/ui/UITransform.h:1)
- [src/ui/UITransform.cpp](C:/Project/2PGameArcade/src/ui/UITransform.cpp:1)
- [src/ui/UIWidget.h](C:/Project/2PGameArcade/src/ui/UIWidget.h:1)
- [src/ui/UIText.h](C:/Project/2PGameArcade/src/ui/UIText.h:1)
- [src/ui/UIText.cpp](C:/Project/2PGameArcade/src/ui/UIText.cpp:1)
- [src/ui/UIManager.h](C:/Project/2PGameArcade/src/ui/UIManager.h:1)
- [src/ui/UIManager.cpp](C:/Project/2PGameArcade/src/ui/UIManager.cpp:1)

## 기본 사용 흐름

1. `Game` 또는 씬 클래스의 멤버로 UI 객체를 만든다.
2. 텍스트, 색상, 폰트 크기, `transform`을 설정한다.
3. `UIManager`에 등록한다.
4. 업데이트 단계에서 `ui.Update()`를 호출한다.
5. 그리기 단계에서 `ui.Draw(screenRect)`를 호출한다.

## 사용 예시

```cpp
#include "../ui/UIManager.h"
#include "../ui/UIText.h"

class Game
{
private:
    UIManager ui;
    UIText titleLabel;
};
```

```cpp
void Game::ConfigureUI()
{
    ui.Clear();

    titleLabel.text = "2PG ARCADE";
    titleLabel.fontSize = 50;
    titleLabel.color = WHITE;

    titleLabel.transform.anchorMin = { 0.5f, 0.5f };
    titleLabel.transform.anchorMax = { 0.5f, 0.5f };
    titleLabel.transform.pivot = { 0.5f, 0.5f };
    titleLabel.transform.autoWidth = UIAutoSize::FitContent;
    titleLabel.transform.autoHeight = UIAutoSize::FitContent;

    ui.Add(titleLabel);
}
```

```cpp
void Game::Update()
{
    ui.Update();
}

void Game::Draw()
{
    Rectangle screenRect = {
        0.0f,
        0.0f,
        static_cast<float>(GetScreenWidth()),
        static_cast<float>(GetScreenHeight())
    };

    ClearBackground(BLACK);
    ui.Draw(screenRect);
}
```

## 배치 개념

### Anchor

`anchorMin`, `anchorMax`는 부모 영역 안에서의 정규화된 위치입니다.

- `{ 0.0f, 0.0f }` = 좌상단
- `{ 0.5f, 0.5f }` = 중앙
- `{ 1.0f, 1.0f }` = 우하단

`anchorMin`과 `anchorMax`가 같으면 한 점 기준 배치가 됩니다.

둘이 다르면 부모 영역을 기준으로 늘어나는 배치가 됩니다.

### Pivot

`pivot`은 위젯 내부에서 기준이 되는 점입니다.

- `{ 0.0f, 0.0f }` = 좌상단
- `{ 0.5f, 0.5f }` = 중앙
- `{ 1.0f, 1.0f }` = 우하단

### Anchored Position

`anchoredPosition`은 anchor 기준점에서 얼마나 이동할지를 뜻합니다.

예시:

```cpp
label.transform.anchorMin = { 0.5f, 0.5f };
label.transform.anchorMax = { 0.5f, 0.5f };
label.transform.pivot = { 0.5f, 0.5f };
label.transform.anchoredPosition = { 0.0f, -40.0f };
```

이렇게 하면 화면 중앙보다 약간 위에 배치됩니다.

## 자동 크기 맞춤

내용에 맞춰 크기를 자동으로 잡고 싶으면 `FitContent`를 사용합니다.

```cpp
label.transform.autoWidth = UIAutoSize::FitContent;
label.transform.autoHeight = UIAutoSize::FitContent;
```

`UIText`에서는 다음 기준으로 내용 크기를 계산합니다.

- 너비: `MeasureText(text, fontSize)`
- 높이: `fontSize`

## 고정 크기 사용

다음 같은 경우에는 `transform.size`를 직접 지정하는 편이 좋습니다.

- 패널 크기를 고정하고 싶을 때
- 버튼 크기를 일정하게 유지하고 싶을 때
- 배경 박스를 일정 크기로 그리고 싶을 때

예시:

```cpp
widget.transform.size = { 300.0f, 80.0f };
widget.transform.autoWidth = UIAutoSize::None;
widget.transform.autoHeight = UIAutoSize::None;
```

## 새 UI 클래스 추가 방법

추천 패턴:

1. `UIWidget`을 상속받는다.
2. 배치 정보는 `transform`에 둔다.
3. 그리기 로직은 위젯 클래스 안에 둔다.
4. 만든 위젯을 `UIManager`에 등록한다.

추가하기 좋은 후보:

- `UIButton`
- `UIPanel`
- `UIImage`

## 다음 확장 추천

UI가 더 커질 경우 다음 순서로 확장하는 걸 추천합니다.

- `UIPanel`
- `UIButton`
- padding / alignment 헬퍼
- 필요하면 부모-자식 UI 계층
