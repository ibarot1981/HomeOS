# ESP32-S3 Notes

## Recommended Board

Use an ESP32-S3 DevKit with the ESP32-S3-WROOM-1-N16R8 module.

Delivered board status:

- received: 2026-07-29
- board marking: `Edgehax S3-PRO`
- module marking: `ESP32-S3-WROOM-1`
- module code marking: `MCN16R8`
- USB connector labels visible on PCB: `UART` and `USB`
- buttons visible on PCB: `RESET` and `BOOT`
- repository photos: `hardware/photos/ESP32 S3 Devkit/`
- board pinout PDF: `hardware/datasheets/edgehax-s3-pro-esp32-s3-wroom-n16r8-pinout.pdf`
- module datasheet PDF: `hardware/datasheets/espressif-esp32-s3-wroom-1-wroom-1u-datasheet.pdf`

The delivered module marking appears to match the intended N16R8 class. PSRAM, 16 MB flash, UART serial, PlatformIO upload, and the first wired ePaper hello-world test have been verified on the delivered board. Native USB behavior and the broader usable GPIO list still need to be verified before being treated as confirmed.

This gives:

- WiFi
- Bluetooth LE
- dual-core processor
- 16 MB flash
- 8 MB PSRAM
- native USB
- enough GPIO for display, buttons, buzzer, and future sensors

## Why Not Arduino Uno

The Arduino Uno R3 is useful for learning, but not ideal as the final controller for HomeOS.

Limitations:

- no built-in WiFi
- very limited RAM
- limited flash
- weaker support for HTTPS APIs
- harder Telegram/weather/calendar integration

The Uno can still be useful for simple sensor experiments.

## Why ESP32-S3 Instead of Basic ESP32

A basic ESP32-WROOM-32 would work, but ESP32-S3 gives more headroom.

Benefits:

- more memory on the N16R8 board
- native USB support in the ESP32-S3 chip
- better fit for graphics buffers
- room for OTA and larger firmware
- more flash space for fonts, icons, configuration, and future modules
- more RAM headroom for HTTPS, JSON parsing, and display work

## Important Pin Notes

Not all GPIO pins are equal. Some pins affect boot mode, some may be connected internally to flash/PSRAM, some may be used for USB, and some may not be available on a particular development board.

Rule:

- choose pin mappings from a known-good ESP32-S3 ePaper example when possible
- document the chosen pins in `Wiring.md`
- avoid changing pins casually after firmware starts depending on them
- do not finalize GPIO assignments until the exact DevKit pinout is checked
- avoid pins connected internally to flash/PSRAM, boot-strapping pins, USB pins, and unavailable pins where applicable

The exact development board matters, not only the `N16R8` module name. Before pin assignments are chosen, record the purchased board model and photograph both sides of the board.

Use the local Edgehax pinout PDF and the Espressif module datasheet in `hardware/datasheets/` before finalizing new GPIO assignments.

## Programming

Preferred setup:

- PlatformIO
- Arduino framework
- USB data cable
- serial monitor for logs

Arduino IDE can work, but PlatformIO is better for this long-term project.

The ESP32-S3 chip supports native USB, but development boards may expose native USB, USB-to-serial, or both through one or two physical USB connectors. The exact use of each USB connector must be checked against the purchased board's pinout or seller documentation.

The delivered Edgehax S3-PRO has two USB-C connectors labeled `UART` and `USB`. The first HomeOS PlatformIO environment is `edgehax_s3_pro_diagnostics`, using the generic PlatformIO `esp32-s3-devkitc-1` board target with explicit 16 MB flash and OPI PSRAM settings for the delivered `MCN16R8` module.

PlatformIO labels the base board target as `ESP32-S3-DevKitC-1-N8 (8 MB QD, No PSRAM)`, but HomeOS overrides the flash and PSRAM settings in `platformio.ini`. The real board values must be confirmed from serial output, not the generic board title alone.

First verified serial result:

- date: 2026-08-01
- connector used: `UART`
- Windows device: `USB-SERIAL CH340`
- Windows port during test: `COM7`
- serial monitor baud rate: `115200`
- boot ROM line observed: `ESP-ROM:esp32s3-20210327`
- factory firmware observed: `EDGEHAX ESP32-S3 AUTO TEST`
- PSRAM result: detected, 8 MB (`8388608` bytes)
- LED blink test: passed
- SD card test: mount failed; expected unless a compatible SD card is installed
- WiFi factory test: failed while trying SSID `Edgehax`; expected unless that factory-test network exists

First verified HomeOS PlatformIO result:

- date: 2026-08-01
- connector used: `UART`
- Windows port during test: `COM7`
- upload: succeeded with PlatformIO over `esptool`
- bootloader entry: automatic; no manual `BOOT`/`RESET` timing required
- chip observed by upload tool: ESP32-S3 revision `v0.2`
- upload tool features: WiFi, BLE, embedded PSRAM 8 MB
- flash size printed by firmware: 16 MB (`16777216` bytes)
- PSRAM printed by firmware: 8 MB class
- serial output: readable HomeOS diagnostics and periodic heartbeat

First verified HomeOS display result:

- date: 2026-08-03
- connector used: `UART`
- Windows port during test: `COM7`
- upload: succeeded with PlatformIO over `esptool`
- bootloader entry: automatic; no manual `BOOT`/`RESET` timing required
- flash size printed by firmware: 16 MB (`16777216` bytes)
- PSRAM printed by firmware: 8 MB class
- display wiring: GPIO11 MOSI, GPIO12 SCK, GPIO10 CS, GPIO8 DC, GPIO9 RST, GPIO7 BUSY, 3V3 power, common GND
- display result: Waveshare 4.2 inch ePaper full-refresh hello-world screen displayed successfully

A USB cable used for firmware flashing must support data. Some phone charging cables provide power only, and the board may turn on but not appear on the computer.

## WiFi

WiFi will be used for:

- time sync
- weather API
- Telegram bot
- OTA firmware updates
- optional future integrations

WiFi credentials should be stored securely and should not be committed to a public repository.

## Time

Use NTP for time sync. NTP means Network Time Protocol. It lets the ESP32 get the correct time from internet time servers.

For India, timezone should be set to IST, UTC+05:30.

An RTC module is not required for Version 1.

## Power

Power the ESP32-S3 DevKit through USB using a good phone charger or computer USB port.

For deployment, use a stable USB charger.

## PSRAM

PSRAM is extra external RAM attached to the ESP32 module.

It is useful for:

- display buffers
- icons
- fonts
- JSON parsing
- future APIs
- smoother firmware growth

The firmware configuration should enable PSRAM when using the N16R8 board. PSRAM must also be verified in firmware through a startup diagnostic rather than merely assumed.

## Initial Board Verification

Before connecting the display or other parts:

- confirm exact board model: delivered board is marked `Edgehax S3-PRO`
- inspect connector labels
- verify behavior of the `UART` and `USB` connectors
- use a known data cable
- confirm the board appears on the computer; first test showed `USB-SERIAL CH340 (COM7)` on the `UART` connector
- upload a basic serial test; first PlatformIO upload succeeded over `COM7`
- print flash size; first HomeOS diagnostic firmware printed 16 MB
- print PSRAM size; factory firmware already detected 8 MB
- record the successful PlatformIO board configuration; initial environment is `edgehax_s3_pro_diagnostics`
- first ePaper hello-world test succeeded on 2026-08-03 using the wiring documented in `docs/Wiring.md`
