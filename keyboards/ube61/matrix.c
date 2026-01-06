// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "i2c_master.h"

#define IODIRA   0x00
#define IODIRB   0x01
#define GPIOA    0x12
#define GPIOB    0x13

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

static void mcp23017_write(uint8_t reg, uint8_t data) {
    uint8_t buf[2] = {reg, data};
    i2c_transmit((MCP23017_I2C_ADDRESS << 1), buf, 2, MCP23017_I2C_TIMEOUT);
    wait_us(20);  // Ensure I2C write completes
}

void matrix_init_custom(void) {
    i2c_init();
    wait_ms(100);
    
    mcp23017_write(IODIRA, 0x00);
    mcp23017_write(IODIRB, 0x00);
    mcp23017_write(GPIOA, 0xFF);
    mcp23017_write(GPIOB, 0xFF);
    
    // Warm-up: cycle through all columns to initialize them
    // This ensures columns are properly charged and ready
    for (uint8_t warmup = 0; warmup < 3; warmup++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            if (col < 8) {
                mcp23017_write(GPIOB, 0xFF);
                wait_us(10);
                mcp23017_write(GPIOA, ~(1 << col));
            } else {
                mcp23017_write(GPIOA, 0xFF);
                wait_us(10);
                mcp23017_write(GPIOB, ~(1 << (col - 8)));
            }
            wait_us(20);
        }
        mcp23017_write(GPIOA, 0xFF);
        wait_us(10);
        mcp23017_write(GPIOB, 0xFF);
        wait_ms(5);
    }
    
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        gpio_set_pin_input_high(row_pins[i]);
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;
    
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        // Always write both ports to ensure clean state
        if (col < 8) {
            mcp23017_write(GPIOB, 0xFF);  // Deselect Port B first
            wait_us(10);
            mcp23017_write(GPIOA, ~(1 << col));  // Select column on Port A
        } else {
            mcp23017_write(GPIOA, 0xFF);  // Deselect Port A first
            wait_us(10);
            mcp23017_write(GPIOB, ~(1 << (col - 8)));  // Select column on Port B
        }
        
        wait_us(100);  // Longer settle time for signal stability
        
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            // Read multiple times and use majority voting for reliability
            bool read1 = !gpio_read_pin(row_pins[row]);
            wait_us(5);
            bool read2 = !gpio_read_pin(row_pins[row]);
            wait_us(5);
            bool read3 = !gpio_read_pin(row_pins[row]);
            
            // Key is pressed if at least 2 out of 3 reads detected it
            bool pressed = (read1 && read2) || (read2 && read3) || (read1 && read3);
            
            matrix_row_t mask = (1 << col);
            
            if (pressed) {
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
    
    mcp23017_write(GPIOA, 0xFF);
    wait_us(10);
    mcp23017_write(GPIOB, 0xFF);
    
    return changed;
}
