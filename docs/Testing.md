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

## Pull Request Build Check

GitHub Actions runs the `Build firmware` check for every pull request targeting
`main` when firmware-related files, `platformio.ini`, or a workflow file changes.
It installs PlatformIO and runs `pio run` using the checked-in configuration.
This verifies that the firmware compiles without local WiFi credentials.

Documentation-only pull requests still run the workflow's changed-file check,
but skip the PlatformIO build successfully. GitHub Actions cannot upload to the
physical ESP32-S3 or validate the display, buttons, WiFi, or NTP; those remain
manual hardware checks.

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

First successful HomeOS display result:

- date: 2026-08-03
- environment: `edgehax_s3_pro_diagnostics`
- library: GxEPD2 `1.6.9`
- driver class: `GxEPD2_420_GDEY042T81`
- wiring: documented in `docs/Wiring.md`
- power: USB power through the ESP32-S3 board only; display VCC connected to ESP32 `3V3`
- build result: passed
- upload result: passed over `COM7`
- serial result: diagnostics printed 16 MB flash, 8 MB-class PSRAM, display pin map, and `Display refresh command complete`
- display result: HomeOS hello-world text appeared clearly on a white background
- setup photos: `hardware/photos/ESP32 S3 Devkit/PXL_20260803_172005639_sm.jpg` and `hardware/photos/ESP32 S3 Devkit/PXL_20260803_172010729_sm.jpg`

Checklist:

- firmware compiles: passed on 2026-08-03
- upload succeeds: passed on 2026-08-03
- serial monitor opens: passed on 2026-08-03
- display initializes: passed on 2026-08-03
- screen refreshes: passed on 2026-08-03
- text appears: passed on 2026-08-03

If it fails:

1. check power
2. check GND
3. check SPI pins
4. check BUSY pin
5. confirm display driver class in GxEPD2
6. run vendor example

Still untested:

- partial refresh
- fast refresh
- refresh behavior after long uptime
- display behavior from a standalone USB charger

## Version 0.2 Clock Screen Test

Goal:

- display shows a useful clock screen using WiFi and NTP while keeping serial diagnostics useful

Build result:

- date: 2026-08-04
- environment: `edgehax_s3_pro_diagnostics`
- build command: `& "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe" run`
- build result: passed
- firmware behavior without local WiFi credentials: compiled fallback path that displays `WiFi not configured`

First hardware result:

- date: 2026-08-04
- test method: user ran VS Code PlatformIO build, upload, and monitor
- local WiFi credentials: present only in ignored `firmware/include/config.local.h`
- display result: digital clock appeared on the ePaper display
- top-right status: `WiFi`
- footer status: NTP sync status and `Full refresh only`
- label follow-up: changed the synced status text from `IST via NTP` to `NTP synced` because the display font could make `IST` look like `1st`

Follow-up recovery result:

- date: 2026-08-04
- physical `RESET` button behavior: user reported pressing it did not appear to do anything obvious
- USB power-cycle result: passed
- after reconnecting USB power, WiFi/NTP behavior returned as before
- one-minute full-refresh update result: passed; after waiting for the screen refresh, the displayed time was correct

Before upload:

1. confirm the ePaper module is still wired exactly as documented in `docs/Wiring.md`
2. confirm USB power is only through the ESP32 board
3. confirm `firmware/include/config.local.h` exists only locally if testing real WiFi/NTP
4. confirm no WiFi SSID or password is staged for commit

Expected serial behavior:

- startup diagnostics still print chip, flash, heap, PSRAM, display pin map, WiFi credential status, timezone, and clock refresh interval
- WiFi SSID and password are not printed
- if credentials are configured, firmware logs WiFi connection status and NTP sync status
- heartbeat output continues after the first display refresh

Expected display behavior:

- without local credentials: fallback clock setup screen appears
- with valid local credentials and network access: clock screen shows IST time and date
- refresh remains full-screen only
- partial refresh and fast refresh remain untested

Still to validate later:

- behavior when WiFi is unavailable after credentials have been configured
- exact physical `RESET` button behavior on the Edgehax S3-PRO

## Version 0.3 Buttons and Navigation Test

Build result:

- build date: 2026-08-05
- environment: `edgehax_s3_pro_diagnostics`
- build command: `& "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe" run`
- build result: passed

Hardware test status:

- upload passed on 2026-08-06 over `COM7`
- serial diagnostics confirmed the Edgehax S3-PRO, 16 MB flash, and 8 MB PSRAM
- each button produced one serial press event per normal tested press; no false repeat was observed
- Previous reached the Board screen, Select redrew the active screen once, and Next returned to Clock
- WiFi connected, NTP synchronized, and the Clock screen remained functional after navigation

