# UBE61 Pinout Reference

## Arduino Pro Micro Pinout

```
                    Arduino Pro Micro
                   (ATmega32u4 - 5V/16MHz)

         ┌─────────────────────────────┐
         │  [ ]                    [ ]  │
         │  [ ]                    [ ]  │
    GND  │  [ ]●                  ●[ ]  │  RAW
    GND  │  [ ]●                  ●[ ]  │  GND
    SDA  │  [ ]●  D1/PD1 (I2C)   ●[ ]  │  RST
    SCL  │  [ ]●  D0/PD0 (I2C)   ●[ ]  │  VCC
 ROW 0   │  [ ]●  D3/PD3          [ ]  │  A3/PF4
 ROW 1   │  [ ]●  D2/PD2          [ ]  │  A2/PF5
 ROW 2   │  [ ]●  D4/PD4          [ ]  │  A1/PF6
 ROW 3   │  [ ]●  C6/PC6          [ ]  │  A0/PF7
 ROW 4   │  [ ]●  E6/PE6          [ ]  │  15/PB1
         │  [ ]   B5/PB5          [ ]  │  14/PB3
         │  [ ]   B4/PB4          [ ]  │  16/PB2
         │  [ ]   B6/PB6          [ ]  │  10/PB6
         │       USB                   │
         └─────────────────────────────┘

● = Used for UBE61
```

**Used Pins:**

-   **D0** (PD0) - I2C SCL
-   **D1** (PD1) - I2C SDA
-   **D2** (PD2) - Row 1
-   **D3** (PD3) - Row 0
-   **D4** (PD4) - Row 2
-   **C6** (PC6) - Row 3
-   **E6** (PE6) - Row 4
-   **VCC** - Power to MCP23017
-   **GND** - Ground to MCP23017

**Available Pins (unused):**

-   A0, A1, A2, A3, 10, 14, 15, 16, B4, B5, B6

## MCP23017 (CJMCU-2317) Pinout

```
                    MCP23017 on CJMCU-2317
                    (I2C GPIO Expander)

         ┌─────────────────────────────┐
    COL8 │  [ ]●  GPB0           VCC ●[ ]  │  +5V (from Pro Micro)
    COL9 │  [ ]●  GPB1           GND ●[ ]  │  GND (from Pro Micro)
   COL10 │  [ ]●  GPB2            NC  [ ]  │
   COL11 │  [ ]●  GPB3           SCL ●[ ]  │  D0 (from Pro Micro)
   COL12 │  [ ]●  GPB4           SDA ●[ ]  │  D1 (from Pro Micro)
   COL13 │  [ ]●  GPB5            NC  [ ]  │
         │  [ ]   GPB6           RST  [ ]  │  (internal pull-up)
         │  [ ]   GPB7           A0  ●[ ]  │  GND (address select)
         │  [ ]   GND            A1  ●[ ]  │  GND (address select)
         │  [ ]   VCC            A2  ●[ ]  │  GND (address select)
    COL0 │  [ ]●  GPA0          GPA7 ●[ ]  │  COL7
    COL1 │  [ ]●  GPA1          GPA6 ●[ ]  │  COL6
    COL2 │  [ ]●  GPA2          GPA5 ●[ ]  │  COL5
    COL3 │  [ ]●  GPA3          GPA4 ●[ ]  │  COL4
         └─────────────────────────────┘

● = Used for UBE61
```

**I2C Address Configuration:**

-   A0 = GND, A1 = GND, A2 = GND → **0x20** (default)

**Column Assignments:**

-   **Port A**: GPA0-GPA7 → Columns 0-7
-   **Port B**: GPB0-GPB5 → Columns 8-13
-   GPB6-GPB7 are unused

## Connection Summary

### Power Rails

```
Pro Micro VCC ──────┬──── MCP23017 VCC
                    │
                    └──── (optional) LED power

Pro Micro GND ──────┬──── MCP23017 GND
                    ├──── MCP23017 A0
                    ├──── MCP23017 A1
                    └──── MCP23017 A2
```

### I2C Bus

```
Pro Micro D0 (SCL) ───────── MCP23017 SCL
Pro Micro D1 (SDA) ───────── MCP23017 SDA

Note: Most CJMCU-2317 modules have built-in
      10kΩ pull-up resistors on SCL and SDA
```

### Row Connections

```
Pro Micro       Wire Color     Function
---------       ----------     --------
   D3    ───→   (suggest red)  ──→ Row 0
   D2    ───→   (suggest ora)  ──→ Row 1
   D4    ───→   (suggest yel)  ──→ Row 2
   C6    ───→   (suggest grn)  ──→ Row 3
   E6    ───→   (suggest blu)  ──→ Row 4
```

