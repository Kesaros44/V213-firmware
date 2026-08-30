#pragma once

#define VIAL_KEYBOARD_UID {0xA5, 0x20, 0x0E, 0x3D, 0xF0, 0x2F, 0xCD, 0x1B}

// atmega32u4 내장 EEPROM은 1KB뿐이라 12x11 매트릭스 * 4레이어 동적 키맵을 다 담을 수 없음.
// 실제로 쓰이지 않는 _WMFN2(4번째, 완전 빈 예비 레이어)를 다이나믹 키맵에서 제외해 3레이어로 줄임.
#define DYNAMIC_KEYMAP_LAYER_COUNT 3
