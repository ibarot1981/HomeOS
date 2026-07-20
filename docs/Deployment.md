# Deployment

## Development Deployment

During development, firmware is uploaded over USB.

Basic flow:

1. connect ESP32-S3 to computer using USB
2. build firmware
3. upload firmware
4. open serial monitor
5. observe logs
6. verify display behavior

## Preferred Tooling

Use PlatformIO when possible.

Benefits:

- clear project structure
- dependency management
- repeatable builds
- board configuration
- easier long-term maintenance

## Configuration

Local configuration should include:

- WiFi SSID
- WiFi password
- Telegram bot token
- Telegram chat ID
- timezone
- weather location
- API keys if needed

These should not be committed to public source control.

## OTA Updates

OTA means Over-The-Air update. It allows firmware updates over WiFi without plugging in USB.

OTA should not be part of the first bring-up. Add it after:

- display works
- WiFi is stable
- serial debugging is understood
- recovery by USB is known

OTA safety rule:

Always keep USB flashing available as a fallback.

## Versioning

Use semantic-ish milestone versions:

- `v0.1-display-hello`
- `v0.2-clock`
- `v0.3-buttons`
- `v0.4-module-manager`
- `v1.0-desk-dashboard`

Every version should have:

- working firmware
- known hardware wiring
- updated docs
- short release notes

## First Release Definition

Version 1.0 is ready when:

- device boots reliably
- display shows useful information
- buttons work
- slideshow/fixed/smart modes work
- buzzer works
- Telegram basics work
- WiFi reconnect is acceptable
- wiring is documented
- setup instructions are clear

## Recovery Plan

If a firmware update breaks the device:

1. connect USB
2. put board into bootloader mode if needed
3. upload last known good firmware
4. check serial logs
5. document what failed

