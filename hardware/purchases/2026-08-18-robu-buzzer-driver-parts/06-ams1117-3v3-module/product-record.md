# AMS1117 3.3 V power-supply module

- Cart quantity: 1
- Listing: fixed 3.3 V AMS1117 low-dropout regulator module
- Intended input: ESP32-S3 board 5 V pin while the board is USB-powered
- Intended output load: buzzer circuit only; do not join to the board 3.3 V rail
- Regulator family rating: up to 1 A under adequate thermal conditions
- Purpose: keep the measured buzzer-coil load off the board's undocumented 3.3 V rail
- Product page: https://robu.in/product/ams1117-3-3v-power-supply-module/
- Saved datasheet: `hardware/datasheets/robu-ams1117-datasheet.pdf` (regulator IC family, not a module pinout)
- Saved image: `robu-reference.jpg`
- Receipt result: the delivered board is marked `HW-122`; `VIN`, `VOUT`, and
  `GND` labels are visible on the front, and a 1x4 header was supplied. It was
  cut into two 1x2 pieces but has not been soldered.
- Remaining check: power from 5 V with no buzzer attached and meter-confirm about
  3.3 V output before connecting the ESP32 GPIO or buzzer
- Limitation: the listing evidence does not establish the delivered module's exact
  terminal order or manufacturer of the fitted regulator IC
