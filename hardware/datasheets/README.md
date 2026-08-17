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
