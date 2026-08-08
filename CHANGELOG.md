# Changelog

All notable HomeOS milestone changes are recorded here.

## Version 0.5 - 2026-08-08

### Added

- Slideshow display mode, with a 60-second firmware-configured interval.
- Fixed display mode, which retains the module selected by Previous or Next.
- Smart display mode, which temporarily shows Status for configured WiFi/NTP
  failure and returns to the module displayed before the alert.
- A small `Module::hasAlert()` lifecycle seam, currently implemented by Status.

### Changed

- Registered modules now receive their `update(now)` call every loop so Clock
  WiFi/NTP retry remains active during a Smart Status override.
- Clock and Status footers show the configured display mode.

### Validation

- PlatformIO build passed locally.
- Hardware validation remains pending for slideshow timing, fixed selection,
  Smart override, and return-to-previous-module behavior.
