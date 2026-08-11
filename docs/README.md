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
7. `Code-Map.md`
8. `visualizations/homeos-code-map.html` (optional interactive companion; open locally in a browser)
9. `Modules.md`
10. `UI.md`
11. `Wiring.md`
12. `Roadmap.md`
13. `Coding-Standards.md`
14. `Testing.md`
15. `Deployment.md`
16. `Decisions.md`

## Project Principle

This project should be built like a small product, not like a one-file Arduino experiment. Every milestone should leave behind a working device, clear documentation, and code that can be extended safely.

## Current Preferred Hardware

- Controller: received Edgehax S3-PRO with ESP32-S3-WROOM-1 module marked MCN16R8
- Display: received Waveshare 4.2 inch black-and-white SPI ePaper Module V2, Rev2.2, 400 x 300
- Interaction: three tactile buttons plus Telegram commands
- Alert output: passive buzzer
- Power: good-quality USB phone charger, typically 5 V / 1 A or better

Version 0.1 verified UART upload/serial on `COM7`, 16 MB flash, 8 MB-class PSRAM, the GxEPD2 display driver class, and the first ePaper wiring in `docs/Wiring.md`.

Version 0.2 verified the first clock screen with local ignored WiFi credentials, NTP sync, USB power-cycle recovery, one-minute full-refresh update, and the ePaper display showing a digital clock.

Version 0.3 verified breadboard buttons on GPIO4, GPIO5, and GPIO6 using active-low wiring and internal pull-ups. Previous and Next navigate between the Clock and Board diagnostics screens, Select redraws the active screen, and normal button presses are debounced and logged once.

Version 0.4 introduces a small built-in module registry. Clock and Status are the
two current modules; Status retains the board diagnostics. Previous and Next wrap
through the registry, Select redraws the active module, and ePaper refresh remains
full-screen only.

Version 0.5 adds compile-time Slideshow, Fixed, and Smart display modes.
Slideshow advances through Clock and Status every 60 seconds; Fixed retains the
module selected with Previous or Next; Smart temporarily shows Status for a
configured WiFi/NTP failure, then returns to the prior module. Physical
validation confirmed Slideshow timing and button behavior on 2026-08-09; Fixed
and Smart hardware validation passed on 2026-08-11. Smart validation also found
and fixed missing post-sync WiFi-loss detection so a recovered connection can
raise a later new alert.

## Documentation Layout

All project Markdown documentation belongs in this `docs/` folder. `AGENTS.md`
is the only Markdown file at the repository root. This file is the canonical
project overview; `docs/CHANGELOG.md` is the canonical changelog.

Still pending:

- native USB behavior
- broader usable GPIO list
- ePaper partial refresh and fast refresh
- exact physical `RESET` button behavior

## User Learning Profile

The intended builder has strong computer systems knowledge but beginner-level hands-on electronics experience. Explanations should assume comfort with software architecture, APIs, configuration, and debugging, but should not assume prior knowledge of voltage, GPIO, SPI, pull-up resistors, breadboards, sensors, or circuit safety.
