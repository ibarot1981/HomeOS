# Electronics Basics

This guide assumes strong computer knowledge but beginner electronics experience.

## Electricity as a Simple Mental Model

Think of electricity like water in pipes.

- Voltage is like pressure.
- Current is like flow.
- Resistance is like a narrow pipe limiting flow.

This model is not perfect, but it is useful at the beginning.

## Voltage

Voltage is the electrical pressure between two points.

Common project voltages:

- 5 V: USB power
- 3.3 V: ESP32 logic voltage
- 230 V AC: Indian mains electricity

For HomeOS, most low-voltage electronics run at 3.3 V or 5 V. Avoid mains electricity until the project is mature and proper safety steps are understood.

## Current

Current is the amount of electrical flow. It is measured in amps.

A phone charger rated 5 V / 2 A does not force 2 A into the ESP32. It means the charger can supply up to 2 A if the device asks for it.

## Ground

Ground, often written as `GND`, is the common reference point for the circuit.

If two modules communicate, they usually need a shared ground. For example, the ESP32 and ePaper display must share GND or the signal levels have no common reference.

## 3.3 V vs 5 V

The ESP32 chip uses 3.3 V logic. Many ESP32 development boards accept 5 V through USB because the board has a voltage regulator that converts 5 V to 3.3 V.

Important:

- Powering the ESP32 board through USB is fine.
- Connecting 5 V directly into an ESP32 GPIO pin can damage it.
- Use modules that are 3.3 V compatible, or have level shifting built in.

## GPIO

GPIO means General Purpose Input/Output.

A GPIO pin is a programmable pin on the ESP32. It can be used to:

- read a button
- control a buzzer
- send data to a display
- read a sensor

Some pins have special boot behavior, so pin selection matters.

## Digital Input

A digital input reads either HIGH or LOW.

Example:

- button not pressed: HIGH
- button pressed: LOW

This depends on wiring and pull-up/pull-down configuration.

## Digital Output

A digital output sends either HIGH or LOW.

Example:

- HIGH: turn buzzer signal on
- LOW: turn buzzer signal off

For a passive buzzer, the ESP32 changes the output rapidly to create sound.

## Pull-Up Resistor

A pull-up resistor keeps an input at a known HIGH state when nothing else is connected.

Without a pull-up or pull-down, a button input can float. A floating input may randomly read HIGH or LOW because it is sensitive to electrical noise.

The ESP32 has internal pull-up resistors that can often be enabled in software. This simplifies button wiring.

## Button Debouncing

Mechanical buttons do not switch cleanly from off to on. When pressed, the metal contacts may bounce for a few milliseconds.

To software, one press might look like several rapid presses.

Debouncing means ignoring the extra transitions and treating them as one press.

## SPI

SPI is a communication method used between chips and modules.

For the ePaper display, the ESP32 sends display data over SPI.

Common SPI pins:

- MOSI or DIN: data from ESP32 to display
- CLK or SCK: clock signal
- CS: chip select
- DC: data/command selection
- RST: reset
- BUSY: display tells ESP32 it is still working

The ePaper display is slower than the ESP32, so the BUSY pin is important.

## Breadboard Basics

A breadboard has hidden metal strips under the holes. Holes in the same row or rail are internally connected.

Before plugging expensive parts into a breadboard, verify the breadboard layout. Small breadboards can vary.

## Safety Rules

- Do not work with mains voltage for early versions.
- Disconnect power before changing wiring.
- Double-check 5 V and 3.3 V pins.
- Never connect 5 V directly to ESP32 GPIO.
- If something becomes hot, disconnect power immediately.
- Use a multimeter before guessing when power behavior is unclear.

## Debugging Mindset

Electronics debugging is often slower than software debugging because mistakes are physical.

Check in this order:

1. Is the board powered?
2. Is ground connected between modules?
3. Are the pins correct?
4. Is the code using the same pins as the wiring?
5. Is the module compatible with 3.3 V logic?
6. Does a minimal example work?

