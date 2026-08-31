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
- upload and hardware validation passed over `COM7`; Clock, Status, navigation,
  Select redraws, and WiFi/NTP retry were verified with no rewiring

## Version 0.5: Display Modes

Goal: implement slideshow, fixed, and smart display modes.

Features:

- slideshow interval
- fixed module setting
- smart alert override
- return-to-previous-screen behavior

Result:

- implemented on 2026-08-08 with a compile-time mode constant
- Slideshow advances through Clock and Status every 60 seconds
- Fixed keeps the module selected with Previous or Next on screen
- Smart temporarily shows Status for 15 seconds when configured WiFi/NTP is
  unhealthy, then restores the module that was displayed before the alert
- PlatformIO builds and uploads passed over `COM7` for all three modes
- Slideshow hardware validation passed on 2026-08-09; Fixed and Smart hardware
  validation passed on 2026-08-11
- Smart validation confirmed one 15-second override per uninterrupted WiFi
  failure, five-minute WiFi/NTP recovery, and a new alert after a later failure
- post-sync WiFi-loss detection was fixed during validation; NTP-only failure
  after a healthy sync remains untested

Success criteria:

- user can choose between passive dashboard and pinned view

## Version 0.6: Buzzer

Goal: add simple audible feedback.

Hardware status:

- SmartElex Passive Buzzer Module received on 2026-08-17; delivery photos and
  supplied reference PDF are stored in the repository
- continuity measurements verify `S` as the positive coil terminal, `-` as the
  other coil terminal, and `NC` as unused; coil resistance is 42.6 ohm
- the resulting approximately 77 mA 3.3 V DC upper bound requires a BC337-25
  low-side driver, flyback diode, and separate 3.3 V buzzer supply
- driver parts arrived and receipt validation verified the 470 ohm and 10 kOhm
  resistors, a forward/reverse diode response, and the 840-point breadboard's
  split-rail topology; photos and measurements are stored in the repository
- the AMS1117 headers were soldered and an isolated no-load test measured 5.03 V
  input and 3.36 V output; no ESP32 or buzzer was connected
- unpowered diode-mode and hFE tests verified the received transistor as NPN and
  confirmed its flat-face, leads-down order as collector, base, emitter
- the no-ESP32 breadboard driver passed unpowered short checks and static
  switching: 3.36 V collector when released and 56.2 mV when driven through the
  installed 470 ohm resistor; the buzzer remained silent under steady DC
- the buzzer `S` and `-` header joints and coil path were validated; the unused
  `NC` pin remains unsoldered
- ESP32 connection, PWM firmware, audible tone, and heating validation remain
  pending

Features:

- short beep
- alert tone
- silent mode
- notification queue

First-increment boundary:

- prove one short, non-blocking Select confirmation tone only
- retain a simple compile-time sound enable/disable constant
- do not add an alert tone or notification queue until the proof is validated

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

# Post-v1.0: Multi-Device HomeOS

This is a future roadmap direction, not a commitment or a pre-v1.0 scope change.
The v0.5 through v1.0 roadmap remains focused on a stable, useful single-device
HomeOS.

Potential future milestones may include:

- persistent device identity
- HomeOS service discovery
- peer approval and trust
- peer registry
- local P2P text messaging
- delivered acknowledgements
- heard acknowledgements
- optional SD storage
- asynchronous voice notes
- Telegram bridge
- device capability exchange
- offline and retry behavior

Exact post-v1.0 version numbers and delivery commitments are intentionally not
assigned yet.

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
