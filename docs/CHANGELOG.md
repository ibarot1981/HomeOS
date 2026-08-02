# Changelog

## Unreleased

### Added

- Added initial PlatformIO configuration for the Edgehax S3-PRO board diagnostics environment.
- Added first firmware diagnostic sketch that prints chip, flash, heap, and PSRAM information over serial.
- Added PR handoff instructions requiring a ready-to-paste pull request title and description whenever Codex asks the user to create a PR.
- Recorded received ESP32-S3 DevKit photos and Waveshare 4.2 inch ePaper display photo/reference PDF.
- Documented observed board/display markings for the delivered Edgehax S3-PRO and Waveshare 4.2 inch e-Paper Module V2 Rev2.2.
- Documented visible USB connector labels, BOOT/RESET buttons, and the display `BS` SPI interface selector marking.
- Recorded the first ESP32-S3 UART serial monitor result, including CH340 detection, readable boot logs, factory test output, and 8 MB PSRAM detection.

### Changed

- Updated hardware, project context, ESP32, display, and wiring notes from purchase planning status to received-hardware verification status.
- Updated microcontroller status after the first HomeOS PlatformIO upload verified UART serial, automatic upload, 16 MB flash, 8 MB-class PSRAM, and heartbeat serial output over `COM7`, while keeping native USB and GPIO mapping pending.

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