The Version 0.3 hardware test used USB power through the ESP32-S3 board only.

## Button Test

Goal:

- each button produces exactly one event per normal press and can navigate between
  the Version 0.3 screens

Checklist:

- internal pull-up, active-low behavior implemented
- serial log printed the button name once per tested press
- Previous changed from Clock to Board
- Next changed from Board to Clock
- Select logged and redrew the active screen once
- no repeated false presses were observed during normal testing
- Clock remained functional after button testing

Version 0.3 intentionally does not include long-press detection. Long press should
be added later when there is a real settings or mode action to attach to it.

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

## Version 0.4 Module Manager Build Test

Build result:

- build date: 2026-08-07
- environment: `edgehax_s3_pro_diagnostics`
- build command: `& "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe" run`
- build result: passed

Upload and hardware validation passed on 2026-08-07 over `COM7`:

- Clock appeared after boot; Next reached Status and Previous returned to Clock.
- Select redrew the active module, with the existing active-low button behavior.
- WiFi/NTP initially missed its startup connection window, then the existing
  five-minute retry succeeded and the Clock showed the current time.

## Clock Minute-Boundary Refresh Test

The Clock module must redraw on the next actual minute change after it becomes
active. Navigation time must not add an extra delay. This uses the rendered-minute
comparison only; it remains a full ePaper refresh and does not affect Status.

Manual check after upload:

- navigate to Clock shortly before a minute changes
- confirm the display refreshes when that minute changes, rather than about one
  minute after navigation

Build and upload passed on 2026-08-07 over `COM7`; the physical minute-boundary
result remains pending.

Manual smoke-test checklist for future regression testing:

- boot into Clock
- press Next to reach Status and confirm the existing board diagnostics render
- press Previous to return to Clock
- press Select on each module and confirm one full redraw
- confirm one serial button event per normal press

The test must use the existing active-low GPIO4/GPIO5/GPIO6 button wiring and USB
power through the ESP32 board only. It must not enable partial or fast refresh.

## Version 0.5 Display Modes Build Test

Build result:

- build date: 2026-08-08
- environment: `edgehax_s3_pro_diagnostics`
- build command: `& "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe" run`
- build result: passed

Version 0.5 uses the `kDisplayMode` firmware constant in
`firmware/src/main.cpp`. Change only that constant, rebuild, and upload before
testing each mode. The default checked-in value is `DisplayMode::kSlideshow`.
Do not commit local WiFi credentials or generated build output.

## Version 0.5 Hardware Validation

Use the existing active-low GPIO4/GPIO5/GPIO6 button wiring, verified ePaper
wiring, and USB power through the ESP32 board only. The feature uses full-screen
refresh only; do not enable partial or fast refresh during this validation.

### Shared Regression Checklist

- upload succeeds and serial monitor opens at 115200 baud
- Clock and Status both render with the configured mode in their footer
- Previous and Next each navigate once per normal press
- Select redraws the active module once
- Clock minute refresh and configured WiFi/NTP retry remain functional

### Slideshow Mode

Set `kDisplayMode` to `DisplayMode::kSlideshow`.

- boot into Clock
- wait 60 seconds and confirm one full refresh changes to Status
- wait another 60 seconds and confirm it returns to Clock
- press Previous or Next and confirm normal navigation still works
- after a manual navigation action, confirm the next automatic advance waits a
  fresh 60 seconds

### Fixed Mode

Set `kDisplayMode` to `DisplayMode::kFixed`.

- boot into Clock and wait longer than 60 seconds; confirm it remains Clock
- press Next; confirm Status becomes the pinned screen
- wait longer than 60 seconds; confirm Status remains visible
- press Previous; confirm Clock becomes the pinned screen
- press Select on each module; confirm a single full redraw

### Smart Mode

Set `kDisplayMode` to `DisplayMode::kSmart` and use valid local WiFi credentials.

- confirm a healthy WiFi/NTP startup remains on the manually selected module
- make WiFi/NTP unhealthy (for example, temporarily turn off the access point)
  and wait for the existing retry path to record an unsynced status
- confirm Status temporarily overrides the current module and serial logs
  `Smart alert started`
- confirm the Status override lasts about 15 seconds and then returns to the
  module that was visible before the alert
- keep the failure active and confirm it does not repeatedly override the screen
- restore WiFi/NTP, confirm a successful recovery, then repeat the failure and
  confirm a new Smart alert may occur

No buzzer, Telegram notification, sensor, relay, persistence, or additional
hardware is part of Version 0.5.

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
