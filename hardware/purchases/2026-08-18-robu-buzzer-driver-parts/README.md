# Robu Version 0.6 Buzzer Driver Parts

Status: received and receipt-checked on 2026-08-23 and 2026-08-24. This folder
is the retained purchase-evidence record; it is no longer an ordered-but-not-
received record.

Captured cart subtotal: INR 599.48 before shipping or checkout adjustments.

This evidence set records the items visible in the live Robu cart before checkout.
It contains no account, address, payment, or order information. Supplier-reference
images remain here as purchase evidence; received-component photos and measurement
results are stored separately under `hardware/photos/Version 0.6 Buzzer Driver
Parts/` and `hardware/measurements/`.

## Review outcome

The core electrical parts match the documented Version 0.6 low-side driver:

- BC337-25 NPN transistor
- 470 ohm base resistor
- 10 kOhm base pull-down resistor
- 1N5819 flyback diode
- AMS1117 fixed 3.3 V supply module
- 100 uF electrolytic and 100 nF ceramic decoupling capacitors

The soldering iron, stand, rosin-core solder, and alligator leads are suitable
support items. The free 22 pF SMD capacitors are unrelated promotional items and
must not be substituted for the 100 nF through-hole capacitor.

## Items captured

| # | Cart item | Qty | Unit / line price | Version 0.6 use | Review |
|---|---|---:|---:|---|---|
| 1 | Double-ended alligator test leads, 10-piece pack | 1 | INR 66 / 66 | temporary testing | suitable |
| 2 | Yageo CFR-25JT-52-470R, 470 ohm, 0.25 W, 5% | 12 | INR 0.89 / 10.68 | GPIO-to-base resistor | exact requirement |
| 3 | Yageo MFR-25FTF52-10K, 10 kOhm, 0.25 W, 1% | 10 | INR 1.08 / 10.80 | base pull-down | exact requirement |
| 4 | MCC 1N5819-AP, 40 V, 1 A, DO-41 Schottky diode | 2 | INR 6 / 12 | flyback protection | exact requirement; spare included |
| 5 | Rubycon 16YXJ100M5X11, 100 uF, 16 V | 2 | INR 8 / 16 | 3.3 V rail bulk decoupling | suitable; polarized |
| 6 | AMS1117 3.3 V power-supply module | 1 | INR 16 / 16 | separate buzzer supply from USB 5 V | received; `VIN`, `VOUT`, and `GND` labels observed; output still unpowered/untested |
| 7 | Noel Super 25 W LED soldering iron | 1 | INR 129 / 129 | solder the supplied 2.54 mm header | suitable if received label states 220-240 V AC |
| 8 | C-4 soldering iron stand with sponge | 1 | INR 177 / 177 | hot-iron support and tip cleaning | suitable |
| 9 | listed onsemi BC33725TA, NPN, TO-92-3 LF | 2 | INR 13 / 26 | low-side switch | received; body marked `JCHC 33725 T20`; BC337-25 grade visually consistent |
| 10 | 100 nF, 50 V through-hole disc capacitor | 8 | INR 1.25 / 10 | local high-frequency decoupling | suitable; expect `104` marking |
| 11 | Murata GCM1555C1H220JA16J, 22 pF, 50 V, 0402 | 8 free | free | none | unrelated SMD promotion |
| 12 | 0.8 mm 60/40 tin-lead rosin-core solder, 14 g | 1 | INR 126 / 126 | header soldering | suitable; use ventilation and wash hands |

## Receipt outcome

The AMS1117 module arrived with one 1x4 male header. It was cut into two 1x2
pieces for the module's separate input and output pairs; no soldering has occurred.
The separately purchased Berg strip is also visibly a straight, single-row male
strip. Exact header pitch was not independently measured; it is visually
consistent with a 2.54 mm breadboard header and must be dry-fitted before a
critical connection.

The user confirmed and continuity-tested:

- a new 840-point breadboard, which provides adequate prototype space; its
  terminal rows behave as expected and each of its four power rails is split into
  upper and lower sections; and
- male-to-female jumper wires for the ESP32-S3-to-breadboard connections.

A desoldering pump or solder wick is optional but useful for a first soldering
attempt. It is not electrically required for the proof circuit. See
`pending-additions.md` for suitable Robu links.

## Evidence limitations

Robu's product bodies were blocked by its anti-bot page during this review. The
saved images are the product-reference images delivered to the live cart, not
photos of the actual units. Several are intentionally named `generic-reference`
because their visible value or package may not match the ordered part. Exact MPN,
markings, polarity, terminal labels, and transistor pin orientation were checked
only to the extent recorded in the receipt-validation record. The regulator output,
solder joints, complete driver wiring, firmware, and buzzer behavior remain
untested.
