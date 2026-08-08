# Architecture Decision Records

This file records important decisions and why they were made.

## ADR-001: Build HomeOS as a Modular Platform

Date: 2026-07-19

Decision:

Build a modular dashboard platform instead of a single-purpose Arduino sketch.

Reason:

The project is expected to grow over 3 to 6 months or more. A modular architecture allows weather, reminders, tank monitoring, electricity logging, Telegram, and future sensors to be added without rewriting the whole firmware.

Alternatives considered:

- single Arduino sketch
- separate standalone projects for each use case

Status:

Accepted

## ADR-002: Use ESP32-S3 N16R8 as Preferred Controller

Date: 2026-07-19

Decision:

Use ESP32-S3 DevKit with ESP32-S3-WROOM-1-N16R8 module.

Reason:

It provides WiFi, Bluetooth LE, 16 MB flash, 8 MB PSRAM, native USB, and enough headroom for graphics, OTA, Telegram, APIs, and future modules.

Alternatives considered:

- Arduino Uno R3
- ESP32-WROOM-32 38-pin DevKit
- ESP8266
- ESP32-C3

Status:

Accepted

## ADR-003: Use 4.2 Inch Black-and-White SPI ePaper

Date: 2026-07-19

Decision:

Use a 4.2 inch black-and-white SPI ePaper display with 400 x 300 resolution, preferably Waveshare-compatible.

Reason:

It offers enough space for useful dashboard screens while remaining affordable and well supported. Black-and-white refresh is faster and simpler than three-color ePaper.

Alternatives considered:

- 2.9 inch ePaper
- 3-color ePaper
- raw Nook display panel
- repurposed entire Nook device

Status:

Accepted for Version 1

## ADR-004: Do Not Use Nook Display for Version 1

Date: 2026-07-19

Decision:

Leave the spare Nook for Phase 2 exploration.

Reason:

Salvaging the raw ePaper panel would require identifying the panel, controller, voltages, waveform behavior, and connector details. This would distract from building a useful first dashboard.

Alternative:

Repurpose the entire Nook later if it still boots.

Status:

Accepted

## ADR-005: Prefer Buttons and Telegram Over Touch

Date: 2026-07-19

Decision:

Use three tactile buttons and Telegram commands for interaction.

Reason:

Touch ePaper is more expensive, harder to source, and does not feel as responsive due to ePaper refresh behavior. Buttons are cheap, reliable, and easier to learn with.

Status:

Accepted

## ADR-006: Documentation-First Project

Date: 2026-07-19

Decision:

Maintain Markdown documentation from the start.

Reason:

The project is long-term and educational. Documentation preserves decisions, wiring, concepts, and troubleshooting knowledge so future sessions do not depend on memory or a long chat transcript.

Status:

Accepted

## ADR-007: Use PlatformIO with the Arduino Framework

Date: 2026-07-19

Decision:

Use PlatformIO as the main development environment while retaining the Arduino framework and Arduino-compatible libraries.

Reason:

PlatformIO provides repeatable builds, dependency management, board configuration, and a maintainable repository structure, while the Arduino framework remains accessible for a beginner.

Status:

Accepted

## ADR-008: Implement the Architecture Incrementally

Date: 2026-07-19

Decision:

Treat the architecture diagram as a target structure. Introduce services, event handling, module interfaces, and other abstractions only when required by a roadmap milestone.

Reason:

Premature abstractions can make firmware harder to learn, test, and debug. Each milestone should leave behind working firmware.

Status:

Accepted

## ADR-009: Monitoring Before Control

Date: 2026-07-19

Decision:

Initial water, electricity, appliance, and environmental modules will be monitoring and notification systems only.

Reason:

Automatic pump, relay, or mains-powered equipment control introduces electrical and operational safety risks. Control features require separate isolation, failure-mode, manual override, and safety reviews.

Status:

Accepted

## ADR-010: No Direct Mains Connection

Date: 2026-07-19

Decision:

HomeOS GPIO pins and low-voltage circuits must never connect directly to Indian 230 V AC mains.

Reason:

Mains detection or control must use appropriately rated isolation hardware, enclosed terminals, fusing where necessary, and qualified electrical installation.

Status:

Accepted

## ADR-011: Protect Main with Pull Requests and a Targeted Firmware Build

Date: 2026-08-08

Decision:

Protect `main` by requiring pull requests, resolved conversations, and a
successful `Build firmware` check. Require zero approving reviews while HomeOS
has a single maintainer. Run the PlatformIO build only when firmware-related
files, `platformio.ini`, or workflow files change; documentation-only pull
requests skip that build successfully.

Reason:

This prevents accidental direct updates and compile regressions without making
one-maintainer work or documentation corrections unnecessarily slow. Hardware
validation remains local because a hosted runner cannot access the ESP32-S3 or
connected peripherals.

Alternatives considered:

- require one approving review
- run the PlatformIO build for every documentation-only pull request
- run a post-merge build on every push to `main`

Status:

Accepted

## ADR-012: Defer Multi-Device Communication Until After v1.0 While Preserving Architectural Seams

Date: 2026-08-08

Decision:

HomeOS remains a single-device platform through Version 1.0. Multi-device
discovery, messaging, pairing, voice-note exchange, delivery receipts, and
related networking will not be implemented before v1.0. Pre-v1.0 development
will avoid unnecessary coupling around device identity, messaging transports,
networking, storage, module boundaries, and hardware capabilities.

Reason:

The priority is to make one HomeOS device stable, useful, and maintainable before
introducing distributed-system complexity. Preserving small architectural seams
reduces future refactoring cost without prematurely implementing unused
frameworks.

Preferred future direction:

- local P2P on the same home Wi-Fi network
- mDNS/DNS-SD as the preferred discovery direction
- no mandatory central server
- an optional future server or broker only if requirements justify it
- asynchronous voice notes before considering live audio intercom

Status:

Accepted
