// Copyright 2024 Jullian (@hul20)
// SPDX-License-Identifier: GPL-2.0-or-later

/*
 * Custom Matrix Scanning for UBE60P
 * 
 * Hardware Configuration:
 * - Rows (5): Directly driven by Pro Micro GPIO pins
 * - Columns (14): Read via MCP23017 I/O Expander over I2C
 * - Diode Direction: COL2ROW (diodes on columns, cathode to column wire)
 * 
 * MCP23017 Pin Mapping:
 * GPIOA (8 pins): Columns 0-7
 * GPIOB (6 pins): Columns 8-13 (bits 0-5, bits 6-7 unused)
 */

#include "quantum.h"
#include "i2c_master.h"
#include "print.h"

/* MCP23017 I2C Address (7-bit) */
#define MCP23017_I2C_ADDR 0x20

/* MCP23017 Register Addresses (BANK=0 mode, default) */
#define MCP23017_IODIRA   0x00  // I/O Direction Register A
#define MCP23017_IODIRB   0x01  // I/O Direction Register B
#define MCP23017_IPOLA    0x02  // Input Polarity Register A
#define MCP23017_IPOLB    0x03  // Input Polarity Register B
#define MCP23017_GPINTENA 0x04  // Interrupt-on-change A
#define MCP23017_GPINTENB 0x05  // Interrupt-on-change B
#define MCP23017_DEFVALA  0x06  // Default compare A
#define MCP23017_DEFVALB  0x07  // Default compare B
#define MCP23017_INTCONA  0x08  // Interrupt control A
#define MCP23017_INTCONB  0x09  // Interrupt control B
#define MCP23017_IOCON    0x0A  // Configuration register
#define MCP23017_GPPUA    0x0C  // Pull-up Register A
#define MCP23017_GPPUB    0x0D  // Pull-up Register B
#define MCP23017_INTFA    0x0E  // Interrupt flag A
#define MCP23017_INTFB    0x0F  // Interrupt flag B
#define MCP23017_INTCAPA  0x10  // Interrupt capture A
#define MCP23017_INTCAPB  0x11  // Interrupt capture B
#define MCP23017_GPIOA    0x12  // GPIO Register A
#define MCP23017_GPIOB    0x13  // GPIO Register B
#define MCP23017_OLATA    0x14  // Output Latch A
#define MCP23017_OLATB    0x15  // Output Latch B

/* Row pins on Pro Micro */
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

/* Track MCP23017 initialization state */
static bool mcp23017_initialized = false;
static uint8_t init_attempts = 0;

/* I2C timeout in milliseconds */
#define I2C_TIMEOUT 100

/*
 * Write a single byte to MCP23017 register
 */
static i2c_status_t mcp23017_write_reg(uint8_t reg, uint8_t data) {
    uint8_t buf[2] = {reg, data};
    i2c_status_t status = i2c_transmit(MCP23017_I2C_ADDR << 1, buf, 2, I2C_TIMEOUT);
    return status;
}

/*
 * Read a single byte from MCP23017 register
 */
static i2c_status_t mcp23017_read_reg(uint8_t reg, uint8_t *data) {
    i2c_status_t status;
    
    // First, write the register address
    status = i2c_transmit(MCP23017_I2C_ADDR << 1, &reg, 1, I2C_TIMEOUT);
    if (status != I2C_STATUS_SUCCESS) {
        return status;
    }
    
    // Then read the data
    status = i2c_receive((MCP23017_I2C_ADDR << 1) | 1, data, 1, I2C_TIMEOUT);
    return status;
}

/*
 * Initialize the MCP23017 for column reading
 * Configure all used pins as inputs with pull-ups enabled
 */
static bool mcp23017_init(void) {
    i2c_status_t status;
    
    uprintf("MCP23017: Initializing...\n");
    
    // Configure IOCON first (BANK=0, SEQOP=1 for byte mode)
    status = mcp23017_write_reg(MCP23017_IOCON, 0x20);
    if (status != I2C_STATUS_SUCCESS) {
        uprintf("MCP23017: IOCON write failed (%d)\n", status);
        return false;
    }
    
    // Set GPIOA as all inputs (columns 0-7)
    status = mcp23017_write_reg(MCP23017_IODIRA, 0xFF);
    if (status != I2C_STATUS_SUCCESS) {
        uprintf("MCP23017: IODIRA write failed (%d)\n", status);
        return false;
    }
    
    // Set GPIOB as all inputs (columns 8-13, bits 6-7 unused)
    status = mcp23017_write_reg(MCP23017_IODIRB, 0xFF);
    if (status != I2C_STATUS_SUCCESS) {
        uprintf("MCP23017: IODIRB write failed (%d)\n", status);
        return false;
    }
    
    // Enable pull-ups on GPIOA (columns 0-7)
    status = mcp23017_write_reg(MCP23017_GPPUA, 0xFF);
    if (status != I2C_STATUS_SUCCESS) {
        uprintf("MCP23017: GPPUA write failed (%d)\n", status);
        return false;
    }
    
    // Enable pull-ups on GPIOB (columns 8-13)
    status = mcp23017_write_reg(MCP23017_GPPUB, 0x3F);
    if (status != I2C_STATUS_SUCCESS) {
        uprintf("MCP23017: GPPUB write failed (%d)\n", status);
        return false;
    }
    
    // Verify by reading back IODIRA
    uint8_t verify = 0;
    status = mcp23017_read_reg(MCP23017_IODIRA, &verify);
    if (status != I2C_STATUS_SUCCESS || verify != 0xFF) {
        uprintf("MCP23017: Verification failed (status=%d, val=0x%02X)\n", status, verify);
        return false;
    }
    
    uprintf("MCP23017: Initialized successfully!\n");
    return true;
}

