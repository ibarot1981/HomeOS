# Testing

## Testing Philosophy

HomeOS testing must cover both software behavior and physical hardware behavior.

Unlike pure software, a firmware bug might be:

- wrong code
- wrong wire
- wrong pin mapping
- bad power
- unsupported display revision
- loose breadboard connection

Testing should isolate one variable at a time.

## Version 0.1 Display Test

Goal:

- display shows a known message

Checklist:

- firmware compiles
- upload succeeds
- serial monitor opens
- display initializes
- screen refreshes
- text appears

If it fails:

1. check power
2. check GND
3. check SPI pins
4. check BUSY pin
5. confirm display driver class in GxEPD2
6. run vendor example

## Button Test

Goal:

- each button produces exactly one event per press

Checklist:

- not pressed reads HIGH
- pressed reads LOW
- serial log prints button name
- long press is detected
- repeated false presses do not occur

## Buzzer Test

Goal:

- passive buzzer produces sound

Checklist:

- short beep works
- alert tone works
- silent mode works
- buzzer does not heat

## WiFi Test

Goal:

- ESP32 connects reliably

Checklist:

- correct SSID
- correct password
- reconnect after router restart
- useful error display if unavailable

## Time Sync Test

Goal:

- correct date and time in local timezone

Checklist:

- NTP sync succeeds
- timezone is IST
- display shows correct date
- restart keeps behavior sane

## Module Manager Test

Goal:

- modules can be switched without rewriting main loop

Checklist:

- Clock module loads
- Status module loads
- Next button changes module
- Previous button changes module
- current module draws correctly

## Smart Mode Test

Goal:

- alert modules temporarily override normal display

Checklist:

- simulated alert switches screen
- buzzer sounds if enabled
- Telegram notification sends if enabled
- display returns to previous module

## Regression Tests

Before declaring a milestone complete:

- compile cleanly
- boot device
- verify display
- verify buttons
- verify serial logs
- update docs
- record known limitations

## Hardware Troubleshooting Notes

When something does not work, avoid changing many things at once.

Good debugging:

- change one wire
- test
- change one setting
- test

Bad debugging:

- change pins, library, board type, and wiring all at once

