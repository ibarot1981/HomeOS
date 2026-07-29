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

Do not treat flash size, PSRAM size, USB behavior, display driver class, or GPIO wiring as confirmed until Version 0.1 verification proves them on the delivered hardware.

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

## Initial Milestone

Start with Version 0.1:

- minimal PlatformIO project
- ESP32-S3 board configuration
- display dependency
- ePaper hello-world screen
- serial logging
- no Telegram yet
- no sensors yet
