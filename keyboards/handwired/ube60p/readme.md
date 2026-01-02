# UBE60P - Handwired 60% Keyboard

A handwired 60% keyboard using Arduino Pro Micro with MCP23017 I/O expander, OLED display, and dual rotary encoders.

## Hardware Components

| Component | Description |
|-----------|-------------|
| Controller | Arduino Pro Micro (ATmega32U4) |
| I/O Expander | CJMCU-2317 (MCP23017) |
| Switches | 61x Akko Radiant Red (or any MX-compatible) |
| Display | 0.91" SSD1306 OLED (128x32, I2C) |
| Encoders | 2x Rotary Encoders with push button |
| Diodes | 61x 1N4148 (installed on columns) |

## Matrix Configuration

- **Rows:** 5 (driven by Pro Micro)
- **Columns:** 14 (read by MCP23017)
- **Diode Direction:** COL2ROW (cathode toward column wire)

---

## Pin Mapping

### Pro Micro Pin Assignments

| Function | Pro Micro Pin | ATmega Pin | Board Label |
|----------|---------------|------------|-------------|
| ROW0 | D2 | PD2 | TX (pin 1) |
| ROW1 | D3 | PD3 | RX (pin 0) |
| ROW2 | D4 | PD4 | 4 |
| ROW3 | E6 | PE6 | 7 |
| ROW4 | D7 | PD7 | 6 |
| I2C SDA | D1 | PD1 | 2 (SDA) |
| I2C SCL | D0 | PD0 | 3 (SCL) |
| Encoder 1 A | B4 | PB4 | 8 |
| Encoder 1 B | B5 | PB5 | 9 |
| Encoder 2 A | B6 | PB6 | 10 |
| Encoder 2 B | C6 | PC6 | 5 |

**⚠️ NOTE:** D5 (PD5) is NOT available on Pro Micro - it's used internally for TX LED!

### MCP23017 Column Assignments

| Column | MCP23017 Pin | Register |
|--------|--------------|----------|
| COL0 | GPA0 (pin 21) | GPIOA bit 0 |
| COL1 | GPA1 (pin 22) | GPIOA bit 1 |
| COL2 | GPA2 (pin 23) | GPIOA bit 2 |
| COL3 | GPA3 (pin 24) | GPIOA bit 3 |
| COL4 | GPA4 (pin 25) | GPIOA bit 4 |
| COL5 | GPA5 (pin 26) | GPIOA bit 5 |
| COL6 | GPA6 (pin 27) | GPIOA bit 6 |
| COL7 | GPA7 (pin 28) | GPIOA bit 7 |
| COL8 | GPB0 (pin 1) | GPIOB bit 0 |
| COL9 | GPB1 (pin 2) | GPIOB bit 1 |
| COL10 | GPB2 (pin 3) | GPIOB bit 2 |
| COL11 | GPB3 (pin 4) | GPIOB bit 3 |
| COL12 | GPB4 (pin 5) | GPIOB bit 4 |
| COL13 | GPB5 (pin 6) | GPIOB bit 5 |

### I2C Bus Addresses

| Device | Address |
|--------|---------|
| MCP23017 | 0x20 (A0=A1=A2=GND) |
| OLED SSD1306 | 0x3C |

---

## Wiring Diagram

### I2C Bus Wiring

```
Pro Micro                MCP23017 (CJMCU-2317)
─────────                ──────────────────────
   VCC ──────────────────► VCC
   GND ──────────────────► GND
   D1 (SDA) ─────────────► SDA
   D0 (SCL) ─────────────► SCL
                          A0 ──► GND
                          A1 ──► GND
                          A2 ──► GND

Pro Micro                OLED (SSD1306)
─────────                ─────────────
   VCC ──────────────────► VCC
   GND ──────────────────► GND
   D1 (SDA) ─────────────► SDA  (shared with MCP23017)
   D0 (SCL) ─────────────► SCL  (shared with MCP23017)
```

