# Changelog

## Unreleased

### Added

- Added living Architecture, static Code Map, and self-contained interactive code-map documentation.
- Added the Version 0.4 built-in Clock and Status module registry, current-module
  state, and draw/update lifecycle. Status retains the existing board diagnostics.
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
- Recorded the first user-reported Version 0.2 clock-screen hardware result.
- Recorded Version 0.2 USB power-cycle recovery and one-minute clock refresh validation.
- Documented Version 0.3 active-low button wiring for Previous, Select, and Next on GPIO4, GPIO5, and GPIO6.
- Added Version 0.3 firmware support for debounced Previous, Select, and Next button presses.
- Recorded successful Version 0.3 upload and hardware validation over `COM7`, including serial press logs and Clock/Board navigation.
- Added a hardware integration plan for a serviceable carrier PCB and enclosure around the existing Edgehax S3-PRO, Waveshare 4.2 inch ePaper display, and three verified buttons.
- Added a future carrier PCB and enclosure prototype roadmap note, intentionally deferred until after UI and physical layout needs are stable.
- Added ADR-011 to prefer a carrier PCB before attempting a fully custom ESP32-S3 motherboard.
- Recorded Version 0.4 upload and hardware validation over `COM7`, including
  Clock/Status navigation, Select redraws, and WiFi/NTP retry recovery.

### Changed

- Replaced direct Clock/Board screen selection with Previous/Next module
  navigation and retained Select as a full redraw of the active module.
- Updated hardware, project context, ESP32, display, and wiring notes from purchase planning status to received-hardware verification status.
- Updated microcontroller status after the first HomeOS PlatformIO upload verified UART serial, automatic upload, 16 MB flash, 8 MB-class PSRAM, and heartbeat serial output over `COM7`, while keeping native USB and GPIO mapping pending.
- Kept the user-provided Waveshare photo PDF under `hardware/photos` and stored downloaded manuals under `hardware/datasheets`.
- Updated wiring, display, deployment, hardware, and testing documentation after the Waveshare display full-refresh hello-world test passed on 2026-08-03.
- Replaced the firmware's hello-world display path with a minimal Version 0.2 clock screen while keeping startup diagnostics and the verified ePaper wiring.
- Documented safe local WiFi credential handling with ignored `firmware/include/config.local.h`.
- Changed the synced clock footer from `IST via NTP` to `NTP synced` to avoid ambiguity on the ePaper font.
- Scoped Version 0.3 to debounced button presses and simple built-in screen navigation, with long press deferred.
- Added direct Clock/Board screen navigation while deferring the formal module manager to Version 0.4.
- Documented that the future carrier PCB hardware integration should preserve the verified GPIO4 through GPIO12 map and continue using USB as the only power source.

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
