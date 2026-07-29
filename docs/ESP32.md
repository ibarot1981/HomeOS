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

The delivered module marking appears to match the intended N16R8 class, but the actual flash size, PSRAM size, USB behavior, and usable GPIO list must be verified through firmware and board documentation before being treated as confirmed.

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

## Programming

Preferred setup:

- PlatformIO
- Arduino framework
- USB data cable
- serial monitor for logs

Arduino IDE can work, but PlatformIO is better for this long-term project.

The ESP32-S3 chip supports native USB, but development boards may expose native USB, USB-to-serial, or both through one or two physical USB connectors. The exact use of each USB connector must be checked against the purchased board's pinout or seller documentation.

The delivered Edgehax S3-PRO has two USB-C connectors labeled `UART` and `USB`. For Version 0.1, record which connector appears in Windows, which connector PlatformIO can upload through, and which connector provides reliable serial logs.

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
- confirm the board appears on the computer
- upload a basic serial test
- print flash size
- print PSRAM size
- record the successful PlatformIO board configuration