### Matrix Wiring (Per Key)

```
Current Flow: ROW → SWITCH → DIODE → COLUMN

    ROW (Pro Micro) ────┬──── SWITCH ──── DIODE ────┬──── COLUMN (MCP23017)
                        │                   │        │
                        │     ┌─────┐      ┌┴┐       │
                        └─────┤     ├──────┤ ├───────┘
                              └─────┘      └┬┘
                               Switch    Diode (cathode → column)
```

**Important:** Diode cathode (band side) connects to COLUMN wire.

### Encoder Wiring

```
Encoder 1:               Encoder 2:
┌─────────────┐          ┌─────────────┐
│  A ──► B4   │          │  A ──► B6   │
│  B ──► B5   │          │  B ──► C6   │
│  C ──► GND  │          │  C ──► GND  │
│ SW ──► (optional) │    │ SW ──► (optional) │
└─────────────┘          └─────────────┘
```

---

## Physical Key Matrix Layout

```
Matrix positions [Row, Column]:

Row 0: [0,0] [0,1] [0,2] [0,3] [0,4] [0,5] [0,6] [0,7] [0,8] [0,9] [0,10] [0,11] [0,12] [0,13]
       ESC    1     2     3     4     5     6     7     8     9     0      -      =     BSPC

Row 1: [1,0] [1,1] [1,2] [1,3] [1,4] [1,5] [1,6] [1,7] [1,8] [1,9] [1,10] [1,11] [1,12] [1,13]
       TAB    Q     W     E     R     T     Y     U     I     O     P      [      ]      \

Row 2: [2,0] [2,1] [2,2] [2,3] [2,4] [2,5] [2,6] [2,7] [2,8] [2,9] [2,10] [2,11] [2,12]
       CAPS   A     S     D     F     G     H     J     K     L     ;      '     ENTER

Row 3: [3,0] [3,1] [3,2] [3,3] [3,4] [3,5] [3,6] [3,7] [3,8] [3,9] [3,10] [3,11]
       LSFT   Z     X     C     V     B     N     M     ,     .     /     RSFT

Row 4: [4,0] [4,1] [4,2] [4,3] [4,4] [4,5] [4,6] [4,7]
       LCTL  LGUI  LALT  SPACE RALT   FN   MENU  RCTL
```

---

## Build Instructions

### Prerequisites

1. Install QMK MSYS or QMK CLI
2. Clone the QMK firmware repository
3. Place this keyboard folder in `keyboards/handwired/ube60p/`

### Compile Firmware

```bash
# Navigate to QMK firmware root
cd qmk_firmware

# Compile the firmware
qmk compile -kb handwired/ube60p -km default

# Or use make
make handwired/ube60p:default
```

### Flash Firmware

```bash
# Flash using QMK
qmk flash -kb handwired/ube60p -km default

# Or use make
make handwired/ube60p:default:flash
```

**Bootloader Entry:**
- Short the RST and GND pins on Pro Micro twice quickly, OR
- Hold ESC while plugging in (Bootmagic Lite)

---

## Layer Guide

### Base Layer (QWERTY)
Standard QWERTY layout with all alphanumeric keys.

### FN Layer (Hold FN key)
- Top row: Grave, F1-F12, Delete
- WASD area: Arrow keys
- Z/X/C: Mute, Volume Down, Volume Up
- Right side: Home, End, Page Up, Page Down
- Insert, Print Screen, Scroll Lock, Pause

### Adjust Layer (FN + Menu)
- ESC position: Bootloader mode (QK_BOOT)
- N position: Toggle NKRO (NK_TOGG)

### Encoder Functions
| Layer | Encoder 1 | Encoder 2 |
|-------|-----------|-----------|
| Base | Volume Up/Down | Page Up/Down |
| FN | Scroll Up/Down | Brightness Up/Down |

---

## Troubleshooting

