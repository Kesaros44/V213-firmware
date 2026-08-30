VIA_ENABLE = yes
VIAL_ENABLE = yes
VIAL_INSECURE = yes

# atmega32u4 1KB EEPROM 예산이 빠듯해서, 지금 keymap.c에서 실제로 쓰지 않는
# Vial 부가기능(탭댄스/콤보/키오버라이드/얼터너티브 리피트 키)은 꺼서 공간을 확보함.
# 필요해지면 언제든 yes로 켤 수 있음(단, EEPROM 여유가 줄어듦).
TAP_DANCE_ENABLE = no
COMBO_ENABLE = no
KEY_OVERRIDE_ENABLE = no
REPEAT_KEY_ENABLE = no

# 플래시 용량(atmega32u4 32KB, 부트로더 제외 28672바이트)이 VIA+Vial 프로토콜
# 코드만으로도 빠듯해서, keymap.c에서 실제로 안 쓰는 마우스키 기능을 꺼서 공간 확보.
MOUSEKEY_ENABLE = no
