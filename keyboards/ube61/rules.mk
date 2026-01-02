# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output

# Custom matrix with I2C
CUSTOM_MATRIX = lite
SRC += matrix.c

# I2C driver for MCP23017
I2C_DRIVER_REQUIRED = yes

# OLED driver
OLED_ENABLE = yes
OLED_DRIVER = ssd1306

# WPM counter for OLED
WPM_ENABLE = yes

# Rotary encoder support
ENCODER_ENABLE = yes

