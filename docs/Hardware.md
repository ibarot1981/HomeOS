# Hardware

## Current Recommended Hardware

| Item | Preferred Choice | Status | Reason |
|---|---|---:|---|
| Microcontroller | Edgehax S3-PRO with ESP32-S3-WROOM-1 module marked MCN16R8 | Received - UART serial, PlatformIO upload, 16 MB flash, and PSRAM verified | native USB behavior and board pinout still must be verified |
| Display | Waveshare 4.2 inch black-and-white SPI ePaper module V2, Rev2.2, 400 x 300 | Received - verification pending | ideal dashboard size; exact driver and refresh behavior must be tested |
| Breadboard | existing 30-point breadboard | Already owned - suitability to be checked | may help with buttons and small components |
| Jumper wires | existing kit | Already owned | required for temporary wiring |
| Buttons | tactile switches | Already owned | good for prototype navigation |
| Buzzer | passive buzzer | Already owned - identify before connecting | type and current requirement must be checked |
| USB data cable | compatible with purchased ESP32-S3 board | Needed | must support both power and data for flashing |
| Power | branded USB phone charger | Already owned | suitable for deployment after firmware is loaded |
| Digital multimeter | basic digital multimeter | Recommended before hardware expansion | useful for voltage, continuity, and troubleshooting |
| Component storage/labels | small box or labels | Optional | helps identify starter-kit parts later |
| Buzzer/load driver parts | transistor, base/gate resistor, protection components | Buy only if required | needed if buzzer or other load exceeds safe GPIO drive |

## Received Hardware Records

Received hardware evidence is stored in the repository:

- ESP32-S3 photos: `hardware/photos/ESP32 S3 Devkit/`
- Waveshare display photo and local reference PDF: `hardware/photos/Waveshare 4.2-inch e-Ink Paper Display module with SPI Interface/`

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

The display driver class, controller IC, power requirements, and refresh behavior are still unverified. Version 0.1 should prove the vendor example or a known matching GxEPD2 example before HomeOS UI work begins.

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

The existing "30-point" breadboard may be usable, but its suitability should be checked before planning around it. "30-point" may be an informal or mistaken description, and small breadboards vary greatly.

A wide ESP32-S3 DevKit may not fit across the centre channel of a tiny breadboard. This is common with development boards because they are wider than simple chips.

The display can initially connect directly to the ESP32 using suitable female-to-female jumper wires, so the breadboard may not be required for Version 0.1. Buttons and small components can still use the small breadboard.

Before deciding whether to buy a larger breadboard, record a photo or dimensions of the existing breadboard and the purchased ESP32-S3 DevKit.

Later, a larger 400-point or 830-point breadboard may be useful when adding sensors.

## Buttons

Use three tactile switches:

- Previous
- Select
- Next

They are small but ideal for prototyping. Later, these can be replaced with nicer panel-mount buttons in an enclosure.

## Buzzer

Use the existing passive buzzer only after identifying it.

A passive buzzer is often like a tiny speaker: the ESP32 must generate a changing signal to produce sound. However, not all passive buzzers can safely be driven directly by an ESP32 GPIO pin.

Before connecting it, identify whether it is:

- a bare piezo buzzer
- a magnetic buzzer
- a buzzer module with extra components

Record its voltage and current requirement if printed or documented. A very small piezo element may be testable directly, but any uncertain or higher-current buzzer should use a transistor driver.

Do not connect the buzzer until it has been identified by photograph or part marking.

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
