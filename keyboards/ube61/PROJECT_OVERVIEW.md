# UBE61 Firmware Project Overview

## Project Complete! ✅

Your QMK firmware for the UBE61 61-key keyboard with MCP23017 I2C GPIO expander is ready!

## 📦 What's Included

### Core Firmware Files (Required)
- **`config.h`** - Hardware configuration and pin definitions
- **`keyboard.json`** - Keyboard metadata and physical layout
- **`matrix.c`** - Custom matrix scanning with I2C communication
- **`rules.mk`** - Build system configuration
- **`keymaps/default/keymap.c`** - Default ANSI keymap with function layer

### Documentation Files
- **`readme.md`** - Main documentation and overview
- **`QUICKSTART.md`** - Quick reference summary (START HERE!)
- **`BUILD.md`** - Complete build and flash instructions
- **`WIRING.md`** - Detailed wiring diagrams and testing procedures
- **`PINOUT.md`** - Visual pinout reference and connection guide

## 🎯 Key Features

### Hardware Support
- ✅ Arduino Pro Micro (ATmega32u4)
- ✅ MCP23017 I2C GPIO Expander (CJMCU-2317)
- ✅ 5×14 matrix (61 keys)
- ✅ COL2ROW diode configuration
- ✅ 400kHz I2C communication

### Firmware Features
- ✅ Full QMK feature support
- ✅ N-Key Rollover (NKRO)
- ✅ Bootmagic Lite
- ✅ Mouse keys
- ✅ Media keys
- ✅ Two-layer keymap (base + function)
- ✅ Configurable debouncing

### Layout Support
- ✅ 61-key ANSI layout
- ✅ Standard modifiers
- ✅ Function layer with F-keys and navigation
- ✅ Reset key for easy reflashing

## 📖 Documentation Guide

### For First-Time Builders
1. **`QUICKSTART.md`** - Read this first for overview
2. **`PINOUT.md`** - Reference while planning your build
3. **`WIRING.md`** - Follow step-by-step during assembly
4. **`BUILD.md`** - Use when ready to compile and flash

### For Troubleshooting
1. Check the relevant section in **`BUILD.md`**
2. Review connections in **`WIRING.md`**
3. Verify pinouts in **`PINOUT.md`**
4. See testing procedures in **`WIRING.md`**

### For Customization
1. Read **`BUILD.md`** section on customization
2. Edit **`keymaps/default/keymap.c`** for layout changes
3. Edit **`config.h`** for hardware changes
4. See QMK docs for advanced features

## 🔧 Technical Specifications

### Matrix Configuration
```
Rows:     5 (D3, D2, D4, C6, E6)
Columns: 14 (MCP23017 GPA0-7, GPB0-5)
Diodes:  COL2ROW orientation
Keys:    61 (70 positions, 9 unused)
```

### I2C Configuration
```
Interface: I2C1
SDA Pin:   D1 (Pro Micro pin 2)
SCL Pin:   D0 (Pro Micro pin 3)
Speed:     400 kHz
Address:   0x20 (default)
Timeout:   100ms
```

### GPIO Expander
```
IC:        MCP23017
Module:    CJMCU-2317
Ports:     A (8 pins) + B (6 pins used)
Protocol:  I2C
Address:   0x20 (A0=A1=A2=GND)
```

## 🚀 Quick Start

```bash
# 1. Navigate to keyboard directory
cd qmk_firmware/keyboards/ube61

# 2. Compile to check for errors
make ube61:default

# 3. Flash to keyboard
make ube61:default:flash
# (Reset Pro Micro when prompted)

# 4. Test all keys
# Open a text editor and press each key
```

## 📋 Pre-Build Checklist

Before building:
- [ ] Arduino Pro Micro (5V/16MHz)
- [ ] CJMCU-2317 (MCP23017) module
- [ ] 61 mechanical switches
- [ ] 61 IN4148 diodes
- [ ] Wire (22-28 AWG)
- [ ] Soldering iron and solder
- [ ] Multimeter (for testing)
- [ ] USB cable (Micro-B)

Software:
- [ ] QMK firmware installed
- [ ] QMK Toolbox (optional, for flashing)
- [ ] Text editor (for keymap customization)

