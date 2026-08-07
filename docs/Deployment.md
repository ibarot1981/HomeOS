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

It began as a board-only diagnostic firmware for the delivered Edgehax S3-PRO. It now keeps those startup diagnostics, runs the Version 0.2 clock screen, and supports the verified Version 0.3 button navigation when the display and buttons are wired according to `docs/Wiring.md`. It uses the `UART` USB-C connector on `COM7` at `115200` baud and prints chip, flash, heap, PSRAM, display pin, button, WiFi/NTP, and display refresh information.

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

Version 0.2 clock-screen result on 2026-08-04:

- PlatformIO build passed.
- The firmware keeps the board diagnostics and verified ePaper pin map.
- The display path now draws a clock screen instead of the hello-world screen.
- WiFi credentials are optional at build time and must live only in ignored local configuration.
- Without local credentials, the firmware builds and shows a clear `WiFi not configured` fallback screen.
- User ran VS Code PlatformIO build, upload, and monitor with local WiFi credentials in ignored `firmware/include/config.local.h`.
- The ePaper display showed the digital clock, top-right `WiFi` status, NTP sync status, and `Full refresh only`.
- USB power-cycle recovery passed; after reconnecting power, WiFi/NTP returned and the clock display recovered.
- One-minute full-refresh update passed; the displayed time was correct after the refresh.
- Physical `RESET` button behavior was not obvious during the user test and remains a separate board-behavior item.

Version 0.3 buttons/navigation build result:

- PlatformIO build passed.
- The firmware keeps the board diagnostics, WiFi/NTP clock path, and verified ePaper pin map.
- Button inputs use active-low wiring with internal pull-ups on `GPIO4`, `GPIO5`, and `GPIO6`.
- Previous and Next cycle between the Clock and Board screens.
- Select logs and redraws the active screen.
- Upload and hardware testing passed on 2026-08-06 over `COM7` after the wiring was confirmed against `docs/Wiring.md`.
- Serial output recorded one event for each tested normal button press with no observed false repeats; WiFi/NTP and Clock remained functional.

Version 0.4 module-manager build result:

- PlatformIO build passed on 2026-08-07.
- The firmware uses Clock and Status modules selected through a small built-in
  registry; Status retains the Board diagnostics content.
- The verified ePaper GPIO7-GPIO12 path, active-low GPIO4/GPIO5/GPIO6 button
  wiring, 50 ms debounce, and full-refresh-only display behavior are unchanged.
- Upload and physical navigation validation remain pending; no hardware rewiring
  is required.

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

For Version 0.2, only WiFi SSID and WiFi password are needed. Copy:

```text
firmware/include/config.example.h
```

to:

```text
firmware/include/config.local.h
```

Then fill in:

```cpp
#define HOMEOS_WIFI_SSID "your-wifi-ssid"
#define HOMEOS_WIFI_PASSWORD "your-wifi-password"
```

`config.local.h` is ignored by git. Do not commit it.

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
