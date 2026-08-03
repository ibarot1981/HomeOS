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
| VCC | power | 3V3 for the first temporary USB-powered test |
| GND | ground | GND |
| DIN / MOSI | data from ESP32 to display | GPIO11 / MOSI |
| CLK / SCK | SPI clock | GPIO12 / SCK |
| CS | chip select | GPIO10 / SS |
| DC | data/command select | GPIO8 |
| RST | reset | GPIO9 |
| BUSY | display busy signal | GPIO7 |

This is the first verified temporary mapping for the Waveshare 4.2 inch e-Paper Module V2 Rev2.2 hello-world test. It uses the generic ESP32-S3 Arduino hardware SPI defaults for MOSI, SCK, and CS, plus nearby non-strapping GPIOs for DC, RST, and BUSY. It avoids ESP32-S3 strapping pins GPIO0, GPIO3, GPIO45, and GPIO46; USB pins GPIO19 and GPIO20; UART0 pins GPIO43 and GPIO44; and pins currently noted as onboard LED/JTAG-sensitive in the board pinout.

The display module manual says V2.1 and later Waveshare driver boards include level processing for 3.3 V and 5 V environments. For the first HomeOS test, use 3V3 from the ESP32-S3 board to keep display power and ESP32 logic at the same voltage. Do not use external power for this milestone.

The GxEPD2 driver class verified for the first full-refresh hello-world test is `GxEPD2_420_GDEY042T81`, listed by GxEPD2 for a 4.2 inch black-and-white 400 x 300 SSD1683 panel. This proves a basic full refresh on the delivered Waveshare V2 Rev2.2 module, but it does not yet prove partial refresh, fast refresh, or long-term refresh behavior.

Reference documents to check before wiring:

- Edgehax S3-PRO pinout: `hardware/datasheets/edgehax-s3-pro-esp32-s3-wroom-n16r8-pinout.pdf`
- Espressif ESP32-S3-WROOM-1 datasheet: `hardware/datasheets/espressif-esp32-s3-wroom-1-wroom-1u-datasheet.pdf`
- Waveshare 4.2 inch ePaper manual PDF: `hardware/datasheets/waveshare-4.2inch-epaper-module-manual.pdf`
- Live Waveshare manual: `https://www.waveshare.com/wiki/4.2inch_e-Paper_Module_Manual`

Some complete Waveshare-style interface boards accept a wider supply range, but raw panels and other boards may not. Logic-level compatibility and power-input voltage are separate questions. Version 0.1 wiring must follow the exact vendor manual or verified example for the delivered revision.

Delivered hardware notes:

- display board: Waveshare 4.2 inch e-Paper Module V2, Rev2.2
- controller board: Edgehax S3-PRO with ESP32-S3-WROOM-1 module marked MCN16R8
- controller USB labels: `UART` and `USB`; upload and serial behavior verified on the `UART` connector over `COM7`
- wiring status: first temporary display mapping physically verified on 2026-08-03
- first display result: full-refresh HomeOS hello-world screen displayed successfully

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
| 1 | Waveshare ePaper | VCC | Edgehax S3-PRO | 3V3 | 3.3 V module power | light gray / white | user photo and manual trace | 2026-08-03 |
| 2 | Waveshare ePaper | GND | Edgehax S3-PRO | GND | common ground | brown | user photo and manual trace | 2026-08-03 |
| 3 | Waveshare ePaper | DIN | Edgehax S3-PRO | GPIO11 | SPI MOSI | blue | user photo and manual trace | 2026-08-03 |
| 4 | Waveshare ePaper | CLK | Edgehax S3-PRO | GPIO12 | SPI SCK | yellow | user photo and manual trace | 2026-08-03 |
| 5 | Waveshare ePaper | CS | Edgehax S3-PRO | GPIO10 | chip select | orange | user photo and manual trace | 2026-08-03 |
| 6 | Waveshare ePaper | DC | Edgehax S3-PRO | GPIO8 | data/command select | green | user photo and manual trace | 2026-08-03 |
| 7 | Waveshare ePaper | RST | Edgehax S3-PRO | GPIO9 | display reset | white / gray | user photo and manual trace | 2026-08-03 |
| 8 | Waveshare ePaper | BUSY | Edgehax S3-PRO | GPIO7 | display busy signal | purple | user photo and manual trace | 2026-08-03 |

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
