# Modules

## Module Concept

A module is a self-contained screen or feature. It should own its own data and drawing logic, while using shared services for WiFi, time, display, storage, and notifications.

## Suggested Module Lifecycle

Each module should support:

- `begin`: initialize resources
- `update`: fetch or compute new data
- `draw`: render screen
- `onButton`: respond to local buttons
- `hasAlert`: tell HomeOS if it needs attention
- `onCommand`: respond to Telegram or serial commands

## Version 0.4 Implementation

Version 0.4 implements the smallest useful subset of the suggested lifecycle:
`name()`, `draw()`, and `update(now)`. The base `Module` class supplies a no-op
default `update`; `ClockModule` overrides it for the existing WiFi/NTP retry and
minute refresh, while `StatusModule` only draws board diagnostics.

The built-in registry contains Clock and Status. The active registry index is the
current-module state. Previous and Next wrap through this registry, and Select
redraws the active module. Future modules can be added to the registry without
rewriting the Arduino `loop()`. Button callbacks, alerts, commands, and plugins
remain out of scope.

## Core Modules

### Clock Module

Purpose:

- always useful default screen

Data:

- current time
- date
- next reminder or event

Version:

- early milestone

### Weather Module

Purpose:

- show current weather and rain probability

Data:

- temperature
- humidity
- rain chance
- daily summary

Future:

- severe weather alert
- umbrella reminder

### Todo Module

Purpose:

- family task list

Data:

- pending tasks
- completed tasks

Input:

- Telegram commands
- future web dashboard

### Reminder Module

Purpose:

- time-based alerts

Examples:

- medicine
- bill payment
- garbage day
- appointment

Alert:

- display popup
- buzzer
- Telegram notification

### Telegram Module

Purpose:

- remote control and notifications

Commands:

- `/status`
- `/module clock`
- `/module weather`
- `/mode slideshow`
- `/mode fixed`
- `/mode smart`
- `/todo add Buy milk`
- `/reminder add Medicine 8 PM`

Security:

- only accept commands from approved chat IDs

## Future Hardware Modules

### Water Tank Module

Purpose:

- show overhead tank level
- notify low level or overflow risk

Possible sensors:

- ultrasonic distance sensor
- pressure sensor
- float switches

Future outputs:

- motor status
- daily usage estimate
- leak detection

Safety:

- start with monitoring only
- do not control pump until confidence and safety design are mature

### Electricity Module

Purpose:

- detect and log power outages

Features:

- power failed notification
- power restored notification
- outage duration
- daily/monthly outage totals

Safety:

- never connect ESP32 directly to mains
- use safe isolated modules or indirect detection

### Indoor Environment Module

Purpose:

- show room temperature and humidity

Possible sensors:

- BME280
- SHT31
- DHT22

### Rain Monitor Module

Purpose:

- detect rain and remind to bring clothes inside

### Washing Machine Module

Purpose:

- detect vibration and notify when washing is complete

### Medicine Module

Purpose:

- reminders with button acknowledgement

## Module Priority

Recommended order:

1. Clock
2. Navigation
3. Weather
4. Telegram
5. Reminders
6. Water Tank
7. Electricity

## Version 0.3 Navigation Scope

Version 0.3 intentionally does not introduce the formal module lifecycle or
module registry. It uses direct built-in screen navigation between the existing
Clock screen and a small Board diagnostics screen so the physical buttons can be
proved before Version 0.4 adds the module manager.
