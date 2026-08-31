# Hardware Reference Documents

This folder stores public hardware manuals, datasheets, and pinout references used by HomeOS.

Do not store invoices, order confirmations, address labels, private emails, or other purchase records here.

## Current References

| File | Hardware | Source | Notes |
|---|---|---|---|
| `edgehax-s3-pro-esp32-s3-wroom-n16r8-pinout.pdf` | Edgehax S3-PRO ESP32-S3 DevKit | `https://edgehax.com/wp-content/uploads/2026/02/ESP32-S3-WROOM-N16R8-Pinout.pdf` | Board-level pinout reference from the Edgehax S3-PRO GitHub documentation. |
| `espressif-esp32-s3-wroom-1-wroom-1u-datasheet.pdf` | ESP32-S3-WROOM-1 module | `https://documentation.espressif.com/esp32-s3-wroom-1_wroom-1u_datasheet_en.pdf` | Official Espressif module datasheet. |
| `waveshare-4.2inch-epaper-module-manual.pdf` | Waveshare 4.2 inch ePaper Module | `https://m.media-amazon.com/images/I/A11RTM39fZL.pdf` | Downloadable PDF export of the Waveshare manual content. Keep the live Waveshare wiki as the current vendor source. |
| `SmartElex-Passive-Buzzer-Module.pdf` | SmartElex Passive Buzzer Module | supplied by the user with the delivered module | States 3.3 V to 5 V PWM use and a generic `VCC`/`GND`/`SIG` interface, but the received PCB is marked `-`/`NC`/`S`. User-performed continuity measurements, not this generic table, verified `S` as positive coil, `-` as the other coil terminal, and `NC` as unused. |
| `yageo-cfr-25jt-52-470r-specsheet.pdf` | Yageo CFR-25JT-52-470R resistor | Yageo product specification saved during pre-order review | 470 ohm, +/-5%, 0.25 W axial carbon-film resistor; a received sample measured 459 ohm. |
| `yageo-mfr-series-specsheet.pdf` | Yageo MFR-25FTF52-10K resistor | Yageo MFR series specification saved during pre-order review | 10 kOhm, +/-1%, 0.25 W axial metal-film resistor; a received sample measured 9.92 kOhm. |
| `mcc-1n5817-to-1n5819-datasheet.pdf` | MCC 1N5819 diode family | MCC product datasheet saved during pre-order review | 1N5819 is a 40 V, 1 A Schottky diode. The received diode showed 0.177 V forward and O.L. reverse in diode-test mode. |
| `rubycon-yxj-series-datasheet.pdf` | Rubycon YXJ electrolytic capacitor series | Rubycon series datasheet saved during pre-order review | Received capacitor marking is 100 uF, 16 V, 105 C; it is polarized. |
| `robu-ams1117-datasheet.pdf` | AMS1117 regulator IC family | Robu download saved during pre-order review | IC-family datasheet only; it does not prove the received `HW-122` module pinout. The observed PCB labels are the wiring source. |
| `robu-bc337-attachment.pdf` | BC337 / BC338 transistor family | Robu attachment saved during pre-order review | Use its TO-92 pin drawing with the physical package orientation. The received transistor is marked `JCBC 33725 T20`; the cart manufacturer identity is not independently verified. |
| `murata-gcm1555c1h220ja16-reference-sheet.pdf` | Murata GCM1555C1H220JA16J | Murata reference sheet saved during pre-order review | Complimentary 22 pF, 50 V, 0402 capacitor; unrelated to the Version 0.6 breadboard driver. |

## Online References

| Hardware | URL | Notes |
|---|---|---|
| Edgehax S3-PRO board repo | `https://github.com/edgehax/esp32-s3-wroom1-n16r8` | Source of the board pinout link and board images. |
| Waveshare 4.2 inch ePaper manual | `https://www.waveshare.com/wiki/4.2inch_e-Paper_Module_Manual` | Live vendor manual. Use this as the current vendor source before finalizing display wiring or driver selection. |

## Photo-Derived PDFs

The user-provided Waveshare photo PDF is stored with photos, not datasheets:

```text
hardware/photos/Waveshare 4.2-inch e-Ink Paper Display module with SPI Interface/Waveshare eink display.pdf
```
