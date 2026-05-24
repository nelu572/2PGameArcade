# 프로젝트 구조

## 엔진 / 실행 환경

- 게임명: SIZE UP
- 장르 / 유형: 2인 로컬 협동 플랫포머
- 언어: C++
- 엔진 / 프레임워크: raylib
- 주요 플랫폼: PC / Windows
- 그래픽스 설정: `GRAPHICS_API_OPENGL_11`
- 커스텀 raylib 빌드: 사용

자세한 raylib 빌드 프로필은 [RAYLIB_PROFILE.md](C:/Project/2PGameArcade/RAYLIB_PROFILE.md:1)를 확인한다.

## 현재 폴더 구조

- `.vscode`: VS Code 빌드 / 실행 설정
- `assets`: 게임 에셋
- `Harness`: AI 개발 하네스 문서
- `src`: 게임 소스 코드
- `_deps`: raylib 등 외부 의존성

## 주요 진입점

- 앱 시작 파일: [src/main.cpp](C:/Project/2PGameArcade/src/main.cpp:1)
- 게임 루프 클래스: [src/core/Game.h](C:/Project/2PGameArcade/src/core/Game.h:1), [src/core/Game.cpp](C:/Project/2PGameArcade/src/core/Game.cpp:1)
- 현재 주요 씬: [src/scenes/MainScene.h](C:/Project/2PGameArcade/src/scenes/MainScene.h:1)

## 코드 영역

- `src/core`: 게임 루프, 씬 인터페이스, 게임 오브젝트 기반 타입
- `src/scenes`: 씬 구성
- `src/entities`: 플레이어 등 게임 엔티티
- `src/ui`: 커스텀 UI 레이어

## 씬 / 화면 역할

- `MainScene`: 현재 확인된 메인 씬. 플레이어 2명, 타이틀 텍스트, 바닥 라인을 구성한다.
- 향후 스테이지 화면: 장애물, 이동 기믹, 협동 구간, 크기 활용 구간, 출구 조건을 포함한다.
- 추가 씬: 확인 필요

## 책임 경계

- `Game`: 창 생성, 렌더 타깃, 메인 루프, 씬 수명 관리
- `Scene`: 씬 생명주기 인터페이스
- `MainScene`: 현재 씬의 오브젝트 구성과 업데이트 / 그리기
- `Player`: 플레이어 입력, 위치, 렌더링
- `ui`: 텍스트와 UI 배치 계산
- 향후 스테이지 시스템: 짧은 스테이지 진행, 양쪽 플레이어의 출구 도달 조건, 빠른 재시작 구조
- 향후 크기 시스템: 소형 / 기본 / 대형 단계, 크기에 따른 이동 공간과 충돌 범위 변화

## 빌드 / 실행 방법

- VS Code 기본 빌드 태스크: `build game`
- raylib 빌드 태스크: `build slim raylib`
- 실행 파일: `game.exe`

명령은 [.vscode/tasks.json](C:/Project/2PGameArcade/.vscode/tasks.json:1)을 기준으로 한다.
