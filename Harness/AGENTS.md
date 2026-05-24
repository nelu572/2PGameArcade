# AI 작업 운영 안내서

## 프로젝트 개요

- 프로젝트명: SIZE UP
- 저장소명: 2PGameArcade
- 장르 / 유형: 2인 로컬 협동 플랫포머
- 엔진 / 프레임워크: C++ / raylib
- 주요 플랫폼: PC / Windows
- 현재 개발 단계: 확인 필요
- 핵심 목표: 두 플레이어가 크기 조절을 활용해 짧은 스테이지의 출구까지 협력해서 도달하는 경험 검증
- 주요 실행 진입점: `src/main.cpp`
- 주요 코드 폴더: `src`
- 주요 기능 영역: `core`, `scenes`, `entities`, `ui`
- 테스트 / 검증 방식: VS Code `build game` 태스크, `game.exe` 실행 확인
- Git 운영 방식: 확인 필요
- 문서 언어: 한국어

## 먼저 읽을 문서 순서

1. 현재 대화의 직접 지시
2. [WORK_ORDER.md](C:/Project/2PGameArcade/Harness/WORK_ORDER.md:1)
3. [PROJECT_STRUCTURE.md](C:/Project/2PGameArcade/Harness/Docs/Structure/PROJECT_STRUCTURE.md:1)
4. [AI_DEVELOPMENT_RULES.md](C:/Project/2PGameArcade/Harness/Docs/Conventions/AI_DEVELOPMENT_RULES.md:1)
5. [CODING_CONVENTIONS.md](C:/Project/2PGameArcade/Harness/Docs/Conventions/CODING_CONVENTIONS.md:1)
6. [PROJECT_PLAN.md](C:/Project/2PGameArcade/Harness/Docs/Planning/PROJECT_PLAN.md:1)
7. [TODO_ROADMAP.md](C:/Project/2PGameArcade/Harness/Docs/Planning/TODO_ROADMAP.md:1)
8. [FILE_CHANGE_LOG.md](C:/Project/2PGameArcade/Harness/Docs/Logs/FILE_CHANGE_LOG.md:1)

## 문서 맵

- `WORK_ORDER.md`: 반복 작업 지시 템플릿
- `Docs/Structure/PROJECT_STRUCTURE.md`: 구조, 진입점, 실행 방식
- `Docs/Conventions/AI_DEVELOPMENT_RULES.md`: AI 작업 우선순위와 원칙
- `Docs/Conventions/CODING_CONVENTIONS.md`: 코딩 규칙
- `Docs/Conventions/GITHUB_HARNESS.md`: Git 작업 흐름
- `Docs/Planning/PROJECT_PLAN.md`: 사용자가 작성하는 기획서
- `Docs/Planning/TODO_ROADMAP.md`: 로드맵과 다음 작업
- `Docs/Planning/VISUAL_HARNESS.md`: 화면 / UX 검수 기준
- `Docs/Logs/FILE_CHANGE_LOG.md`: 파일 변경 이력

## 작업 우선순위

현재 대화의 직접 프롬프트가 항상 `WORK_ORDER.md`보다 우선한다. 충돌이 있으면 현재 대화 지시를 따른다.

사용자가 "메모 작업해"라고 말하면 `WORK_ORDER.md`를 읽고, 그 안의 작업 이름과 상세 요구사항을 실제 작업 대상으로 해석해 수행한다.

## 작업 규칙

- 수정 전 관련 파일을 먼저 읽는다.
- 확인되지 않은 프로젝트 정보는 지어내지 않고 `확인 필요`로 남긴다.
- 기존 public API, 시스템 책임 경계, 빌드 흐름을 불필요하게 흔들지 않는다.
- 작업 후 가능한 검증을 수행한다.
- 작업 완료 후 [FILE_CHANGE_LOG.md](C:/Project/2PGameArcade/Harness/Docs/Logs/FILE_CHANGE_LOG.md:1)를 갱신한다.
- 기획 변경이 있으면 [PROJECT_PLAN.md](C:/Project/2PGameArcade/Harness/Docs/Planning/PROJECT_PLAN.md:1)를 기준 문서로 본다.

## 문서 처리 규칙

- 하네스 문서는 짧고 실행 가능한 내용 중심으로 유지한다.
- `WORK_ORDER.md`는 템플릿이므로 명시 요청 없이 구조를 지우지 않는다.
- `PROJECT_PLAN.md`가 채워진 뒤에는 그 내용을 기준으로 하네스의 개요, 로드맵, 화면 / UX 기준을 갱신한다.
- 오래된 내용은 삭제보다 갱신 또는 이력화한다.
