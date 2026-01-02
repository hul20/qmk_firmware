// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Matrix configuration
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

// Row pins (direct on Pro Micro)
// Using available digital pins: D3, D2, D4, C6, E6
#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5 }

// I2C Configuration for Pro Micro
// Pro Micro I2C: SDA = D1 (pin 2), SCL = D0 (pin 3)
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN D0
#define I2C1_SDA_PIN D1

// MCP23017 I2C GPIO Expander Configuration
#define MCP23017_I2C_ADDRESS 0x20  // Default address (A2=A1=A0=GND)
#define MCP23017_I2C_TIMEOUT 100

// Diode direction - diodes in columns
#define DIODE_DIRECTION COL2ROW

// Debounce reduces chatter (increased for stability)
#define DEBOUNCE 15

// I2C speed - lowered for stability with OLED + MCP23017
#define I2C1_CLOCK_SPEED 100000  // 100kHz for better stability

// OLED Configuration
#define OLED_DISPLAY_128X32
#define OLED_DISPLAY_ADDRESS 0x3C  // Try 0x3D if 0x3C doesn't work
#define OLED_TIMEOUT 30000  // 30 seconds
#define OLED_BRIGHTNESS 128  // Reduced brightness to avoid flickering
#define OLED_UPDATE_INTERVAL 100  // Update every 100ms to reduce I2C traffic

// Debug - Enable console output (optional)
// #define CONSOLE_ENABLE

// Rotary Encoder Configuration
// Encoder pins are defined in keyboard.json
#define ENCODER_RESOLUTION 4  // Adjust to 2 if too sensitive

