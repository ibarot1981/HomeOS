# Roadmap

The roadmap should produce working milestones, not unfinished branches of complexity. Each version should be something that can be demonstrated and understood.

## Phase 0: Project Setup

Goal: create the foundation.

Deliverables:

- repository structure
- documentation folder
- BOM
- hardware purchase links
- wiring notes
- first PlatformIO project

Success criteria:

- all important decisions are documented
- hardware list is clear
- future Codex tasks can refer to the docs

## Version 0.1: Display Hello World

Goal: prove the ESP32-S3 can control the 4.2 inch ePaper display.

Status:

- first full-refresh hello-world test passed on 2026-08-03
- partial refresh, fast refresh, and long-term refresh behavior remain future validation

Features:

- compile and flash firmware
- display text
- full screen refresh
- basic boot message

Learning:

- what flashing means
- how SPI wiring works
- what display BUSY means
- how to troubleshoot wrong pins

## Version 0.2: Clock Screen

Goal: show a useful first screen.

Status:

- firmware implementation started on 2026-08-04
- local PlatformIO build passed
- user-reported VS Code build, upload, monitor, WiFi/NTP sync, and ePaper clock display passed on 2026-08-04
- USB power-cycle recovery and one-minute full-refresh clock update passed on 2026-08-04

Features:

- WiFi connection
- NTP time sync
- date and time display
- timezone configuration
- manual refresh interval, currently as a firmware constant

Scope boundaries:

- full refresh only
- same verified ePaper wiring as Version 0.1
- no buttons, buzzer, Telegram, sensors, relays, or module-manager abstraction yet

Success criteria:

- screen shows correct local time
- device recovers after restart

Result:

- success criteria met using USB power-cycle restart; physical `RESET` button behavior still needs separate board-behavior investigation

## Version 0.3: Buttons and Navigation

Goal: allow local interaction.

Features:

- previous button
- select button
- next button
- button debounce
- simple navigation between built-in screens

Result:

- completed and hardware-verified on 2026-08-06 using USB power only
- Previous and Next navigate between Clock and Board; Select redraws the active screen
- normal button presses logged once with no observed false repeats

Deferred:

- long press detection, once there is a real settings or mode action
- formal module switcher, which belongs in Version 0.4

Learning:

- digital input
- pull-up behavior
- why buttons can produce multiple electrical transitions

## Version 0.4: Module Manager

Goal: introduce the HomeOS app model.

Features:

- module base class
- module registry
- current module state
- draw/update lifecycle
- Clock module
- Status module

Success criteria:

- adding a new module does not require rewriting the main loop

Result:

- implemented on 2026-08-07 with Clock and Status as the two built-in modules
- PlatformIO build passed
- physical navigation smoke test remains pending after upload; no rewiring is
  required

## Version 0.5: Display Modes

Goal: implement slideshow, fixed, and smart display modes.

Features:

- slideshow interval
- fixed module setting
- smart alert override
- return-to-previous-screen behavior

Success criteria:

- user can choose between passive dashboard and pinned view

## Version 0.6: Buzzer

Goal: add simple audible feedback.

Features:

- short beep
- alert tone
- silent mode
- notification queue

Learning:

- passive vs active buzzer
- PWM tones
- why volume control may need extra hardware later

## Version 0.7: Telegram Integration

Goal: allow remote control and notifications.

Features:

- Telegram bot setup
- allowed chat ID
- commands:
  - `/status`
  - `/module clock`
  - `/mode slideshow`
  - `/mode fixed`
  - `/beep`
- send alerts to Telegram

Success criteria:

- dashboard can be controlled without touching it

## Version 0.8: Weather Module

Goal: show real daily-use data.

Features:

- current temperature
- humidity if available
- rain chance
- forecast summary
- weather alert screen

## Version 0.9: Reminder and Todo Module

Goal: make the dashboard useful for family routine.

Features:

- locally stored reminders
- Telegram command to add reminder
- due reminder alert
- simple todo list

## Version 1.0: Stable Desk Dashboard

Goal: a polished first release.

Features:

- clock
- weather
- reminders
- navigation
- slideshow/fixed/smart modes
- Telegram basics
- buzzer
- documented wiring
- stable build and deployment guide

## Post 1.0: Hardware Modules

Possible modules:

- water tank level monitor
- electricity outage logger
- indoor temperature and humidity
- rain detector
- washing machine vibration detector
- refrigerator door monitor
- medicine reminder with button acknowledgment

## Long-Term Vision

HomeOS can become a reusable platform for multiple displays:

- one in the kitchen
- one near the entrance
- one in the bedroom
- one for factory alerts
- one for water and power monitoring
