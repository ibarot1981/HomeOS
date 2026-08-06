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

## ADR-011: Prefer a Carrier PCB Before a Fully Custom ESP32-S3 Board

Date: 2026-08-06

Decision:

When HomeOS reaches a future hardware-freeze milestone, the first custom hardware
integration should be a carrier PCB that accepts the existing Edgehax S3-PRO
through headers and preserves the verified GPIO map:

- GPIO4: Previous button
- GPIO5: Select button
- GPIO6: Next button
- GPIO7 through GPIO12: Waveshare 4.2 inch ePaper

The project should not design a fully custom ESP32-S3 motherboard yet.

This decision records the preferred hardware direction, not an immediate roadmap
commitment. The project should continue through software and UI milestones before
freezing carrier PCB dimensions, button placement, or enclosure shape.

Reason:

The Edgehax S3-PRO has already verified UART upload, serial diagnostics, 16 MB
flash, 8 MB-class PSRAM, ePaper display output, button input, and USB-powered
operation. A carrier PCB improves serviceability and removes breadboard wiring
while keeping the known-good controller and firmware assumptions intact.

A fully custom ESP32-S3 board would add USB, boot, reset, power, RF layout, module
assembly, and manufacturing risks before the enclosure shape and product needs are
stable.

Alternatives considered:

- continue with breadboard wiring
- solder jumper wires directly into a permanent prototype
- design a fully custom ESP32-S3 motherboard now

Status:

Accepted
