# UBE60P Handwired Keyboard Build Rules
# Pro Micro + MCP23017 (Keys only - no OLED/encoders)

# Custom matrix required for MCP23017 column scanning
CUSTOM_MATRIX = lite
SRC += matrix.c

# I2C driver for MCP23017 communication
I2C_DRIVER_REQUIRED = yes

# Disable OLED and Encoders for now
OLED_ENABLE = no
ENCODER_ENABLE = no
WPM_ENABLE = no

# Console for debugging
CONSOLE_ENABLE = yes
COMMAND_ENABLE = no
