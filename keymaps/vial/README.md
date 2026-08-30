# krsplit/v213 keymaps/vial

이 폴더는 **일반 QMK가 아니라 vial-kb/vial-qmk 포크로만 빌드됩니다.**
(mainline QMK로는 컴파일 안 됨 — VIA/VIAL 관련 소스가 없음)

## 빌드 방법

1. https://github.com/vial-kb/vial-qmk 를 별도 폴더에 클론 (qmk_firmware 폴더 안에 중첩하지 말 것)
2. `keyboards/krsplit/v213/` 를 만들고 상위 폴더의 keyboard.json / config.h / krsplit.c / krsplit.h / rules.mk 를 그대로 복사
3. `keyboards/krsplit/v213/keymaps/vial/` 에 이 폴더의 4개 파일(keymap.c, rules.mk, config.h, vial.json)을 복사
4. `make krsplit/v213:vial` 실행

이미 컴파일된 결과물이 `krsplit_v213_vial.hex` (한 단계 위 폴더)로 들어있으니,
그냥 플래시만 하고 싶으면 빌드 없이 바로 이 hex 파일을 avrdude/QMK Toolbox로 구우면 됩니다.

## 메모리 예산 (atmega32u4: 플래시 32KB / EEPROM 1KB) — 이미 한계까지 채워진 상태

- 플래시: 27824 / 28672 바이트 (97%, 여유 848바이트) — 마우스키 기능을 꺼서 겨우 맞춤
- EEPROM: 1024 / 1024 바이트 전부 사용
  - 다이나믹 키맵 3레이어(WBase/MBase/Fn) × 12×11 매트릭스 × 2바이트 = 792B
  - 엔코더 3레이어분 = 12B
  - QMK 설정 동기화 블록 = 40B
  - EECONFIG/VIA 기본 영역 = 41B
  - Vial 매크로 편집 버퍼 = 남는 139B
- 그래서 빈 예비 레이어(원래 4번째 레이어)를 빼고, 탭댄스/콤보/키오버라이드/얼트리핏/마우스키를 껐음.
  나중에 이런 기능이 필요해지면 그만큼 다른 걸 더 줄여야 함 — 여유가 거의 없음.

## 사용 방법
1. 부트로더 진입: Fn 레이어(_WMFN1)의 좌상단/우상단 QK_RBT 키
2. avrdude 또는 QMK Toolbox로 krsplit_v213_vial.hex 플래시
3. Vial 앱(vial.rocks) 실행 — VIAL_INSECURE 모드라 언락 콤보 없이 바로 편집 가능 (보안 원하면 config.h에 VIAL_UNLOCK_COMBO_ROWS/COLS 추가하고 VIAL_INSECURE 제거)
