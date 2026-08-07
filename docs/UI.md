# UI Guidelines

## UI Philosophy

HomeOS should feel like a small home appliance: calm, readable, useful, and reliable.

The UI should not try to imitate a phone. ePaper refreshes slowly, so screens should change thoughtfully.

## Screen Size

Target resolution:

```text
400 x 300 pixels
```

Design all first screens for this size.

## Common Layout

Suggested layout:

```text
+----------------------------------+
| Header: title, time, status      |
+----------------------------------+
|                                  |
| Module body                      |
|                                  |
| Main content                     |
|                                  |
+----------------------------------+
| Footer: mode, nav hints, alerts  |
+----------------------------------+
```

## Header

Header may show:

- current module name
- WiFi status
- current time
- alert indicator

## Footer

Footer may show:

- display mode
- navigation hints
- last update time

## Typography

Use a small set of font sizes:

- large: main value, such as time or tank percentage
- medium: headings and labels
- small: metadata and footer

Avoid using many fonts.

## Icons

Use icons for:

- weather
- WiFi
- alerts
- power
- water
- reminders

Icons should be black-and-white and readable at small sizes.

## Module Screen Examples

### Clock

```text
HomeOS                         WiFi

08:35 AM
Sunday, 19 July

Next: Dentist at 5:00 PM

Mode: Slideshow
```

### Weather

```text
Weather                        WiFi

31 C
Humidity 71%
Rain chance 20%

Evening: Light rain possible
Updated 08:20 AM
```

### Water Tank

```text
Water Tank                     WiFi

82%
[################----]

Motor: OFF
Today usage: 320 L
```

### Electricity

```text
Power                          WiFi

Status: ON
Outages today: 3
Last outage: 17 min
Monthly outage: 7h 48m
```

## Interaction Model

Three buttons:

- Previous: go to previous module
- Select: choose or toggle
- Next: go to next module

Long press Select:

- open settings or switch mode

Version 0.3 starts with the same physical model but a smaller firmware behavior:
Previous and Next cycle between built-in screens, while Select logs and redraws
the active screen. Long press is deferred until settings or display modes exist.

Version 0.4 names those built-in screens Clock and Status modules. Previous and
Next wrap through the two-module registry; Select still performs a full redraw of
the active module. Status presents the board diagnostics. This does not add menus
or settings.

Telegram can provide richer remote control:

- `/module weather`
- `/mode slideshow`
- `/mode fixed`
- `/status`

## Alert Behavior

Alerts should be visible but not annoying.

Examples:

- tank low
- reminder due
- rain expected
- power failed

Alert screen behavior:

1. show alert module
2. beep if sound is enabled
3. send Telegram notification if configured
4. return to previous screen after configured time

## ePaper-Specific UI Rules

- Avoid frequent full-screen changes.
- Use partial updates only for small areas when tested.
- Do not animate.
- Avoid dense dashboards with too many tiny values.
- Prefer one strong main idea per module.
