# Building and Flashing Guide for UBE61

## Prerequisites

### 1. Install QMK Environment

If you haven't already set up QMK, follow these steps:

**Windows (using MSYS2):**
```bash
# Install QMK CLI
python3 -m pip install --user qmk

# Setup QMK
qmk setup
```

**macOS/Linux:**
```bash
# Install QMK CLI
python3 -m pip install --user qmk

# Setup QMK
qmk setup
```

### 2. Navigate to Your Keyboard Directory

```bash
cd qmk_firmware/keyboards/ube61
```

## Building the Firmware

### Compile Only (to test for errors)

```bash
qmk compile -kb ube61 -km default
```

Or from the QMK root directory:

```bash
make ube61:default
```

This will create a `.hex` file in the `qmk_firmware` directory if successful.

### Check for Compilation Errors

If you get errors, check:
1. All files are in the correct locations
2. Syntax in configuration files is correct
3. QMK is properly installed and up to date

## Flashing the Firmware

### Method 1: Automatic Flash (Recommended)

```bash
qmk flash -kb ube61 -km default
```

Or:

```bash
make ube61:default:flash
```

**Steps:**
1. Run the flash command
2. Wait for "Waiting for USB device..."
3. Reset your Pro Micro (short RST to GND twice quickly)
4. Firmware will automatically upload

### Method 2: Manual Flash with QMK Toolbox

1. **Build the firmware first:**
   ```bash
   make ube61:default
   ```

2. **Download QMK Toolbox:**
   - Windows/macOS: https://github.com/qmk/qmk_toolbox/releases

3. **Flash Steps:**
   - Open QMK Toolbox
   - Select your `.hex` file (in qmk_firmware directory)
   - Select "atmega32u4" as MCU
   - Click "Flash"
   - Reset your Pro Micro
   - Wait for upload to complete

## Testing After Flash

### 1. Check USB Recognition

**Windows:**
- Open Device Manager
- Look for "USB Input Device" under "Human Interface Devices"

**macOS:**
- Open System Information → USB
- Look for "ube61" or "ATm32U4DFU" (if in bootloader mode)

**Linux:**
```bash
lsusb | grep -i keyboard
```

### 2. Test Key Presses

1. Open a text editor
2. Press each key
3. Verify all 61 keys work

### 3. Test Layer Switching

Hold down **Caps Lock** (if configured as Fn) and press other keys to test Layer 1

## Troubleshooting

### Compilation Errors

**Error: "matrix.c: No such file or directory"**
- Ensure `matrix.c` is in the keyboard root directory
- Check `rules.mk` has `SRC += matrix.c`

**Error: "i2c_master.h: No such file or directory"**
- Ensure `I2C_DRIVER_REQUIRED = yes` is in `rules.mk`
- Update QMK: `qmk setup -H <path_to_qmk_firmware>`

**Error: "LAYOUT_61_ansi not defined"**
- Check `keyboard.json` has the correct layout definition
- Verify `keymap.c` uses matching layout name

### Flashing Errors

**"Device not found"**
- Check USB cable connection
- Try a different USB port
- Ensure Pro Micro is in bootloader mode (reset twice quickly)

**"Access denied" (Windows)**
- Install drivers via QMK Toolbox ("Install Drivers" button)
- Run as Administrator

**"Permission denied" (Linux)**
```bash
# Add udev rules for Pro Micro
sudo sh -c 'echo "SUBSYSTEMS==\"usb\", ATTRS{idVendor}==\"2341\", MODE:=\"0666\"" > /etc/udev/rules.d/50-arduino.rules'
sudo udevadm control --reload-rules
```

### Runtime Issues

**No keys work after flashing**
- Check I2C wiring (SDA/SCL)
- Verify MCP23017 power connections
- Test with multimeter for continuity

**Some keys don't work**
- Check diode orientation (cathode toward column)
- Verify row/column connections
- Test individual switches

**Keys type wrong characters**
- Check matrix mapping in `keyboard.json`
- Verify physical wiring matches matrix definition

**Multiple characters per key press**
- Increase debounce value in `config.h`
- Check for short circuits in wiring

## Customizing Your Layout

### Edit the Keymap

1. Open `keymaps/default/keymap.c`
2. Modify the key assignments in the layout
3. Recompile and flash

### Create a New Keymap

```bash
# Copy default keymap
cp -r keymaps/default keymaps/mymap

# Edit new keymap
# Edit keymaps/mymap/keymap.c

# Compile new keymap
make ube61:mymap:flash
```

### Useful QMK Keycodes

- `KC_TRNS` or `_______` - Transparent (use key from lower layer)
- `QK_BOOT` - Reset keyboard to bootloader
- `LT(layer, kc)` - Tap for key, hold for layer
- `MT(mod, kc)` - Tap for key, hold for modifier

See full list: https://docs.qmk.fm/#/keycodes

## Advanced Configuration

### Adjust I2C Speed

In `config.h`, modify:
```c
#define I2C1_CLOCK_SPEED 400000  // 400kHz (fast)
// or
#define I2C1_CLOCK_SPEED 100000  // 100kHz (safe, default)
```

Lower speeds are more reliable with longer wires.

### Change MCP23017 Address

If you've configured the address pins differently:

In `config.h`:
```c
// Default: A2=A1=A0=GND → 0x20
#define MCP23017_I2C_ADDRESS 0x20

// If A0=VCC → 0x21
// If A1=VCC → 0x22
// If A0=A1=VCC → 0x23
// etc.
```

### Enable Console Debugging

In `rules.mk`:
```make
CONSOLE_ENABLE = yes
```

Then use `dprintf()` in code and view output in QMK Toolbox.

## Useful Commands

```bash
# Clean build files
make clean

# Clean specific keyboard
make ube61:clean

# Compile with verbose output
make ube61:default VERBOSE=true

# List all available keyboards
qmk list-keyboards | grep ube61

# Check QMK setup
qmk doctor
```

## Resources

- **QMK Documentation**: https://docs.qmk.fm/
- **QMK Discord**: https://discord.gg/qmk
- **QMK Reddit**: https://reddit.com/r/olkb
- **Keymap Editor**: https://config.qmk.fm/

## Getting Help

If you encounter issues:

1. Check this guide's troubleshooting section
2. Review the wiring guide (`WIRING.md`)
3. Verify connections with a multimeter
4. Ask in QMK Discord #help channel
5. Create an issue on the QMK GitHub

## Firmware Updates

To update QMK and rebuild:

```bash
# Update QMK
cd ~/qmk_firmware
qmk git-submodule
git pull

# Rebuild
make ube61:default:flash
```

---

**Happy typing! 🎉**

