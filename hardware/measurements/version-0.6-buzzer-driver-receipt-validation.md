# Version 0.6 Buzzer Driver Receipt Validation

Date of user-performed checks: 2026-08-23 to 2026-08-24.

This record distinguishes received-item evidence and meter observations from
future powered-circuit and firmware validation.

## Receipt and visual evidence

| Item | Actual result | Status |
|---|---|---|
| AMS1117 module | PCB marked `HW-122`; input marked `VIN`/`GND`, output marked `VOUT`/`GND`; supplied 1x4 header cut into two 1x2 pieces | received; unpowered, unsoldered |
| NPN transistor | body marked `JCHC 33725 T20` | received; BC337-25 grade visually consistent |
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

## Still untested

- Header solder joints and bridge inspection.
- AMS1117 output voltage with a 5 V input and no buzzer attached.
- Complete low-side driver wiring.
- PWM tone generation, sound, heating, and firmware behavior.
