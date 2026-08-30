# krsplit V213

A large split ergonomic keyboard (108-key style layout, `LAYOUT_108`) with an integrated numpad on the left half, an F-row, a full navigation cluster, and a rotary encoder — built around two ATmega32U4 controllers (one per half).

* Keyboard Maintainer: [AJG](https://github.com/Kesaros44)
* Hardware Supported: krsplit V213 split keyboard (AVR / ATmega32U4)
* Hardware Availability: personal/custom build

## Hardware

- **MCU:** ATmega32U4, bootloader `atmel-dfu` (32KB flash / 1KB EEPROM)
- **Matrix:** 6 rows x 11 cols per half, `COL2ROW` diode direction
- **Split communication:** soft serial (`D0`), handedness detected via `SPLIT_USB_DETECT`
- **Encoder:** one rotary encoder, right half only (`pin_a D7`, `pin_b D6`)
- **Backlight:** single-color, PWM-driven (`BACKLIGHT_PIN B6`), 7 levels, default level 3
- **Caps Lock LED:** left half only (`D6`)
- No RGB underglow, no pointing device on this revision

### D6 pin sharing (left vs. right half)

`D6` is used for two different things depending on the half: on the **left** half it drives the Caps Lock LED, and on the **right** half it is the encoder's `pin_b`. `v213.c` handles this explicitly — `matrix_init_kb()`/`led_update_kb()` only touch the Caps Lock LED pin when `is_keyboard_left()` is true, so the right half never fights the encoder for that pin. If you ever touch this file, keep that guard — removing it silently breaks encoder rotation detection on the right half.

## Software Features

Two keymaps are maintained side by side:

- **`keymaps/default`** — plain QMK, no VIA/Vial. 4 layers:
  - `_WBASE` (Windows base)
  - `_MBASE` (Mac base — same layout, with Mac modifier keycodes and Mac-specific encoder behavior)
  - `_WMFN1` (Fn layer — media/nav/backlight controls, `QK_RBT` to reboot into the bootloader)
  - `_WMFN2` (currently blank, reserved for future use)
- **`keymaps/vial`** — VIA/Vial-enabled, only 3 dynamic layers (`_WBASE`/`_MBASE`/`_WMFN1`) — see "EEPROM/flash budget" below for why the blank 4th layer had to be dropped here.
- Encoder behavior is layer-aware: on `_MBASE` it sends volume up/down (consumer keycodes, for reliable Mac media key handling); on every other layer it sends the Windows equivalent.
- Bootmagic Lite, mouse keys, and extra keys (audio/system control) enabled; NKRO disabled by default.
- `SLEEP_LED_ENABLE` is intentionally left off — it shares a timer with `BACKLIGHT_ENABLE`, so turning both on at once causes the two to interfere with each other.

### Vial build: EEPROM/flash budget (already maxed out)

The ATmega32U4's 1KB EEPROM and 32KB flash are both nearly full on the Vial build:

- Flash: 27,824 / 28,672 bytes (97%) — `MOUSEKEY_ENABLE` had to be turned off in `keymaps/vial/rules.mk` just to fit.
- EEPROM: all 1024 bytes used — 3 dynamic-keymap layers x 12x11 matrix x 2 bytes (792B) + 3 layers of encoder mapping (12B) + QMK config-sync block (40B) + EECONFIG/VIA defaults (41B), leaving ~139B for Vial's macro editor.
- To make room, the empty 4th layer (`_WMFN2`) is excluded from the dynamic keymap (`DYNAMIC_KEYMAP_LAYER_COUNT 3` in `keymaps/vial/config.h`), and Tap Dance, Combos, Key Overrides, the Repeat Key, and Mouse Keys are all disabled in `keymaps/vial/rules.mk`.
- If you need any of those features back, something else in this list has to shrink further — there's essentially no free EEPROM left.

### Backlight and USB suspend (known QMK behavior)

This board does not currently define `NO_SUSPEND_POWER_DOWN`. By default, QMK turns the backlight off the instant the host suspends the USB connection, and restores it to full brightness — with no fade — the instant it wakes back up. If the host's USB power management periodically suspends/resumes an idle keyboard, this can show up as a visible backlight flash at that same interval. (This exact symptom was diagnosed and fixed this way on the companion P213 board — see that repo's readme for the full writeup.) If V213 ever exhibits the same flashing, adding `#define NO_SUSPEND_POWER_DOWN` to `config.h` is the fix — this is a wired keyboard, so there's no real reason to power down on suspend in the first place.

## Building

Two different QMK sources are required depending on which keymap you build — mainline QMK does not include VIA/Vial support, and vial-qmk is not kept in sync with mainline.

