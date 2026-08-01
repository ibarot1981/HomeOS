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

## Version 0.1 Board Serial Test

Goal:

- prove the ESP32-S3 board powers on and prints readable serial logs before connecting the display

First result:

- date: 2026-08-01
- connector used: `UART`
- Windows device: `USB-SERIAL CH340`
- Windows port during test: `COM7`
- baud rate: `115200`
- boot ROM line observed: `ESP-ROM:esp32s3-20210327`
- factory firmware observed: `EDGEHAX ESP32-S3 AUTO TEST`
- PSRAM detected: 8 MB (`8388608` bytes)
- LED blink test: passed

Notes:

- SD card mount failure is acceptable during this test because no SD card is part of Version 0.1.
- Factory WiFi failure is acceptable because the test firmware tries SSID `Edgehax`, not the future HomeOS WiFi setup.
- The next board test is the HomeOS PlatformIO environment `edgehax_s3_pro_diagnostics`, which prints flash size, PSRAM size, chip information, and a heartbeat over serial.

HomeOS PlatformIO result:

- date: 2026-08-01
- environment: `edgehax_s3_pro_diagnostics`
- build result: passed
- upload result: passed over `COM7`
- manual bootloader buttons required: no
- firmware flash size output: 16 MB (`16777216` bytes)
- firmware PSRAM output: 8 MB class
- heartbeat output: observed every 5 seconds

PlatformIO CLI commands, if `pio` is available in the terminal:

```powershell
pio run
pio run --target upload
pio device monitor
```

On this Windows PC, the PlatformIO extension may install the CLI without adding it to the normal terminal path. In that case, use the VS Code PlatformIO sidebar or run:

```powershell
& "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe" run
& "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe" run --target upload
& "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe" device monitor --port COM7 --baud 115200
```

In VS Code, the same actions are available from the PlatformIO sidebar as Build, Upload, and Monitor.

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
