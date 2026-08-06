# Project Context for Codex

Use this file when starting implementation tasks in Codex.

## Project

HomeOS is a modular ESP32-S3 plus 4.2 inch ePaper home dashboard. It should be built as a long-term firmware platform, not a single large Arduino sketch.

## User Profile

The user has strong computer systems knowledge but beginner hands-on electronics experience. When implementation affects wiring or hardware behavior, explain the reason in beginner-friendly language.

## Preferred Hardware

- received Edgehax S3-PRO with ESP32-S3-WROOM-1 module marked MCN16R8
- received Waveshare 4.2 inch black-and-white SPI ePaper Module V2, Rev2.2, 400 x 300
- three tactile buttons
- passive buzzer
- USB phone charger

Confirmed so far:

- UART USB-C upload and serial monitor on `COM7`
- 16 MB flash
- 8 MB-class PSRAM
- Waveshare 4.2 inch ePaper full-refresh hello-world using the wiring in `docs/Wiring.md`
- Version 0.2 clock-screen upload and display using local ignored WiFi credentials
- Version 0.2 USB power-cycle recovery and one-minute clock refresh
- Version 0.3 button wiring, debounced input, and Clock/Board navigation verified on GPIO4/5/6

Still unverified or pending:

- native USB behavior
- broader usable GPIO list
- ePaper partial refresh and fast refresh
- exact physical `RESET` button behavior

## Architecture Direction

Use:

- PlatformIO
- Arduino framework
- modular C++ structure

Avoid:

- one huge `main.ino`
- hardcoded secrets
- premature complex abstractions
- controlling mains power in early versions

## Firmware Areas

- core lifecycle
- display manager
- button driver
- buzzer driver
- WiFi service
- time service
- Telegram service
- module manager
- UI components
- individual modules

## Display Modes

Implement over time:

- slideshow mode
- fixed module mode
- smart alert mode

## Current Milestone

Version 0.1 passed:

- minimal PlatformIO project
- ESP32-S3 board configuration
- display dependency
- ePaper hello-world screen
- serial logging
- no Telegram yet
- no sensors yet

Version 0.2 starts the first useful screen:

- WiFi connection through ignored local credentials
- NTP time sync
- IST date and time display
- full-refresh ePaper clock screen
- no buttons, buzzer, Telegram, sensors, relays, or module-manager abstraction yet
