# Project Context for Codex

Use this file when starting implementation tasks in Codex.

## Project

HomeOS is a modular ESP32-S3 plus 4.2 inch ePaper home dashboard. It should be built as a long-term firmware platform, not a single large Arduino sketch.

## User Profile

The user has strong computer systems knowledge but beginner hands-on electronics experience. When implementation affects wiring or hardware behavior, explain the reason in beginner-friendly language.

## Preferred Hardware

- ESP32-S3 DevKit with ESP32-S3-WROOM-1-N16R8
- 4.2 inch black-and-white SPI ePaper display, 400 x 300, Waveshare-compatible
- three tactile buttons
- passive buzzer
- USB phone charger

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

