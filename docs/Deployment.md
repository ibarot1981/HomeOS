# Deployment

## Development Deployment

During development, firmware is uploaded over USB.

Basic flow:

1. connect ESP32-S3 to computer using USB
2. build firmware
3. upload firmware
4. open serial monitor
5. observe logs
6. verify display behavior

## Preferred Tooling

Use PlatformIO when possible.

Benefits:

- clear project structure
- dependency management
- repeatable builds
- board configuration
- easier long-term maintenance

## First PlatformIO Environment

The first checked-in PlatformIO environment is:

```text
edgehax_s3_pro_diagnostics
```

It began as a board-only diagnostic firmware for the delivered Edgehax S3-PRO. It now keeps those startup diagnostics and also runs the Version 0.1 ePaper hello-world test when the display is wired according to `docs/Wiring.md`. It uses the `UART` USB-C connector on `COM7` at `115200` baud and prints chip, flash, heap, PSRAM, display pin, and display refresh information.

First verified result on 2026-08-01:

- PlatformIO build passed.
- PlatformIO upload passed over `COM7`.
- The board entered upload mode automatically; no manual `BOOT`/`RESET` sequence was needed.
- Serial monitor showed readable HomeOS diagnostics and heartbeat output.
- Firmware printed 16 MB flash and 8 MB-class PSRAM.

First display hello-world deployment result on 2026-08-03:

- PlatformIO build passed with GxEPD2 `1.6.9`.
- PlatformIO upload passed over `COM7`.
- The board entered upload mode automatically; no manual `BOOT`/`RESET` sequence was needed.
- Serial monitor showed readable HomeOS diagnostics, display pin mapping, GxEPD2 full-refresh output, and heartbeat output.
- Firmware printed 16 MB flash and 8 MB-class PSRAM.
- The Waveshare 4.2 inch ePaper display showed the HomeOS hello-world screen.

In VS Code:

1. open the HomeOS folder
2. wait for PlatformIO to finish loading
3. use the PlatformIO sidebar
4. run Build
5. run Upload with the board connected to the `UART` USB-C port
6. run Monitor at `115200` baud

If using a normal Windows terminal and `pio` is not on `PATH`, run PlatformIO through the extension's installed executable:

```powershell
& "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe" run
& "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe" run --target upload
& "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe" device monitor --port COM7 --baud 115200
```

## Configuration

Local configuration should include:

- WiFi SSID
- WiFi password
- Telegram bot token
- Telegram chat ID
- timezone
- weather location
- API keys if needed

These should not be committed to public source control.

## OTA Updates

OTA means Over-The-Air update. It allows firmware updates over WiFi without plugging in USB.

OTA should not be part of the first bring-up. Add it after:

- display works
- WiFi is stable
- serial debugging is understood
- recovery by USB is known

OTA safety rule:

Always keep USB flashing available as a fallback.

## Versioning

Use semantic-ish milestone versions:

- `v0.1-display-hello`
- `v0.2-clock`
- `v0.3-buttons`
- `v0.4-module-manager`
- `v1.0-desk-dashboard`

Every version should have:

- working firmware
- known hardware wiring
- updated docs
- short release notes

## First Release Definition

Version 1.0 is ready when:

- device boots reliably
- display shows useful information
- buttons work
- slideshow/fixed/smart modes work
- buzzer works
- Telegram basics work
- WiFi reconnect is acceptable
- wiring is documented
- setup instructions are clear

## Recovery Plan

If a firmware update breaks the device:

1. connect USB
2. put board into bootloader mode if needed
3. upload last known good firmware
4. check serial logs
5. document what failed