### Keyboard Not Detected

1. **Check USB connection** - Try different cable/port
2. **Enter bootloader** - Short RST-GND twice, LED should fade
3. **Check Pro Micro** - Ensure it's genuine ATmega32U4

### Keys Not Working (Entire Column)

**Symptom:** All keys in one column don't work

**Causes:**
1. **MCP23017 pin disconnected** - Check solder joint on column wire to MCP23017
2. **I2C failure** - Check SDA/SCL connections and pull-up resistors
3. **Wrong MCP23017 address** - Verify A0/A1/A2 pins are grounded

**Fix:** Use multimeter to check continuity from column wire to MCP23017 pin.

### Keys Not Working (Entire Row)

**Symptom:** All keys in one row don't work

**Causes:**
1. **Row pin disconnected** - Check solder joint on Pro Micro
2. **Wrong row pin assignment** - Verify config.h matches your wiring

### Single Key Not Working

**Causes:**
1. **Bad switch** - Test switch with multimeter
2. **Bad diode** - Check diode orientation (cathode → column)
3. **Cold solder joint** - Reflow the connection

### Multiple Keys Trigger (Ghosting)

**Symptom:** Pressing one key triggers multiple keys

**Causes:**
1. **Missing diode** - Every key needs a diode
2. **Diode reversed** - Cathode (band) must face column
3. **Short circuit** - Check for bridged wires

### Stuck/Repeating Keys

**Causes:**
1. **Debounce too low** - Increase `DEBOUNCE` in config.h (try 10-15)
2. **Bad switch contact** - Replace switch
3. **Noise on I2C bus** - Add 4.7kΩ pull-ups on SDA/SCL

### OLED Not Working

1. **Check address** - Default is 0x3C, some are 0x3D
2. **Check wiring** - VCC/GND/SDA/SCL
3. **I2C bus conflict** - Ensure MCP23017 is at 0x20

**Debug I2C:** Use I2C scanner sketch on Arduino to detect devices.

### Encoders Not Working

1. **Check pin assignment** - Verify pins match config
2. **Check common pin** - Encoder common should go to GND
3. **Debounce** - Some encoders need lower `ENCODER_RESOLUTION`

### I2C Not Responding

**Symptoms:** Nothing works, OLED blank, all columns dead

**Checklist:**
- [ ] VCC connected to 5V (not 3.3V for Pro Micro)
- [ ] GND connected
- [ ] SDA to D1 (Pro Micro pin 2)
- [ ] SCL to D0 (Pro Micro pin 3)
- [ ] Pull-up resistors (4.7kΩ) on SDA and SCL to VCC

**I2C Scanner Test:**
```cpp
// Upload this to Pro Micro to scan I2C bus
#include <Wire.h>
void setup() {
  Wire.begin();
  Serial.begin(9600);
}
void loop() {
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found: 0x");
      Serial.println(addr, HEX);
    }
  }
  delay(5000);
}
```

---

## Testing Checklist

Before final assembly:

- [ ] Pro Micro detected as USB device
- [ ] Firmware compiles without errors
- [ ] Firmware flashes successfully
- [ ] I2C scanner detects MCP23017 at 0x20
- [ ] I2C scanner detects OLED at 0x3C
- [ ] OLED displays content
- [ ] Each row triggers when shorted to column
- [ ] Encoder 1 sends volume commands
- [ ] Encoder 2 sends page up/down
- [ ] All 61 keys register correctly
- [ ] No ghosting when pressing multiple keys
- [ ] FN layer accessible

---

## Firmware Size

Expected size: ~20-24KB (Pro Micro has 28KB available)

If firmware is too large, disable in `rules.mk`:
```make
WPM_ENABLE = no
MOUSEKEY_ENABLE = no
```

---

## Credits

- QMK Firmware: https://qmk.fm
- Designed by Jullian (@hul20)

## License

GPL-2.0-or-later
