# Version 0.6 Buzzer Driver Receipt Validation

Date of user-performed checks: 2026-08-23 to 2026-08-27.

This record distinguishes received-item evidence and meter observations from
future powered-circuit and firmware validation.

## Receipt and visual evidence

| Item | Actual result | Status |
|---|---|---|
| AMS1117 module | PCB marked `HW-122`; input marked `VIN`/`GND`, output marked `VOUT`/`GND`; supplied 1x4 header cut into two 1x2 pieces | headers soldered and visually inspected on 2026-08-26 |
| NPN transistor | body marked `JCBC 33725 T20` | received; NPN type and physical pin order meter-verified on 2026-08-27 |
| 1N5819 diode pack | two axial, banded diodes; body marking visually consistent with the received pack | received; polarity meter-verified below |
| 470 ohm resistor | colour bands visually consistent with yellow-violet-brown-gold | received; value meter-verified below |
| 10 kOhm resistor | five bands visually consistent with brown-black-black-red-brown | received; value meter-verified below |
| 100 uF capacitor | sleeve marked 100 uF, 16 V, 105 C | received; polarized |
| 100 nF capacitor | disc marked `104`, with 50 V marking visible | received; non-polarized |
| Berg header strip | straight single-row male strip observed | received; spare header source |
| Breadboard | 840-point-style board; main terminal strips and four split rails checked | received; topology meter-verified below |
| Soldering equipment | 25 W iron, stand, and solder received; three-pin plug visible in later setup photo | user reports iron heats; no manufacturer/rating label observed |

## Meter results

All readings were obtained by the user with no powered driver circuit assembled.

| Test | Actual result | Interpretation |
|---|---:|---|
| 470 ohm resistor | 0.459 kOhm | 459 ohm, within +/-5% tolerance (446.5 to 493.5 ohm) |
| 10 kOhm resistor | 9.92 kOhm | within +/-1% tolerance (9.90 to 10.10 kOhm) |
| 1N5819, red probe anode and black probe cathode/banded end | 0.177 V | forward Schottky-diode response |
| Same diode, probes reversed | O.L. | reverse blocking response |
| Breadboard `a10` to `e10` | beep, 0.2 ohm | left five-hole terminal group connected |
| Breadboard `f10` to `j10` | beep, 0.2 ohm | right five-hole terminal group connected |
| Breadboard `e10` to `f10` | no beep, O.L. | centre channel isolates the groups |
| Breadboard `a10` to `a11` | no beep, O.L. | adjacent numbered rows are separate |
| Each of four power rails | first five visible five-hole groups continuous; groups six to ten continuous; no continuity across the boundary | treat every rail as two independent sections |

## Isolated regulator validation

The user tested the assembled regulator with no ESP32, buzzer, driver parts, or
load connected.

| Test | Actual result | Interpretation |
|---|---:|---|
| Unpowered `VIN` to input `GND` | no continuity beep | no persistent input short observed |
| Unpowered `VOUT` to output `GND` | no continuity beep | no persistent output short observed |
| USB-derived input | 5.03 V DC | suitable isolated input for this no-load test |
| `VOUT` to output `GND` with input applied | 3.36 V DC | regulator output is within the expected 3.3 V range |
| Regulator LED | red LED lit while input was applied; remained lit about 40 to 60 seconds after power-off | user observation; no load or thermal conclusion drawn |

## Transistor identification and pin-order validation

The received transistor was tested unpowered with its flat marked face toward
the user and its leads pointing down. In that viewing direction, the leads are
left collector, middle base, and right emitter.

| Test | Actual result | Interpretation |
|---|---:|---|
| Red probe on middle, black on left | 0.656 V | forward-biased base-to-collector junction |
| Red probe on middle, black on right | 0.658 V | forward-biased base-to-emitter junction |
| Red probe on left, black on middle | O.L. | reverse junction blocks |
| Red probe on right, black on middle | O.L. | reverse junction blocks |
| hFE socket: left to `C`, middle to `B`, right to `E` | 274 | clear higher-gain NPN orientation; not a datasheet-condition gain qualification |
| hFE socket with left/right swapped | 12 | reverse outer-lead orientation; not used |

The transistor was stabilized in separate breadboard rows and connected to the
meter's NPN hFE socket with jumper wires. No external power was applied.

## Still untested

- Complete low-side driver wiring.
- PWM tone generation, sound, heating, and firmware behavior.