### Default keymap (mainline QMK)

```sh
git clone --depth 1 https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
git submodule update --init --depth 1 lib/lufa lib/printf

python3 -m venv .venv && source .venv/bin/activate
pip install -r requirements.txt
pip install qmk
qmk config user.qmk_home="$(pwd)"

mkdir -p keyboards/krsplit/v213/keymaps/default
cp /path/to/V213/config.h keyboards/krsplit/v213/
cp /path/to/V213/keyboard.json keyboards/krsplit/v213/
cp /path/to/V213/v213.c keyboards/krsplit/v213/
cp /path/to/V213/krsplit.h keyboards/krsplit/v213/
cp /path/to/V213/rules.mk keyboards/krsplit/v213/
cp /path/to/V213/keymaps/default/keymap.c keyboards/krsplit/v213/keymaps/default/

make krsplit/v213:default
```

### Vial keymap (vial-kb/vial-qmk fork)

```sh
git clone --depth 1 https://github.com/vial-kb/vial-qmk.git
cd vial-qmk
git submodule update --init --depth 1 lib/lufa lib/printf

mkdir -p keyboards/krsplit/v213/keymaps/vial
cp /path/to/V213/config.h keyboards/krsplit/v213/
cp /path/to/V213/keyboard.json keyboards/krsplit/v213/
cp /path/to/V213/v213.c keyboards/krsplit/v213/
cp /path/to/V213/krsplit.h keyboards/krsplit/v213/
cp /path/to/V213/rules.mk keyboards/krsplit/v213/
cp /path/to/V213/keymaps/vial/keymap.c   keyboards/krsplit/v213/keymaps/vial/
cp /path/to/V213/keymaps/vial/rules.mk   keyboards/krsplit/v213/keymaps/vial/
cp /path/to/V213/keymaps/vial/config.h   keyboards/krsplit/v213/keymaps/vial/
cp /path/to/V213/keymaps/vial/vial.json  keyboards/krsplit/v213/keymaps/vial/

make krsplit/v213:vial
```

Pre-built `.hex` files (`krsplit_default.hex`, `krsplit_v213_vial.hex`) are included in this repo if you just want to flash without building.

## Flashing

1. Enter the bootloader:
   - Default keymap: press the `QK_RBT` key on the `_WMFN1` layer (top-left or top-right key of that layer, on either half).
   - Vial keymap: same key, same layer.
   - Alternatively, tap the reset button on the half's PCB if one is present.
2. Flash with `avrdude` or QMK Toolbox (`atmel-dfu` bootloader, `atmega32u4`).
3. For the Vial build, open the [Vial app](https://vial.rocks) — `VIAL_INSECURE` is set, so it unlocks for editing immediately, no unlock combo needed. If you want to require one, add `VIAL_UNLOCK_COMBO_ROWS`/`VIAL_UNLOCK_COMBO_COLS` to `keymaps/vial/config.h` and remove `VIAL_INSECURE`.

## Important notes / bugs found and fixed

- **`v213.c` was never actually being compiled.** QMK's build system only auto-includes a keyboard-level `.c` file that is named exactly after its own folder — for `keyboards/krsplit/v213/`, that means `v213.c`, not `krsplit.c`. The source file used to be named `krsplit.c`, so it silently never made it into any build: the Caps Lock LED / D6 pin-conflict-avoidance logic and the `backlight_enable()`/`backlight_level(3)` EEPROM-init call were dead code in every firmware shipped before this fix. Renaming it to `v213.c` (and updating `.github/workflows/build.yml` to match) fixed this — verify after any future rename that a `v213.o` (not `krsplit.o`) actually shows up under `.build/`.
- **Deprecated GPIO function names.** Once `v213.c` started actually compiling, it failed with `implicit-function-declaration` errors on `setPinOutput()`/`writePin()` — QMK 0.24.0 renamed these to `gpio_set_pin_output()`/`gpio_write_pin()` and later removed the old compatibility aliases entirely from mainline. Fixed by using the current names.
- **`DEFAULT_FOLDER` broke the `vial-qmk` CI build.** `rules.mk` used to set `DEFAULT_FOLDER = krsplit`, which mainline QMK tolerates (with a deprecation warning) but vial-qmk's Makefile does not — it failed with `No rule to make target 'krsplit/v213:vial'`. Removed since this keyboard has no sub-revisions that need it.

## CI

`.github/workflows/build.yml` builds both keymaps on every push: `build-default` against `qmk/qmk_firmware`, `build-vial` against `vial-kb/vial-qmk`. Both upload their `.hex` as a build artifact.
