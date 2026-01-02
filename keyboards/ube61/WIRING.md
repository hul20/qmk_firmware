# UBE61 Wiring Guide

## Component List

-   1x Arduino Pro Micro (ATmega32u4)
-   1x CJMCU-2317 (MCP23017 I2C GPIO Expander)
-   61x Mechanical keyboard switches
-   61x IN4148 diodes
-   Wire for connections

## Wiring Diagram

### Pro Micro to MCP23017 (I2C Connection)

```
Pro Micro          CJMCU-2317 (MCP23017)
---------          ---------------------
   VCC    ------→     VCC
   GND    ------→     GND
   D1     ------→     SDA
   D0     ------→     SCL
```

### MCP23017 Address Configuration (for 0x20)

```
CJMCU-2317 (MCP23017)
---------------------
   A0     ------→     GND
   A1     ------→     GND
   A2     ------→     GND
```

### Pro Micro Row Connections

Connect these pins from Pro Micro to the row lines:

```
Pro Micro Pin    →    Row Number
-------------          ----------
     D3         →      Row 0
     D2         →      Row 1
     D4         →      Row 2
     C6         →      Row 3
     E6         →      Row 4
```

### MCP23017 Column Connections

Connect these pins from MCP23017 to the column lines:

```
MCP23017 Pin     →    Column Number
------------           -------------
    GPA0       →      Column 0
    GPA1       →      Column 1
    GPA2       →      Column 2
    GPA3       →      Column 3
    GPA4       →      Column 4
    GPA5       →      Column 5
    GPA6       →      Column 6
    GPA7       →      Column 7
    GPB0       →      Column 8
    GPB1       →      Column 9
    GPB2       →      Column 10
    GPB3       →      Column 11
    GPB4       →      Column 12
    GPB5       →      Column 13
```

## Switch Matrix Construction

### Diode Orientation (COL2ROW)

Since we're using COL2ROW configuration with diodes in columns:

```
For each switch:

    Row Line ────┬──── Switch ──── Column Line
                 │
              Diode (cathode/black band toward column)
                 │
                GND
```

Each switch connects:

1. One terminal to a ROW line
2. Other terminal to a DIODE (anode)
3. Diode cathode (black band) to a COLUMN line

### Example for a Single Key

```
Switch at position Row 0, Column 0 (ESC key):

Pro Micro D3 ──── [Switch] ──── |>|─── MCP23017 GPA0
(Row 0)                      (Diode)   (Column 0)
```

## Matrix Mapping

### Physical Layout to Matrix Positions

```
Row 0: ESC   1    2    3    4    5    6    7    8    9    0    -    =    BACKSPACE
       [0,0][0,1][0,2][0,3][0,4][0,5][0,6][0,7][0,8][0,9][0,10][0,11][0,12][0,13]

Row 1: TAB   Q    W    E    R    T    Y    U    I    O    P    [    ]    \
       [1,0][1,1][1,2][1,3][1,4][1,5][1,6][1,7][1,8][1,9][1,10][1,11][1,12][1,13]

Row 2: CAPS  A    S    D    F    G    H    J    K    L    ;    '    ENTER  ---
       [2,0][2,1][2,2][2,3][2,4][2,5][2,6][2,7][2,8][2,9][2,10][2,11][2,12]

Row 3: SHIFT Z    X    C    V    B    N    M    ,    .    /    SHIFT ---   ---
       [3,0][3,1][3,2][3,3][3,4][3,5][3,6][3,7][3,8][3,9][3,10][3,11]

Row 4: CTRL  GUI  ALT  ---  ---  --- SPACE ---  ---  --- ALT  GUI  MENU CTRL
       [4,0][4,1][4,2]              [4,6]              [4,10][4,11][4,12][4,13]
```

## Testing Checklist

### Step 1: Test I2C Communication

1. Connect Pro Micro to computer via USB
2. Flash the firmware
3. If keyboard is detected by computer, I2C is likely working

### Step 2: Test Rows

1. Use a multimeter in continuity mode
2. Touch each row pin on Pro Micro to verify connection to switches
3. Each row should connect to 12-14 switches

### Step 3: Test Columns

1. Verify each column connects to its respective MCP23017 pin
2. Check diode orientation (cathode toward column)
3. Each column should connect to 4-5 switches

### Step 4: Test Individual Keys

1. Open a text editor
2. Press each key to verify it registers
3. If a key doesn't work:
    - Check the switch connection
    - Verify the diode is properly oriented
    - Test the solder joints

## Common Issues

### No keys work

-   Check I2C connections (SDA/SCL)
-   Verify MCP23017 has power (VCC/GND)
-   Check I2C address is correct (0x20)

### Entire row doesn't work

-   Check Pro Micro row pin connection
-   Verify row wire continuity

### Entire column doesn't work

-   Check MCP23017 column pin connection
-   Verify column wire continuity
-   Check all diodes in that column

### Single key doesn't work

-   Check switch solder joints
-   Verify diode orientation and connection
-   Test switch itself (may be defective)

### Keys register multiple times

-   Add/adjust debounce in config.h (default is 5ms)
-   Check for solder bridges between adjacent pins

## Pro Tips

1. **Use different colored wires** for rows and columns to make debugging easier
2. **Test as you build** - verify each row/column before moving to the next
3. **Label your wires** - it helps during troubleshooting
4. **Keep wires organized** - use cable management to prevent shorts
5. **Double-check diode orientation** - most common mistake in hand-wired builds
