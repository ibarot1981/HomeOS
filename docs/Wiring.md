# Wiring

## Purpose

This document will become the live wiring reference. Every wire used in the project should eventually be listed here.

## Beginner Rule

Before changing wiring:

1. disconnect USB and every external power source
2. move wires
3. take a clear photograph before and after changing wiring
4. check against the wiring table
5. reconnect power

This simple habit prevents many mistakes.

Never rely solely on jumper-wire color. Wire colors are helpful labels, but the real rule is to follow endpoint labels: which pin on one device connects to which pin on the other device.

## ePaper Display Pins

Delivered Waveshare 4.2 inch ePaper module pin labels are printed on the interface board. The connector order visible in the repository photo is:

```text
BUSY
RST
DC
CS
CLK
DIN
GND
VCC
```

The through-hole header on the same board is printed in the reverse visual order:

```text
VCC
GND
DIN
CLK
CS
DC
RST
BUSY
```

Always follow the label printed next to the exact connector being wired. Do not wire by cable color.

The display PCB also has a `BS` interface selector marking. The printed table says `1` means 3-line SPI and `0` means 4-line SPI. Version 0.1 should use the vendor-documented 4-line SPI setup unless a matching example requires otherwise.

Typical 4.2 inch SPI ePaper module pins:

| Display Pin | Meaning | ESP32-S3 Connection |
|---|---|---|
| VCC | power | TBD - must be confirmed from the exact delivered module documentation |
| GND | ground | GND |
| DIN / MOSI | data from ESP32 to display | TBD |
| CLK / SCK | SPI clock | TBD |
| CS | chip select | TBD |
| DC | data/command select | TBD |
| RST | reset | TBD |
| BUSY | display busy signal | TBD |

The exact ESP32-S3 pins should be selected after checking the board pinout and display library examples.

Reference documents to check before wiring:

- Edgehax S3-PRO pinout: `hardware/datasheets/edgehax-s3-pro-esp32-s3-wroom-n16r8-pinout.pdf`
- Espressif ESP32-S3-WROOM-1 datasheet: `hardware/datasheets/espressif-esp32-s3-wroom-1-wroom-1u-datasheet.pdf`
- Waveshare 4.2 inch ePaper manual PDF: `hardware/datasheets/waveshare-4.2inch-epaper-module-manual.pdf`
- Live Waveshare manual: `https://www.waveshare.com/wiki/4.2inch_e-Paper_Module_Manual`

Some complete Waveshare-style interface boards accept a wider supply range, but raw panels and other boards may not. Logic-level compatibility and power-input voltage are separate questions. Version 0.1 wiring must follow the exact vendor manual or verified example for the delivered revision.

Delivered hardware notes:

- display board: Waveshare 4.2 inch e-Paper Module V2, Rev2.2
- controller board: Edgehax S3-PRO with ESP32-S3-WROOM-1 module marked MCN16R8
- controller USB labels: `UART` and `USB`; upload and serial behavior still must be verified
- wiring status: not finalized
- first safe step: verify board USB/serial behavior before connecting the display

## What Each Display Signal Means

### VCC

Power input for the display module.

### GND

Common electrical reference. The ESP32 and display must share ground.

### DIN / MOSI

The data line from ESP32 to display.

### CLK / SCK

The clock line. It tells the display when to read each bit of data.

### CS

Chip Select. It tells the display that the current SPI communication is meant for it.

### DC

Data/Command. It tells the display whether incoming bytes are commands or image data.

### RST

Reset. The ESP32 can use this to restart the display controller.

### BUSY

The display uses this to tell the ESP32, "wait, I am still refreshing."

## Buttons

Use three buttons:

| Button | Purpose | ESP32-S3 Pin |
|---|---|---|
| Previous | previous module | TBD |
| Select | select / mode | TBD |
| Next | next module | TBD |

Recommended software approach:

- connect one side of button to GPIO
- connect other side to GND
- enable internal pull-up in software

Behavior:

- not pressed: HIGH
- pressed: LOW

## Buzzer

All buzzer wiring is TBD until the buzzer type and current requirement are identified.

| Buzzer Pin | ESP32-S3 Connection |
|---|---|
| positive | TBD until identified |
| negative | TBD until identified |

A bare piezo element is a small sound element that may need only a tiny current. A magnetic passive buzzer can need more current than an ESP32 GPIO should provide directly. A three-pin buzzer module may include extra parts and may have separate signal, power, and ground pins.

If current demand is unknown, use a transistor driver rather than risking an ESP32 GPIO. Never connect the buzzer directly to 5 V through a GPIO.

## Connection Verification Table

| Wire number | From device | From pin | To device | To pin | Expected voltage or signal | Wire color | Verified by | Date |
|---|---|---|---|---|---|---|---|---|
| 1 | TBD | TBD | TBD | TBD | TBD | TBD | TBD | TBD |

## Power

Use USB power through the ESP32-S3 board.

Do not connect random external power directly until the board power pins are clearly understood.

## First Wiring Milestone

Minimum wiring for Version 0.1:

- ESP32-S3 connected to computer by USB
- ePaper display connected by SPI wires
- no buttons yet
- no buzzer yet

This reduces the number of possible mistakes during first display bring-up.

## First Power-On Checklist

1. Confirm exact ESP32 board.
2. Confirm exact display revision.
3. Verify all connections against the table.
4. Check that VCC and GND are not reversed.
5. Check for loose strands or accidental adjacent-pin contact.
6. Power initially from the computer USB port.
7. Watch for heat, smell, or unstable connection.
8. Disconnect immediately if anything becomes hot.
