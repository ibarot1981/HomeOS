# HomeOS Design Pack

HomeOS is a long-term DIY project to build a modular home information appliance using an ESP32-S3 controller and a 4.2 inch SPI ePaper display. The goal is not only to make a useful dashboard, but also to create a beginner-friendly learning path for electronics while keeping the software architecture clean enough to grow for months or years.

This folder is meant to be uploaded into a new ChatGPT Project and used as the single source of truth for future planning, implementation, Codex prompts, reviews, wiring, and troubleshooting.

## Recommended Reading Order

1. `Project.md`
2. `Hardware.md`
3. `Electronics-Basics.md`
4. `ESP32.md`
5. `Display.md`
6. `Architecture.md`
7. `Modules.md`
8. `UI.md`
9. `Wiring.md`
10. `Roadmap.md`
11. `Coding-Standards.md`
12. `Testing.md`
13. `Deployment.md`
14. `Decisions.md`

## Project Principle

This project should be built like a small product, not like a one-file Arduino experiment. Every milestone should leave behind a working device, clear documentation, and code that can be extended safely.

## Current Preferred Hardware

- Controller: received Edgehax S3-PRO with ESP32-S3-WROOM-1 module marked MCN16R8
- Display: received Waveshare 4.2 inch black-and-white SPI ePaper Module V2, Rev2.2, 400 x 300
- Interaction: three tactile buttons plus Telegram commands
- Alert output: passive buzzer
- Power: good-quality USB phone charger, typically 5 V / 1 A or better

Version 0.1 verified UART upload/serial on `COM7`, 16 MB flash, 8 MB-class PSRAM, the GxEPD2 display driver class, and the first ePaper wiring in `docs/Wiring.md`.

Version 0.2 verified the first clock screen with local ignored WiFi credentials, NTP sync, and the ePaper display showing a digital clock.

Still pending:

- native USB behavior
- broader usable GPIO list
- ePaper partial refresh and fast refresh
- one-minute clock refresh behavior over longer runtime

## User Learning Profile

The intended builder has strong computer systems knowledge but beginner-level hands-on electronics experience. Explanations should assume comfort with software architecture, APIs, configuration, and debugging, but should not assume prior knowledge of voltage, GPIO, SPI, pull-up resistors, breadboards, sensors, or circuit safety.
