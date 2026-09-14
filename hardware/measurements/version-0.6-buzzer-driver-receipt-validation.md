# Version 0.6 Buzzer Driver Receipt Validation

Date of user-performed checks: 2026-08-23 to 2026-09-10.

This record distinguishes received-item evidence and meter observations from the
completed GPIO17 Select-tone proof and the bounded thermal/stability check.
Electrical PWM waveform capture remains a separate optional future diagnostic;
it is not a Version 0.6 acceptance gate.

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

## Breadboard driver and static switching validation

The user assembled the documented low-side driver on one continuity-verified
section of the breadboard. The test used the separate `HW-122` regulator supply;
no ESP32 was connected. The transistor occupied rows 30 to 32 as collector,
base, and emitter. A 470 ohm resistor connected the base to the temporary input
at row 25, a 10 kOhm resistor pulled the base to common ground, and the 1N5819
was fitted with its banded cathode at 3.3 V and its anode at the collector.
The 100 uF and 100 nF capacitors were fitted across the regulator output.

The buzzer header currently has its `S` and `-` pins soldered; its electrically
unused `NC` pin remains unsoldered. The coil measured 43.4 ohm through the
soldered header pins and 44.8 ohm through the installed breadboard path.

| Test | Actual result | Interpretation |
|---|---:|---|
| 10 kOhm pull-down in circuit | 9.79 kOhm | base pull-down path present |
| 470 ohm base resistor in circuit | 0.460 kOhm | base-drive resistor path present |
| Installed 1N5819, red at collector and black at 3.3 V | 0.178 V | forward path matches intended flyback orientation |
| Installed 1N5819, probes reversed | 1.390 V | assembled-network reading; no short conclusion drawn |
| Unpowered 3.3 V rail to GND, both probe directions | O.L. | no persistent rail short observed |
| Powered rail voltage with row 25 unconnected | 3.36 V | regulator remained at expected output under the assembled load |
| Buzzer with row 25 unconnected | silent | pull-down held the transistor in its default-off state |
| Collector to GND with row 25 temporarily connected to 3.3 V through 470 ohm | settled at 56.2 mV | transistor switched on and pulled the collector low |
| Buzzer during the same steady-DC test | no click, buzz, or tone observed | no acoustic result claimed; steady DC was not a PWM tone test |
| Collector to GND after removing the temporary drive | 3.36 V | transistor returned to its default-off state |

The temporary row-25-to-3.3 V jumper was removed after the test. The charger was
switched off and unplugged between wiring changes.

## ESP32 connection and GPIO17 PWM proof

The existing Edgehax button/ePaper breadboard was left intact. All four Edgehax
GND pins were already occupied, so the new driver used an electrically equivalent
branch from the existing Previous-button ground node: a jumper from free `B8`
beside the ground wire at `A8` to the verified lower driver ground rail nearest
column A. This joins the BC337 emitter, AMS1117 output GND, and 10 kOhm pull-down
to the Edgehax ground reference.

A female-to-male jumper connects Edgehax `GPIO17` to `E25`, the input side of the
installed 470 ohm base resistor. The Edgehax remained powered through its `UART`
computer USB connection; the separately validated USB charger powers AMS1117
`VIN`. The two 5 V rails are not joined, and the AMS1117 3.3 V output is not
joined to the Edgehax 3.3 V rail.

| Test | Actual result | Interpretation |
|---|---|---|
| AMS1117 output rail to Edgehax 3.3 V, continuity mode in both probe directions | no beep, O.L. | no direct output-to-ESP32-3.3 V connection observed before power-on |
| Charger on with Edgehax USB off for 10 seconds | AMS1117 LED on; buzzer silent; no heat or smell reported | driver remained default-off through the pull-down with the ESP32 unpowered |
| Firmware upload | PlatformIO upload over `COM8` succeeded; boot diagnostics, WiFi/NTP, ePaper, and buzzer configuration printed | GPIO17 proof firmware ran on the physical Edgehax board |
| First Select attempt from original firmware | silent; serial logged `LEDC is not initialized` | PWM channel required explicit initialization before the first asynchronous tone request |
| Corrected first Select attempt | short audible tone; normal ePaper redraw; serial logged `Button pressed`, `Select redraw`, and `Select tone : started`; no LEDC error | first-press PWM/acoustic proof passed |
| Two corrected repeat Select attempts | short audible tone, normal ePaper redraw, and matching serial logs each time | repeat Select-tone behavior passed for the observed presses |

The firmware now initializes LEDC channel 0 at startup before `tone()` is used.
After the proof, the AMS1117 charger was unplugged and its LED was confirmed dark.

## Bounded thermal and stability check

On 2026-09-10, the user first confirmed the separate charger unplugged, the
AMS1117 LED dark, and all meter/crocodile leads removed. With the Edgehax on its
existing computer USB, the user reported normal display and serial behavior. The
separate charger was then connected only to AMS1117 `VIN`; for the ten-second
baseline observation, the LED was on and there was no sound, smell, or instability.

The user confirmed ten counted Select presses after each display redraw had
settled. Each produced one short beep and a normal screen redraw. During an
uncounted attempt, presses spaced about three seconds apart could be missed while
the slideshow display was still refreshing; after the display settled and a
further ten seconds elapsed, the subsequent presses each produced a beep. This is
recorded as an observation of the existing synchronous display-refresh boundary,
not as a prolonged-tone or power-fault result.

After the bounded tone check, the charger was unplugged and the AMS1117 LED was
dark. The user then reported the buzzer, BC337, and AMS1117 cool with no abnormal
smell. Wiring was not changed; the two 5 V sources and the AMS1117/ESP32 3.3 V
rails remained separate throughout.

## Deferred and still untested

- Soldering and inspection of the mechanically useful but electrically unused
  buzzer `NC` header pin.
- Electrical PWM waveform capture at GPIO17 or the buzzer/collector circuit.
  On 2026-09-14, the user confirmed that no oscilloscope or logic analyzer is
  available and that purchasing one is outside this milestone's scope. The
  available digital multimeter cannot resolve a 2 kHz, 100 ms waveform. No
  waveform result is claimed; capture is deferred as an optional future
  diagnostic rather than a Version 0.6 release gate.
- Alert tone, silent-mode behavior, and any notification queue.
