# 커스텀 raylib 빌드 프로필

이 프로젝트는 기본 raylib를 그대로 쓰지 않고, 실행 파일 크기를 줄이기 위해 기능을 선택적으로 끈 커스텀 빌드를 사용합니다.

현재 기준 설정은 [tasks.json](C:/Project/2PGameArcade/.vscode/tasks.json:1)에 들어 있는 `build slim raylib` 태스크를 따릅니다.

## 현재 빌드 방향

- 플랫폼: `PLATFORM_DESKTOP_WIN32`
- 그래픽스 API: `GRAPHICS_API_OPENGL_11`
- 오디오: 켬
- shapes: 켬
- textures: 켬
- text: 켬
- models: 끔
- 실행 파일 크기 최적화 옵션: 켬
- Win32 DPI-aware 처리: 직접 활성화됨

참고:
- DPI 관련 패치는 [rcore_desktop_win32.c](C:/Project/2PGameArcade/_deps/raylib-src/src/platforms/rcore_desktop_win32.c:1512)에 반영되어 있습니다.

## 가능한 것

### 기본 창 / 렌더링

- `InitWindow()`
- `CloseWindow()`
- `BeginDrawing()`
- `EndDrawing()`
- `ClearBackground()`
- 입력 처리
- 기본적인 2D 렌더링 루프

### 도형 그리기

`rshapes` 모듈이 켜져 있으므로 기본 도형 API를 사용할 수 있습니다.

예:
- `DrawRectangle()`
- `DrawRectangleRec()`
- `DrawRectanglePro()`
- `DrawCircle()`
- `DrawLine()`

### 텍스트

`rtext` 모듈이 켜져 있으므로 기본 텍스트 출력은 가능합니다.

예:
- `DrawText()`
- `DrawTextEx()`
- `MeasureText()`

주의:
- 외부 폰트 파일 로딩은 꺼져 있습니다.
- 기본 내장 폰트 기반 텍스트 출력만 된다고 생각하면 됩니다.

### 이미지 / 텍스처

`rtextures` 모듈이 켜져 있고, 일부 포맷만 허용되어 있습니다.

가능:
- `LoadImage()`
- `LoadTexture()`
- `LoadTextureFromImage()`
- `DrawTexture()`
- `DrawTexturePro()`

현재 로딩 가능한 이미지 포맷:
- PNG
- BMP

### 오디오

`raudio` 모듈이 켜져 있고, 일부 포맷만 허용되어 있습니다.

가능:
- `InitAudioDevice()`
- `LoadSound()`
- `PlaySound()`
- `LoadMusicStream()`

현재 로딩 가능한 오디오 포맷:
- WAV
- OGG

## 불가능한 것

### 3D 모델 / 모델 파일 로딩

`rmodels` 모듈이 꺼져 있습니다.

즉 다음 계열은 사용할 수 없습니다.
- 3D 모델 로딩
- 메시 생성
- glTF / OBJ / IQM / VOX / M3D 등 모델 포맷 처리

### 외부 폰트 파일 로딩

다음 포맷 지원이 꺼져 있습니다.
- TTF
- FNT
- BDF

즉 다음 같은 용도는 불가능합니다.
- `LoadFont("font.ttf")`
- 커스텀 비트맵 폰트 파일 로딩

### 추가 이미지 포맷

다음 포맷은 꺼져 있습니다.
- TGA
- JPG
- GIF
- QOI
- PSD
- DDS
- HDR
- PIC
- PNM
- KTX
- ASTC
- PKM
- PVR

즉 현재는 PNG/BMP 위주로 쓰는 것이 맞습니다.

### 추가 오디오 포맷

다음 포맷은 꺼져 있습니다.
- MP3
- QOA
- FLAC
- XM
- MOD

즉 현재는 WAV/OGG 위주로 쓰는 것이 맞습니다.

### 이미지 내보내기 / 런타임 이미지 생성

다음 기능이 꺼져 있습니다.
- `SUPPORT_IMAGE_EXPORT`
- `SUPPORT_IMAGE_GENERATION`

즉 런타임에 이미지 파일을 저장하거나, raylib의 절차적 이미지 생성 기능에 의존하는 건 피하는 편이 좋습니다.

### 기타 꺼진 기능

다음 부가 기능들은 꺼져 있습니다.
- trace log
- camera system
- gestures system
- pseudo-random generator helper
- mouse gestures
- high resolution WinMM timer hint
- screen capture
- compression API
- automation events
- clipboard image

## 실전 기준으로 보면

현재 프로필은 대략 이런 게임에 맞습니다.

잘 맞는 경우:
- 2D 픽셀 게임
- 스프라이트 기반 게임
- PNG 이미지 사용
- WAV / OGG 사운드 사용
- 기본 도형과 기본 텍스트를 함께 쓰는 게임

안 맞는 경우:
- 3D 게임
- 외부 TTF 폰트를 꼭 써야 하는 게임
- JPG / GIF / MP3 같은 포맷에 의존하는 게임
- 런타임 이미지 저장 / 생성 기능이 필요한 게임

## 새 기능이 필요할 때

새로운 기능이 필요하면 보통 아래 둘 중 하나를 바꿔야 합니다.

1. `.vscode/tasks.json`의 `RAYLIB_CONFIG_FLAGS`
2. 필요한 경우 `RAYLIB_MODULE_*` 플래그

예:
- MP3를 쓰고 싶다
  - `SUPPORT_FILEFORMAT_MP3=1`
- TTF 폰트를 쓰고 싶다
  - `SUPPORT_FILEFORMAT_TTF=1`
- 3D 모델이 필요하다
  - `RAYLIB_MODULE_MODELS=TRUE`
  - 관련 `SUPPORT_FILEFORMAT_*`도 함께 검토

## 권장 사용 규칙

- 이미지 에셋은 가능하면 PNG로 통일
- 오디오는 가능하면 OGG 또는 WAV로 통일
- 폰트는 당장은 기본 폰트 중심으로 사용
- 3D 계열 기능은 추가하기 전까지 건드리지 않기
- 기능을 하나 켤 때마다 실행 파일 크기를 다시 확인하기
