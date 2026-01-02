// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "i2c_master.h"

// MCP23017 Register addresses (IOCON.BANK = 0)
#define IODIRA   0x00  // I/O Direction Register A
#define IODIRB   0x01  // I/O Direction Register B
#define GPPUA    0x0C  // Pull-up Register A
#define GPPUB    0x0D  // Pull-up Register B
#define GPIOA    0x12  // GPIO Register A
#define GPIOB    0x13  // GPIO Register B

static matrix_row_t raw_matrix[MATRIX_ROWS];
static matrix_row_t matrix[MATRIX_ROWS];

// Row pins array
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

// MCP23017 helper function
static void mcp23017_write_register(uint8_t reg, uint8_t data) {
    uint8_t buf[2] = {reg, data};
    i2c_transmit((MCP23017_I2C_ADDRESS << 1), buf, 2, MCP23017_I2C_TIMEOUT);
}

void matrix_init_custom(void) {
    // Initialize I2C
    i2c_init();
    wait_ms(100);
    
    // Configure MCP23017
    // Set both ports A and B as outputs (for 14 columns to drive)
    mcp23017_write_register(IODIRA, 0x00);  // Port A all outputs (columns 0-7)
    mcp23017_write_register(IODIRB, 0x00);  // Port B all outputs (columns 8-13, bits 0-5)
    
    // Set all columns high initially (not selected)
    mcp23017_write_register(GPIOA, 0xFF);   // Port A all high
    mcp23017_write_register(GPIOB, 0xFF);   // Port B all high
    
    // Initialize row pins as inputs with pull-ups (for reading)
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        gpio_set_pin_input_high(row_pins[i]);
    }
    
    // Initialize matrix state
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i] = 0;
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;
    
    // Scan each column
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        // Select column (drive low)
        if (col < 8) {
            // Column 0-7 on Port A
            mcp23017_write_register(GPIOA, ~(1 << col));
            mcp23017_write_register(GPIOB, 0xFF);
        } else {
            // Column 8-13 on Port B
            mcp23017_write_register(GPIOA, 0xFF);
            mcp23017_write_register(GPIOB, ~(1 << (col - 8)));
        }
        
        // Wait longer for signal to stabilize (increased from 10us to 30us)
        wait_us(30);
        
        // Read all rows
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            // Read the row pin (low = pressed because of pull-up)
            bool key_pressed = !gpio_read_pin(row_pins[row]);
            
            // Update matrix state
            matrix_row_t mask = ((matrix_row_t)1 << col);
            if (key_pressed) {
                if (!(current_matrix[row] & mask)) {
                    current_matrix[row] |= mask;
                    changed = true;
                }
            } else {
                if (current_matrix[row] & mask) {
                    current_matrix[row] &= ~mask;
                    changed = true;
                }
            }
        }
    }
    
    // Deselect all columns (set high)
    mcp23017_write_register(GPIOA, 0xFF);
    mcp23017_write_register(GPIOB, 0xFF);
    
    return changed;
}

