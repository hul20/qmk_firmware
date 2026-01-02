# UBE61 Keyboard

A custom 61-key keyboard using Arduino Pro Micro and MCP23017 (CJMCU-2317) I2C GPIO expander.

![ube61](imgur.com image replace me!)

## Hardware

-   **Microcontroller**: Arduino Pro Micro (ATmega32u4)
-   **GPIO Expander**: CJMCU-2317 (MCP23017) for column scanning
-   **Layout**: 61-key ANSI layout
-   **Matrix**: 5 rows × 14 columns
-   **Diodes**: IN4148 diodes in columns (COL2ROW)

## Wiring

### Arduino Pro Micro Connections

**Row Pins (5 rows)**:

-   Row 0: D3
-   Row 1: D2
-   Row 2: D4
-   Row 3: C6
-   Row 4: E6

**I2C Pins**:

-   SDA: D1 (Pin 2)
-   SCL: D0 (Pin 3)

### MCP23017 (CJMCU-2317) Connections

**I2C Interface**:

-   VCC → 5V (Pro Micro VCC)
-   GND → GND (Pro Micro GND)
-   SDA → D1 (Pro Micro)
-   SCL → D0 (Pro Micro)

**Address Pins** (for default address 0x20):

-   A0 → GND
-   A1 → GND
-   A2 → GND

**Column Pins (14 columns)**:

-   Columns 0-7: GPA0 to GPA7 (Port A)
-   Columns 8-13: GPB0 to GPB5 (Port B)

## Matrix Layout

The keyboard uses a standard 61-key ANSI layout:

```
┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
│Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
│ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
│ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │
├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
│ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │  Shift   │
├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
│Ctrl│GUI │Alt │         Space          │ Alt│GUI │Menu│Ctrl│
└────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
```

## Building Firmware

Make example for this keyboard (after setting up your build environment):

```bash
make ube61:default
```

Flashing example for this keyboard:

```bash
make ube61:default:flash
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold down Escape (top left key) and plug in the keyboard
-   **Physical reset button**: Short the RST and GND pins on the Pro Micro twice quickly
-   **Keycode in layout**: Press Fn+Backslash to trigger `QK_BOOT` (in Layer 1)

## Troubleshooting

### Keyboard not detected

-   Check USB cable and Pro Micro connections
-   Ensure bootloader is working (try resetting Pro Micro)

### Keys not registering

-   Verify I2C connections (SDA/SCL between Pro Micro and MCP23017)
-   Check MCP23017 power (VCC and GND)
-   Verify diode orientation (cathode/black band toward columns)
-   Test I2C address (default is 0x20)

### Some columns not working

-   Check MCP23017 column connections (GPA0-GPA7, GPB0-GPB5)
-   Verify pull-up resistors on I2C lines (most modules have built-in 10kΩ resistors)

## Maintainer

-   Keyboard Maintainer: [Jullian Bilan](https://github.com/hul20)
-   Hardware Supported: Arduino Pro Micro, MCP23017 (CJMCU-2317)
