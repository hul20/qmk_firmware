# UBE61 Firmware - Quick Start Summary

## ✅ Setup Complete!

Your UBE61 keyboard firmware has been successfully configured for:
- **61-key ANSI layout**
- **5 rows × 14 columns** matrix
- **Arduino Pro Micro** controller
- **MCP23017 (CJMCU-2317)** I2C GPIO expander for columns
- **COL2ROW** diode direction

## 📁 File Structure

```
ube61/
├── config.h              # Hardware configuration (I2C, pins, matrix)
├── keyboard.json         # Keyboard metadata and layout definition
├── matrix.c              # Custom matrix scanning with MCP23017
├── rules.mk              # Build configuration
├── keymaps/
│   └── default/
│       └── keymap.c      # Default 61-key ANSI keymap with Fn layer
├── readme.md             # Main documentation
├── WIRING.md             # Detailed wiring guide
└── BUILD.md              # Build and flash instructions

```

## 🔌 Hardware Connection Summary

### Pro Micro Connections
- **Rows**: D3, D2, D4, C6, E6 (5 rows)
- **I2C**: D0 (SCL), D1 (SDA)

### MCP23017 Connections
- **Power**: VCC → 5V, GND → GND
- **I2C**: SDA → D1, SCL → D0
- **Address**: A0/A1/A2 → GND (address 0x20)
- **Columns**: 
  - Port A (GPA0-GPA7) → Columns 0-7
  - Port B (GPB0-GPB5) → Columns 8-13

## 🚀 Quick Build & Flash

```bash
# Navigate to keyboard directory
cd qmk_firmware/keyboards/ube61

# Compile and flash
make ube61:default:flash

# When prompted, reset Pro Micro (short RST to GND twice)
```

## 🎹 Default Keymap

**Layer 0 (Base):**
- Standard QWERTY layout
- Escape, numbers, letters, punctuation
- Standard modifiers (Ctrl, Alt, Win/GUI, Shift)

**Layer 1 (Function):**
- Access by holding Caps Lock (if configured as Fn)
- F1-F12 keys
- Arrow keys (WASD on base layer)
- Reset key (Fn + Backslash)

## 📋 Configuration Details

### I2C Settings
- **Speed**: 400 kHz (fast mode)
- **Address**: 0x20 (default)
- **Timeout**: 100ms

### Matrix Settings
- **Debounce**: 5ms
- **Direction**: COL2ROW
- **Scanning**: Custom I2C-based

### Features Enabled
- ✅ Bootmagic Lite (Hold ESC while plugging in to enter bootloader)
- ✅ NKRO (N-Key Rollover)
- ✅ Mousekey
- ✅ Extrakey (media controls)

## 🔧 Troubleshooting Quick Checks

### Keyboard Not Detected
1. Check USB cable
2. Try different USB port
3. Reset Pro Micro (double-tap RST to GND)

### No Keys Working
1. Verify I2C wiring (D0/D1 to SCL/SDA)
2. Check MCP23017 power (VCC/GND)
3. Confirm address pins (A0/A1/A2 to GND)

### Some Keys Not Working
1. Check diode orientation (cathode toward column)
2. Verify row connections to Pro Micro
3. Verify column connections to MCP23017

### Build Errors
1. Ensure all files are in correct locations
2. Update QMK: `qmk setup`
3. Clean build: `make clean`

## 📚 Documentation Reference

| File | Purpose |
|------|---------|
| **readme.md** | Main documentation, hardware info |
| **WIRING.md** | Detailed wiring diagrams and testing |
| **BUILD.md** | Complete build and flash guide |
| This file | Quick reference summary |

## 🛠️ Customization

### Change Keymap
Edit `keymaps/default/keymap.c` and reflash

### Create New Keymap
```bash
cp -r keymaps/default keymaps/yourname
# Edit keymaps/yourname/keymap.c
make ube61:yourname:flash
```

### Adjust Settings
- **I2C speed**: Edit `I2C1_CLOCK_SPEED` in `config.h`
- **Debounce**: Edit `DEBOUNCE` in `config.h`
- **Features**: Edit `rules.mk`

## 📞 Support

- QMK Documentation: https://docs.qmk.fm/
- QMK Discord: https://discord.gg/qmk
- Issues: Check WIRING.md and BUILD.md first

## ⚡ Next Steps

1. **Wire your keyboard** following WIRING.md
2. **Build firmware** using BUILD.md instructions
3. **Test all keys** after flashing
4. **Customize keymap** to your preferences

---

**Hardware Configuration:**
- Matrix: 5×14 (70 positions, 61 keys used)
- Controller: ATmega32u4 (Pro Micro)
- Expander: MCP23017 via I2C @ 400kHz
- Diodes: IN4148, COL2ROW orientation

**Firmware Version:** QMK (latest)
**Maintainer:** Jullian Bilan (hul20)
**License:** GPL-2.0-or-later

---

Good luck with your build! 🎊