### Column Connections

```
MCP23017        Wire Color       Function
--------        ----------       --------
  GPA0   ───→   (suggest blk)   ──→ Column 0
  GPA1   ───→   (suggest brn)   ──→ Column 1
  GPA2   ───→   (suggest red)   ──→ Column 2
  GPA3   ───→   (suggest ora)   ──→ Column 3
  GPA4   ───→   (suggest yel)   ──→ Column 4
  GPA5   ───→   (suggest grn)   ──→ Column 5
  GPA6   ───→   (suggest blu)   ──→ Column 6
  GPA7   ───→   (suggest vio)   ──→ Column 7
  GPB0   ───→   (suggest gry)   ──→ Column 8
  GPB1   ───→   (suggest wht)   ──→ Column 9
  GPB2   ───→   (any color)     ──→ Column 10
  GPB3   ───→   (any color)     ──→ Column 11
  GPB4   ───→   (any color)     ──→ Column 12
  GPB5   ───→   (any color)     ──→ Column 13
```

## Physical Key to Matrix Map

### Row 0 (D3)

```
Col:  0    1    2    3    4    5    6    7    8    9   10   11   12   13
Key: ESC   1    2    3    4    5    6    7    8    9    0    -    =   BSPC
```

### Row 1 (D2)

```
Col:  0    1    2    3    4    5    6    7    8    9   10   11   12   13
Key: TAB   Q    W    E    R    T    Y    U    I    O    P    [    ]    \
```

### Row 2 (D4)

```
Col:  0    1    2    3    4    5    6    7    8    9   10   11   12
Key: CAPS  A    S    D    F    G    H    J    K    L    ;    '   ENT
```

### Row 3 (C6)

```
Col:  0    1    2    3    4    5    6    7    8    9   10   11
Key: SHFT  Z    X    C    V    B    N    M    ,    .    /   SHFT
```

### Row 4 (E6)

```
Col:  0    1    2    6              10   11   12   13
Key: CTRL GUI  ALT  SPC            ALT  GUI  MENU CTRL
```

## Diode Orientation

```
     ROW (from Pro Micro)
      │
      ├─── Switch ───┐
      │              │
      │           Diode
      │         (Anode)
      │              │
      │          (Cathode)
      │              │
      │              ▼ (Black band)
      │              │
      │              └─── COLUMN (to MCP23017)
      │
```

**Remember:** Cathode (black band) points toward COLUMN

## Testing Points

### I2C Communication Test

```
Multimeter in Continuity Mode:

Pro Micro D0 ←→ MCP23017 SCL  (should beep)
Pro Micro D1 ←→ MCP23017 SDA  (should beep)
MCP23017 VCC ←→ +5V           (should beep)
MCP23017 GND ←→ Ground        (should beep)
```

### Voltage Test

```
Multimeter in DC Voltage Mode:

Pro Micro VCC to GND:  ~5.0V
MCP23017 VCC to GND:   ~5.0V
```

### Row Continuity Test

```
With keyboard powered OFF:

Pro Micro D3 ←→ Any switch in Row 0 (one terminal)
Pro Micro D2 ←→ Any switch in Row 1 (one terminal)
Pro Micro D4 ←→ Any switch in Row 2 (one terminal)
Pro Micro C6 ←→ Any switch in Row 3 (one terminal)
Pro Micro E6 ←→ Any switch in Row 4 (one terminal)
```

### Column Continuity Test

```
With keyboard powered OFF:

MCP23017 GPA0 ←→ Diode cathode in Column 0
MCP23017 GPA1 ←→ Diode cathode in Column 1
... and so on for all 14 columns
```

## Wire Recommendations

### Wire Gauge

-   **Power (VCC/GND)**: 22-24 AWG
-   **I2C (SCL/SDA)**: 24-26 AWG
-   **Rows/Columns**: 26-28 AWG

### Wire Length

-   Keep I2C wires as short as practical (<30cm ideal)
-   Keep rows/columns organized and neat
-   Leave some slack for rework if needed

### Color Coding

Use consistent colors for easy debugging:

-   **Red** = VCC/Power
-   **Black** = GND/Ground
-   **Yellow** = SCL
-   **Blue** = SDA
-   **Various** = Rows (one color per row)
-   **Various** = Columns (one color per column if possible)

---

**Pro Tip:** Print this document and keep it handy while wiring!
