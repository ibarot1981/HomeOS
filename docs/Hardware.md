# Hardware

## Current Recommended Hardware

| Item | Preferred Choice | Status | Reason |
|---|---|---:|---|
| Microcontroller | Edgehax S3-PRO with ESP32-S3-WROOM-1 module marked MCN16R8 | Received - UART serial, PlatformIO upload, 16 MB flash, PSRAM, Version 0.2 clock-screen upload, and USB power-cycle recovery verified | native USB behavior, physical RESET behavior, and board pinout still must be verified |
| Display | Waveshare 4.2 inch black-and-white SPI ePaper module V2, Rev2.2, 400 x 300 | Received - full-refresh hello-world and Version 0.2 clock screen verified | ideal dashboard size; partial refresh and fast refresh behavior still must be tested |
| Breadboard | new 840-point solderless breadboard | Received - terminal strips and split power rails meter-verified on 2026-08-24 | adequate space for the Version 0.6 driver; each rail has independent upper/lower sections |
| Jumper wires | male-to-female 2.54 mm kit | Already owned - user confirmed | required for temporary wiring |
| Buttons | tactile switches | Version 0.3 verified on GPIO4, GPIO5, and GPIO6 | active-low prototype navigation on breadboard |
| Buzzer | SmartElex Passive Buzzer Module | Pinout independently continuity-verified on 2026-08-17; 42.6 ohm DC coil resistance measured | requires a low-side driver and flyback diode; do not connect it directly to GPIO |
| USB data cable | compatible with purchased ESP32-S3 board | Needed | must support both power and data for flashing |
| Power | branded USB phone charger | Already owned | suitable for deployment after firmware is loaded |
| Digital multimeter | basic digital multimeter | Recommended before hardware expansion | useful for voltage, continuity, and troubleshooting |
| Component storage/labels | small box or labels | Optional | helps identify starter-kit parts later |
| Buzzer/load driver parts | BC337-25, 470 ohm and 10 kOhm resistors, 1N5819 diode, 3.3 V LDO module, and decoupling capacitors | Received - core parts receipt-checked and key resistor/diode measurements recorded | isolates the ESP32 GPIO from the estimated 77 mA buzzer-coil current |

## Received Hardware Records

Received hardware evidence is stored in the repository:

- ESP32-S3 photos: `hardware/photos/ESP32 S3 Devkit/`
- Waveshare display photo: `hardware/photos/Waveshare 4.2-inch e-Ink Paper Display module with SPI Interface/`
- first wired display hello-world photos: `hardware/photos/ESP32 S3 Devkit/PXL_20260803_172005639_sm.jpg` and `hardware/photos/ESP32 S3 Devkit/PXL_20260803_172010729_sm.jpg`
- SmartElex passive-buzzer delivery photos: `hardware/photos/SmartElex Passive Buzzer Module/`
- Version 0.6 driver receipt photos: `hardware/photos/Version 0.6 Buzzer Driver Parts/`
- Version 0.6 driver receipt validation: `hardware/measurements/version-0.6-buzzer-driver-receipt-validation.md`
- Hardware reference documents: `hardware/datasheets/`

Do not store purchase invoices in the public repository. They can contain personal billing or shipping details.

## Controller Rationale

The recommended ESP32-S3 board is the ESP32-S3-WROOM-1-N16R8 variant.

The delivered board is marked:

- board: `Edgehax S3-PRO`
- module: `ESP32-S3-WROOM-1`
- module marking: `MCN16R8`
- seller/manufacturer marking on PCB: `Edgehax`
- USB connector labels visible on PCB: `UART` and `USB`
- button labels visible on PCB: `RESET` and `BOOT`

The module marking is consistent with the intended N16R8 class. The first UART serial monitor test on 2026-08-01 showed the board booting factory firmware and detecting 8 MB PSRAM. The first HomeOS PlatformIO diagnostic firmware uploaded successfully over `COM7` and printed 16 MB flash plus 8 MB-class PSRAM. Native USB behavior and usable GPIOs still need to be verified before depending on them.

Version 0.2 clock-screen firmware recovered correctly after a USB power-cycle on 2026-08-04. Pressing the physical `RESET` button did not appear to do anything obvious during that user test, so exact reset-button behavior remains to be investigated separately.

Reference documents:

- board pinout: `hardware/datasheets/edgehax-s3-pro-esp32-s3-wroom-n16r8-pinout.pdf`
- module datasheet: `hardware/datasheets/espressif-esp32-s3-wroom-1-wroom-1u-datasheet.pdf`
- Edgehax board repository: `https://github.com/edgehax/esp32-s3-wroom1-n16r8`

Name breakdown:

- `ESP32-S3`: modern ESP32 family with WiFi, Bluetooth LE, and strong processing capability
- `WROOM-1`: Espressif module family
- `N16`: 16 MB flash memory
- `R8`: 8 MB PSRAM

Why this matters:

- 16 MB flash gives room for firmware, fonts, icons, settings, and OTA updates.
- 8 MB PSRAM gives room for graphics buffers, JSON parsing, and future modules.
- Native USB improves programming and debugging.
- ESP32-S3 gives more long-term room than a basic ESP32-WROOM-32.

## Display Rationale

The preferred display is a 4.2 inch black-and-white SPI ePaper module with 400 x 300 resolution.

The delivered display PCB is marked:

- brand: `Waveshare`
- model marking: `4.2inch e-Paper Module`
- version marking: `V2`
- board revision: `Rev2.2`
- resolution marking: `400x300 Pixels`
- interface labels: `BUSY`, `RST`, `DC`, `CS`, `CLK`, `DIN`, `GND`, `VCC`
- interface selector marking: `BS`, with PCB table showing `1` for 3-line SPI and `0` for 4-line SPI

