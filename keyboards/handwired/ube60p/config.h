// Copyright 2024 Jullian (@hul20)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* ==========================================================================
 * MATRIX CONFIGURATION
 * 5 rows x 14 columns = 70 positions (61 keys used)
 * Rows: Pro Micro GPIO pins 5-9
 * Columns: MCP23017 I/O Expander (read via I2C)
 * ========================================================================== */

/* Row pins on Pro Micro physical pins 5-9:
 * Pin 5 = C6, Pin 6 = D7, Pin 7 = E6, Pin 8 = B4, Pin 9 = B5
 */
#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5 }

/* ==========================================================================
 * MCP23017 I/O EXPANDER CONFIGURATION
 * ========================================================================== */
#define MCP23017_ADDR 0x20

/* MCP23017 Pin Mapping for Columns:
 * COL0  = GPA0 (pin 21)    COL7  = GPA7 (pin 28)
 * COL1  = GPA1 (pin 22)    COL8  = GPB0 (pin 1)
 * COL2  = GPA2 (pin 23)    COL9  = GPB1 (pin 2)
 * COL3  = GPA3 (pin 24)    COL10 = GPB2 (pin 3)
 * COL4  = GPA4 (pin 25)    COL11 = GPB3 (pin 4)
 * COL5  = GPA5 (pin 26)    COL12 = GPB4 (pin 5)
 * COL6  = GPA6 (pin 27)    COL13 = GPB5 (pin 6)
 */

/* ==========================================================================
 * I2C CONFIGURATION
 * Pro Micro I2C pins: SDA = D1 (pin 2), SCL = D0 (pin 3)
 * ========================================================================== */
#define I2C1_SDA_PIN D1
#define I2C1_SCL_PIN D0

/* ==========================================================================
 * DEBOUNCE CONFIGURATION
 * ========================================================================== */
#define DEBOUNCE 5

/* ==========================================================================
 * BOOTMAGIC LITE - Hold ESC on plug-in to enter bootloader
 * ========================================================================== */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
