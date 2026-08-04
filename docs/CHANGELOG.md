# Changelog

## Unreleased

### Added

- Added initial PlatformIO configuration for the Edgehax S3-PRO board diagnostics environment.
- Added first firmware diagnostic sketch that prints chip, flash, heap, and PSRAM information over serial.
- Added PR handoff instructions requiring a ready-to-paste pull request title and description whenever Codex asks the user to create a PR.
- Added hardware reference documents for the Edgehax S3-PRO pinout, Espressif ESP32-S3-WROOM-1 module datasheet, and Waveshare 4.2 inch ePaper module manual PDF.
- Recorded received ESP32-S3 DevKit photos and Waveshare 4.2 inch ePaper display photo/reference PDF.
- Documented observed board/display markings for the delivered Edgehax S3-PRO and Waveshare 4.2 inch e-Paper Module V2 Rev2.2.
- Documented visible USB connector labels, BOOT/RESET buttons, and the display `BS` SPI interface selector marking.
- Recorded the first ESP32-S3 UART serial monitor result, including CH340 detection, readable boot logs, factory test output, and 8 MB PSRAM detection.
- Added minimal GxEPD2 display hello-world firmware for the Waveshare 4.2 inch ePaper module.
- Recorded first wired setup and display hello-world photos.
- Added Version 0.2 clock screen firmware path using WiFi, NTP, IST timezone, and full-refresh ePaper drawing.
- Added a non-secret firmware config example for local WiFi credentials.

### Changed

- Updated hardware, project context, ESP32, display, and wiring notes from purchase planning status to received-hardware verification status.
- Updated microcontroller status after the first HomeOS PlatformIO upload verified UART serial, automatic upload, 16 MB flash, 8 MB-class PSRAM, and heartbeat serial output over `COM7`, while keeping native USB and GPIO mapping pending.
- Kept the user-provided Waveshare photo PDF under `hardware/photos` and stored downloaded manuals under `hardware/datasheets`.
- Updated wiring, display, deployment, hardware, and testing documentation after the Waveshare display full-refresh hello-world test passed on 2026-08-03.
- Replaced the firmware's hello-world display path with a minimal Version 0.2 clock screen while keeping startup diagnostics and the verified ePaper wiring.
- Documented safe local WiFi credential handling with ignored `firmware/include/config.local.h`.

### Fixed

### Removed

---

## v0.1.0 - Initial Design Pack

### Added

- Initial HomeOS documentation
- Architecture
- Hardware
- ESP32
- Display
- UI
- Modules
- Wiring
- Coding Standards
- Testing
- Deployment
- ADRs
- Roadmap
- Electronics Basics
- Project Context
- Development Workflow

### Changed

- N/A

### Fixed

- N/A

### Known Limitations

- Hardware not yet purchased
- Wiring not yet finalized
- GPIO assignments intentionally left TBD