/*
 * Read all 14 columns from MCP23017
 * Returns a 16-bit value where bits 0-7 are GPIOA and bits 8-13 are GPIOB
 */
static uint16_t mcp23017_read_cols(void) {
    uint8_t gpioa = 0xFF;
    uint8_t gpiob = 0xFF;
    
    mcp23017_read_reg(MCP23017_GPIOA, &gpioa);
    mcp23017_read_reg(MCP23017_GPIOB, &gpiob);
    
    // Combine into 16-bit value, mask to 14 columns
    // Invert because pull-ups mean pressed = LOW
    uint16_t cols = ~((uint16_t)(gpiob & 0x3F) << 8 | gpioa) & 0x3FFF;
    
    return cols;
}

/*
 * Initialize matrix hardware
 * Called once at keyboard startup
 */
void matrix_init_custom(void) {
    uprintf("Matrix: Initializing custom matrix...\n");
    
    // Initialize I2C bus
    i2c_init();
    uprintf("Matrix: I2C initialized\n");
    
    // Longer delay for I2C bus and MCP23017 to stabilize after power-on
    wait_ms(50);
    
    // Initialize MCP23017
    mcp23017_initialized = mcp23017_init();
    init_attempts = 1;
    
    if (!mcp23017_initialized) {
        uprintf("Matrix: MCP23017 init FAILED!\n");
        uprintf("Matrix: Check I2C wiring - SDA=D1(pin 2), SCL=D0(pin 3)\n");
        uprintf("Matrix: Check MCP23017 address pins A0,A1,A2 are GND\n");
    }
    
    // Configure row pins as outputs, initially high (inactive)
    uprintf("Matrix: Configuring row pins...\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        gpio_set_pin_output(row_pins[row]);
        gpio_write_pin_high(row_pins[row]);
        uprintf("  ROW%d: pin %d configured\n", row, row_pins[row]);
    }
    
    uprintf("Matrix: Init complete (MCP23017 %s)\n", 
            mcp23017_initialized ? "OK" : "FAILED");
}

/* Status message counter */
static uint32_t scan_count = 0;
static bool startup_message_sent = false;

/*
 * Scan the matrix and update state
 * Called repeatedly by QMK matrix scanning loop
 * 
 * Returns true if matrix state changed
 */
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_changed = false;
    
    // Increment scan counter
    scan_count++;
    
    // Send startup status message after USB is ready (~2 seconds after boot)
    if (!startup_message_sent && scan_count > 2000) {
        startup_message_sent = true;
        uprintf("\n========== UBE60P STATUS ==========\n");
        uprintf("MCP23017 I2C Address: 0x%02X\n", MCP23017_I2C_ADDR);
        uprintf("MCP23017 Status: %s\n", mcp23017_initialized ? "OK" : "FAILED");
        uprintf("Init attempts: %d\n", init_attempts);
        uprintf("I2C SDA: D1 (pin 2), SCL: D0 (pin 3)\n");
        uprintf("===================================\n\n");
    }
    
    // Print periodic heartbeat every ~5 seconds
    if (scan_count % 5000 == 0) {
        uprintf("[%lu] MCP23017: %s\n", scan_count / 1000, 
                mcp23017_initialized ? "OK" : "FAILED - check I2C wiring!");
    }
    
    // Try to reinitialize MCP23017 if it failed previously
    if (!mcp23017_initialized) {
        // Only try every ~2 seconds
        static uint16_t retry_counter = 0;
        if (++retry_counter >= 2000) {
            retry_counter = 0;
            init_attempts++;
            uprintf("Matrix: Retrying MCP23017 init (attempt %d)...\n", init_attempts);
            mcp23017_initialized = mcp23017_init();
        }
        
        if (!mcp23017_initialized) {
            return false;
        }
    }
    
    // Scan each row
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        // Drive current row LOW (active)
        gpio_write_pin_low(row_pins[row]);
        
        // Delay for signal to stabilize through diodes and I2C read time
        // This is critical for reliable scanning with MCP23017
        wait_us(50);
        
        // Read column states from MCP23017
        matrix_row_t cols = mcp23017_read_cols();
        
        // Drive row HIGH again (inactive)
        gpio_write_pin_high(row_pins[row]);
        
        // Check if this row changed
        if (current_matrix[row] != cols) {
            current_matrix[row] = cols;
            matrix_changed = true;
        }
    }
    
    return matrix_changed;
}