## 🔍 File Descriptions

### `config.h`
Defines hardware configuration including:
- Matrix size (5×14)
- Row pin assignments
- I2C pin assignments  
- MCP23017 settings
- Debounce timing
- I2C bus speed

### `keyboard.json`
QMK's declarative configuration:
- Keyboard metadata
- USB vendor/product IDs
- Bootloader type
- Feature flags
- Physical layout (61 keys with positions)

### `matrix.c`
Custom matrix scanning implementation:
- I2C initialization
- MCP23017 register configuration
- Row scanning routine
- Column reading via I2C
- Debouncing handled by QMK core

### `rules.mk`
Build system configuration:
- MCU and bootloader selection
- Feature enable/disable flags
- Custom matrix source inclusion
- I2C driver requirement

### `keymaps/default/keymap.c`
Default keymap definition:
- Layer 0: Base QWERTY layout
- Layer 1: Function keys and navigation
- Standard 61-key ANSI arrangement

## 🎨 Customization Options

### Change I2C Speed
Edit `config.h`:
```c
#define I2C1_CLOCK_SPEED 100000  // 100kHz (more reliable)
// or
#define I2C1_CLOCK_SPEED 400000  // 400kHz (faster)
```

### Change MCP23017 Address
If you configure address pins differently:
```c
// In config.h
#define MCP23017_I2C_ADDRESS 0x21  // If A0=VCC
```

### Adjust Debounce
Edit `config.h`:
```c
#define DEBOUNCE 10  // Increase if keys chatter
```

### Custom Keymap
Copy and modify:
```bash
cp -r keymaps/default keymaps/mymap
# Edit keymaps/mymap/keymap.c
make ube61:mymap:flash
```

## 📊 Project Statistics

```
Lines of Code:
- config.h:     32 lines
- matrix.c:     85 lines
- rules.mk:     24 lines
- keymap.c:     40 lines
Total:         181 lines

Documentation:
- README.md:        120 lines
- BUILD.md:         350 lines
- WIRING.md:        380 lines
- PINOUT.md:        280 lines
- QUICKSTART.md:    140 lines
Total:           1,270 lines

Files Created:  10 files
```

## 🔗 Useful Resources

- **QMK Documentation**: https://docs.qmk.fm/
- **MCP23017 Datasheet**: https://www.microchip.com/wwwproducts/en/MCP23017
- **Pro Micro Guide**: https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide
- **QMK Discord**: https://discord.gg/qmk
- **r/olkb**: https://reddit.com/r/olkb

## 📝 Build Log Template

Use this to track your build:

```
Build Date: __________

Hardware:
[ ] Pro Micro tested
[ ] CJMCU-2317 tested  
[ ] Switches installed
[ ] Diodes soldered (correct orientation!)
[ ] Rows wired
[ ] Columns wired
[ ] I2C wired
[ ] Power wired

Testing:
[ ] Continuity test (rows)
[ ] Continuity test (columns)
[ ] Voltage test (5V on expander)
[ ] I2C communication test
[ ] First firmware flash
[ ] All keys tested
[ ] Layers tested

Issues Encountered:
_________________________________
_________________________________

Solutions Applied:
_________________________________
_________________________________

Final Notes:
_________________________________
_________________________________
```

## ✨ Next Steps

1. **Read QUICKSTART.md** for overview
2. **Plan your build** using PINOUT.md
3. **Wire your keyboard** following WIRING.md
4. **Compile firmware** per BUILD.md
5. **Test thoroughly** using procedures in WIRING.md
6. **Customize** your keymap and enjoy!

## 🙏 Credits

- **QMK Firmware**: https://qmk.fm
- **MCP23017 Library**: Part of QMK i2c_master
- **Community**: QMK Discord and Reddit

## 📄 License

This firmware is licensed under GPL-2.0-or-later, consistent with QMK firmware.

---

**Version**: 1.0  
**Created**: December 2024  
**Maintainer**: Jullian Bilan (hul20)  
**Status**: ✅ Ready to build!

---

**Happy building and happy typing! 🎉⌨️**