The first HomeOS display hello-world test on 2026-08-03 verified full refresh using GxEPD2 driver class `GxEPD2_420_GDEY042T81`, USB power through the ESP32 board, and 3V3 display power. The display controller is inferred from that working GxEPD2 class rather than directly read from a chip marking. Partial refresh, fast refresh, and long-term refresh behavior are still unverified.

Reference documents:

- downloaded display manual PDF: `hardware/datasheets/waveshare-4.2inch-epaper-module-manual.pdf`
- live Waveshare manual: `https://www.waveshare.com/wiki/4.2inch_e-Paper_Module_Manual`

Why 4.2 inch:

- enough room for useful layouts
- readable from a distance
- good for charts, QR codes, lists, and status screens
- still reasonably compact for a wall or desk

Why black-and-white:

- faster refresh than three-color ePaper
- better library support
- cleaner UI
- cheaper than larger color displays

Why SPI:

- common in ESP32 projects
- well supported by GxEPD2
- fewer wires than parallel displays
- practical for beginners

## Breadboard

A breadboard is a temporary construction board for circuits. It lets components and jumper wires be plugged in without soldering.

The received 840-point breadboard has adequate room for the Version 0.6 driver.
The user continuity-tested its terminal strips: `a10` to `e10` and `f10` to
`j10` are connected, while `e10` to `f10` and `a10` to `a11` are open.

Each of its four outer power rails is split in two. The first five visible
five-hole groups are continuous with each other; groups six through ten are also
continuous with each other; there is no continuity across that boundary. Use only
one tested rail section for any first circuit and never assume power crosses it.

## Buttons

Use three tactile switches:

- Previous
- Select
- Next

They are small but ideal for prototyping. Later, these can be replaced with nicer panel-mount buttons in an enclosure.

Version 0.3 assigns these buttons to `GPIO4`, `GPIO5`, and `GPIO6` using
active-low wiring with internal pull-ups. On 2026-08-06, the breadboard wiring,
navigation behavior, debounce, and serial press logs were verified using USB power.

## Buzzer

The delivered Version 0.6 candidate is a SmartElex Passive Buzzer Module. The
PCB is marked `SmartElex Passive Buzzer`, has a three-position header footprint,
and the observed silkscreen labels are `-`, `NC`, and `S`; see the delivery
photos in `hardware/photos/SmartElex Passive Buzzer Module/`.

The supplied reference `hardware/datasheets/SmartElex-Passive-Buzzer-Module.pdf`
describes a generic `VCC`, `GND`, `SIG / IN` interface, which does not match the
delivered PCB and is not used as the pinout source for this revision. The user
independently verified the actual electrical connections by continuity testing:

| Measurement | Actual result | Meaning |
|---|---:|---|
| PCB `-` to buzzer lead 1 | 0.2 ohm | direct connection |
| PCB `S` to buzzer lead 2 | 0.2 ohm | direct connection |
| PCB `NC` to either buzzer lead | O.L. | genuinely not connected |
| Between buzzer leads | 42.6 ohm | low-resistance magnetic coil |

Lead 2 is next to the buzzer's moulded `+` mark. Therefore `S` is the positive
coil terminal and `-` is the other coil terminal. `NC` is unused. At 3.3 V, the
simple DC upper-bound calculation is `3.3 V / 42.6 ohm = 77 mA`; it is far above
the current that this project will ask an ESP32 GPIO to supply. The module must
use a low-side transistor driver and a flyback diode.

The planned, not-yet-wired Version 0.6 circuit is a BC337-25 NPN low-side switch
on verified available PWM-capable `GPIO17`. Its base will use a 470 ohm series
resistor and 10 kOhm pull-down; a 1N5819 flyback diode will be fitted across the
coil. The Edgehax board documentation does not specify spare capacity on its
3.3 V rail, so the buzzer will receive 3.3 V from a separate AMS1117-3.3 LDO
module powered from the board's USB-derived 5 V rail. Grounds will be common,
but the LDO's 3.3 V output must never connect to the board's 3.3 V pin.

The received `HW-122` regulator board has visible `VIN`, `VOUT`, and `GND`
labels. Its supplied 1x4 header was cut into two 1x2 pieces for its separated
input and output hole pairs. The two headers were soldered and visually inspected
on 2026-08-26. With no ESP32 or buzzer connected, a USB-derived 5.03 V input
produced 3.36 V at `VOUT` relative to output `GND`; the module's red LED lit.
After the USB source was switched off, the LED remained lit for approximately
40 to 60 seconds. This is recorded as an unloaded observation, not a load or
thermal qualification. The complete driver, ESP32 connection, firmware control,
and buzzer validation remain untested.

## Power Supply

A good-quality USB phone charger is suitable for deployment.

Recommended:

- 5 V / 1 A minimum
- 5 V / 2 A preferred

Avoid very cheap or damaged chargers. The ESP32 board regulates USB 5 V down to 3.3 V for the chip.

During development, initially power the ESP32 from a computer USB port so firmware can be uploaded and serial logs can be viewed.

## Future Hardware

Possible future additions:

- ultrasonic or pressure-based water level sensor
- current or voltage sensing module for power outage monitoring
- DHT22, SHT31, or BME280 temperature/humidity sensor
- rain sensor
- vibration sensor for washing machine
- magnetic reed switch for fridge or door monitor
- relay module only after safety review
- larger breadboard
- 3D printed enclosure

## Recommended Before Hardware Expansion

A basic digital multimeter is not essential for the first USB/display test, but it is recommended before adding tank sensors, electricity monitoring, relays, or unfamiliar sensor modules. It is the most useful beginner electronics tool because it lets you check voltage, continuity, and basic wiring mistakes.
