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

Version 0.3 adds three active-low tactile buttons. This keeps the circuit simple:
the ESP32-S3 enables an internal pull-up resistor for each GPIO, and pressing the
button connects that GPIO to `GND`.

| Button | Purpose | ESP32-S3 Pin |
|---|---|---|
| Previous | previous screen | GPIO4 |
| Select | select / redraw current screen | GPIO5 |
| Next | next screen | GPIO6 |

Wire each button like this:

- connect one side of button to GPIO
- connect other side to GND
- enable internal pull-up in software

Behavior:

- not pressed: HIGH
- pressed: LOW

Button GPIO selection notes:

- `GPIO4`, `GPIO5`, and `GPIO6` are exposed on the Edgehax S3-PRO pinout.
- They are not used by the verified ePaper wiring.
- They avoid ESP32-S3 strapping pins `GPIO0`, `GPIO3`, `GPIO45`, and `GPIO46`.
- They avoid USB pins `GPIO19` and `GPIO20`.
- They avoid UART0 pins `GPIO43` and `GPIO44`.
- They avoid the onboard LED/JTAG-sensitive pins currently noted in the board pinout.

Before wiring buttons:

1. disconnect USB power
2. keep the verified ePaper wires unchanged
3. connect Previous between `GPIO4` and `GND`
4. connect Select between `GPIO5` and `GND`
5. connect Next between `GPIO6` and `GND`
6. check there is no connection from any button to `3V3` or `5V`
7. reconnect USB power only after the wiring matches this table

## Buzzer

The Version 0.6 SmartElex Passive Buzzer Module has three observed labels, from
left to right in `hardware/photos/SmartElex Passive Buzzer Module/PXL_20260817_154237701.jpg`:
`-`, `NC`, and `S`. The supplied generic PDF's `VCC`, `GND`, `SIG / IN` table is
not valid for this physical revision.

User-performed continuity measurements verified the actual module wiring:

| PCB label | Confirmed function | Buzzer lead | HomeOS connection |
|---|---|---|---|
| `-` | negative coil terminal | lead 1 | BC337-25 collector and diode anode |
| `NC` | no connection | none | leave unconnected |
| `S` | positive coil terminal | lead 2 beside moulded `+` | dedicated LDO 3.3 V output and diode cathode |

The two coil leads measure 42.6 ohm. The 3.3 V DC upper bound is about 77 mA;
the ESP32 GPIO must not drive it directly.

### Planned low-side driver (not yet wired)

Required parts:

- 1 x BC337-25 NPN transistor, through-hole TO-92 (buy a spare)
- 1 x 470 ohm, 0.25 W resistor from `GPIO17` to the transistor base (buy spares)
- 1 x 10 kOhm, 0.25 W resistor from base to common GND (buy spares)
- 1 x 1N5819 Schottky diode (buy a spare); its band marks the cathode
- 1 x AMS1117-3.3 fixed-output LDO module, rated at least 500 mA, powered from 5 V
- 1 x 100 uF electrolytic capacitor rated at least 10 V, plus 1 x 100 nF ceramic
  capacitor, across the LDO output near the buzzer
- a solderless breadboard and suitable 2.54 mm jumper wires, if the existing
  breadboard cannot hold the driver safely
- soldering iron, rosin-core solder, and a stand to solder the supplied module
  header before a reliable connection can be made

Do not substitute a BC547/BC548 (their collector-current margin is inadequate)
or an IRF520 module (it is not a suitable 3.3 V logic-level choice here).

Planned electrical connections:

```text
Edgehax 5V (USB-powered only) ---- AMS1117 VIN
Edgehax GND ---------------------- AMS1117 GND ---- BC337 emitter ---- common GND
AMS1117 3V3 OUT ------------------ buzzer S (+ coil)

buzzer - (other coil) ------------ BC337 collector
GPIO17 ---- 470 ohm -------------- BC337 base
BC337 base ---- 10 kOhm ---------- common GND

1N5819 cathode (banded end) ------ buzzer S (+ coil)
1N5819 anode --------------------- buzzer - / BC337 collector

100 uF and 100 nF capacitors ----- between AMS1117 3V3 OUT and common GND
NC -------------------------------- leave unconnected
```

The LDO's 3.3 V output powers only the buzzer circuit; do **not** join it to the
ESP32 board's 3.3 V pin. The common ground is required so `GPIO17` has a valid
base-drive reference. The base pull-down holds the transistor off during reset
and boot. The flyback diode is reverse-biased while the buzzer is on and protects
the transistor when PWM switches the magnetic coil off.

Before any connection to the module or GPIO, disconnect USB, solder only the
header with its pins facing down for breadboard use, inspect for solder bridges,
then test the LDO by itself: board 5 V to GND must be approximately 5 V and LDO
output to GND must be approximately 3.3 V. Do not power the circuit if either
reading is outside expectation. Physical wiring remains unvalidated until this
procedure is completed and recorded.

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
| 9 | Previous button | one side | Edgehax S3-PRO | GPIO4 | active-low input with internal pull-up | user wiring | display and serial test | 2026-08-06 |
| 10 | Previous button | other side | Edgehax S3-PRO | GND | ground when pressed | user wiring | display and serial test | 2026-08-06 |
| 11 | Select button | one side | Edgehax S3-PRO | GPIO5 | active-low input with internal pull-up | user wiring | display and serial test | 2026-08-06 |
| 12 | Select button | other side | Edgehax S3-PRO | GND | ground when pressed | user wiring | display and serial test | 2026-08-06 |
| 13 | Next button | one side | Edgehax S3-PRO | GPIO6 | active-low input with internal pull-up | user wiring | display and serial test | 2026-08-06 |
| 14 | Next button | other side | Edgehax S3-PRO | GND | ground when pressed | user wiring | display and serial test | 2026-08-06 |

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

## Version 0.2 Wiring

Version 0.2 keeps the same verified ePaper wiring table and still uses USB power through the ESP32-S3 board only. Do not add buttons, buzzer, sensors, relays, or external power for the clock-screen test.

Before uploading the Version 0.2 firmware, re-check the display wires against the connection verification table above. The firmware still uses GPIO11 MOSI, GPIO12 SCK, GPIO10 CS, GPIO8 DC, GPIO9 RST, and GPIO7 BUSY.

## Version 0.3 Wiring

Version 0.3 keeps the same verified ePaper wiring and adds only the three active-low
buttons on `GPIO4`, `GPIO5`, and `GPIO6`.

Do not change the ePaper connections. Do not add buzzer, sensors, relays, external
power, or mains-powered wiring for this milestone. The button wiring above was
validated on 2026-08-06 using USB power through the ESP32-S3 board only.

## First Power-On Checklist

1. Confirm exact ESP32 board.
2. Confirm exact display revision.
3. Verify all connections against the table.
4. Check that VCC and GND are not reversed.
5. Check for loose strands or accidental adjacent-pin contact.
6. Power initially from the computer USB port.
7. Watch for heat, smell, or unstable connection.
8. Disconnect immediately if anything becomes hot.
