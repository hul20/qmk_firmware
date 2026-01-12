// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "i2c_master.h"

#define IODIRA 0x00
#define IODIRB 0x01
#define GPIOA 0x12
#define GPIOB 0x13

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

static void mcp23017_write(uint8_t reg, uint8_t data) {
    uint8_t buf[2] = {reg, data};
    i2c_transmit((MCP23017_I2C_ADDRESS << 1), buf, 2, MCP23017_I2C_TIMEOUT);
}

void matrix_init_custom(void) {
    i2c_init();
    wait_ms(100);

    mcp23017_write(IODIRA, 0x00);
    mcp23017_write(IODIRB, 0x00);
    mcp23017_write(GPIOA, 0xFF);
    mcp23017_write(GPIOB, 0xFF);

    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        gpio_set_pin_input_high(row_pins[i]);
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    // Phase 1: Scan Columns 0-7 (Port A)
    // Deactivate Port B columns first so we don't need to write to it in the loop
    mcp23017_write(GPIOB, 0xFF);

    for (uint8_t col = 0; col < 8; col++) {
        // Activate specific column on Port A
        mcp23017_write(GPIOA, ~(1 << col));
        wait_us(30);

        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            bool         pressed = !gpio_read_pin(row_pins[row]);
            matrix_row_t mask    = (1 << col);

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

    // Phase 2: Scan Columns 8-13 (Port B)
    // Deactivate Port A columns
    mcp23017_write(GPIOA, 0xFF);

    for (uint8_t col = 8; col < MATRIX_COLS; col++) {
        // Activate specific column on Port B (adjusted for 0-index on port)
        mcp23017_write(GPIOB, ~(1 << (col - 8)));
        wait_us(30);

        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            bool         pressed = !gpio_read_pin(row_pins[row]);
            matrix_row_t mask    = (1 << col);

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

    // Reset Port B to high (Port A is already high from Phase 2 start)
    mcp23017_write(GPIOB, 0xFF);

    return changed;
}
