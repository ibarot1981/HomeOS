# Display

## Recommended Display

Use a 4.2 inch black-and-white SPI ePaper module with 400 x 300 resolution, preferably Waveshare-compatible.

Delivered display status:

- received: 2026-07-29
- brand marking: `Waveshare`
- model marking: `4.2inch e-Paper Module`
- version marking: `V2`
- board revision: `Rev2.2`
- resolution marking: `400x300 Pixels`
- interface selector marking: `BS`, with PCB table showing `1` for 3-line SPI and `0` for 4-line SPI
- repository photo: `hardware/photos/Waveshare 4.2-inch e-Ink Paper Display module with SPI Interface/PXL_20260729_154404151_sm.jpg`
- downloaded reference manual PDF: `hardware/datasheets/waveshare-4.2inch-epaper-module-manual.pdf`
- user-provided photo PDF: `hardware/photos/Waveshare 4.2-inch e-Ink Paper Display module with SPI Interface/Waveshare eink display.pdf`
- first hello-world photo: `hardware/photos/ESP32 S3 Devkit/PXL_20260803_172005639_sm.jpg`
- live vendor manual: `https://www.waveshare.com/wiki/4.2inch_e-Paper_Module_Manual`

This recommendation is for a complete driver module, not a bare ePaper panel. A complete module includes the small interface board needed to connect the panel to an ESP32-style controller. A bare panel is much harder to use and should not be selected for Version 1.

Expected pins:

- VCC
- GND
- DIN or MOSI
- CLK or SCK
- CS
- DC
- RST
- BUSY

## Why ePaper

ePaper is ideal for an always-on home dashboard because:

- it is readable in daylight
- it uses almost no power when the image is static
- it looks calm and premium
- it does not glow at night
- it keeps showing the last image even when power is removed

## ePaper Trade-Offs

ePaper is not like a phone screen.

Limitations:

- full refresh is slow
- partial refresh can leave ghosting if overused
- animation is not practical
- black-and-white design needs careful layout

This is fine for HomeOS because the content is informational, not animation-heavy.

## Full Refresh

A full refresh redraws the entire display. It may take several seconds and can flash black/white during refresh.

Use for:

- boot
- module changes
- major layout changes
- periodic cleanup after many partial updates

## Partial Refresh

Partial refresh may mean updating a smaller rectangular memory area, but the panel may still visibly flash depending on its revision and refresh waveform.

Use for:

- clock minutes
- small status changes
- alert badges
- progress changes

Do not depend on partial refresh for everything until the exact display revision has been tested. The first objective is reliable full refresh. Partial refresh optimization comes later.

## Fast Refresh

Some V2-style 4.2 inch displays support faster refresh modes. Fast refresh and partial refresh support must be verified on the actual delivered display, not assumed from size and resolution.

## Exact Display Identification

Before firmware implementation, record the exact display details:

- seller
- product link
- manufacturer or compatible brand
- board/module revision
- display controller or GxEPD2 driver class
- supply-voltage instructions
- logic-voltage compatibility
- vendor example used for first testing
- photograph of the front and back
- pin labels printed on the actual unit

Version 0.1 should first use the vendor's official example or a known matching GxEPD2 example. The goal is to prove the exact delivered module works before building HomeOS-specific UI code.

| Field | Value |
|---|---|
| Seller | Robu.in, based on user-provided purchase context |
| Product link | TBD until recorded |
| Manufacturer or compatible brand | Waveshare, observed on PCB |
| Board/module revision | V2, Rev2.2, observed on PCB |
| Display controller | SSD1683 inferred from the working GxEPD2 `GxEPD2_420_GDEY042T81` driver class; not directly read from a chip marking |
| GxEPD2 driver class | `GxEPD2_420_GDEY042T81`, verified by full-refresh hello-world test on 2026-08-03 |
| Supply-voltage instructions | Manual says V2.1 and later driver boards support 3.3 V and 5 V environments; first HomeOS test used 3V3 only |
| Logic-voltage compatibility | Verified with ESP32-S3 3.3 V GPIO during first hello-world test |
| Vendor example used for first testing | HomeOS minimal GxEPD2 hello-world sketch using the GxEPD2 matching 4.2 inch black-and-white driver class |
| Front photograph | `hardware/photos/ESP32 S3 Devkit/PXL_20260803_172005639_sm.jpg` |
| Back/interface photograph | `hardware/photos/Waveshare 4.2-inch e-Ink Paper Display module with SPI Interface/PXL_20260729_154404151_sm.jpg` |
| Wired setup photograph | `hardware/photos/ESP32 S3 Devkit/PXL_20260803_172010729_sm.jpg` |
| Downloaded reference manual PDF | `hardware/datasheets/waveshare-4.2inch-epaper-module-manual.pdf` |
| User-provided photo PDF | `hardware/photos/Waveshare 4.2-inch e-Ink Paper Display module with SPI Interface/Waveshare eink display.pdf` |
| Live vendor manual | `https://www.waveshare.com/wiki/4.2inch_e-Paper_Module_Manual` |
| Printed pin labels | `BUSY`, `RST`, `DC`, `CS`, `CLK`, `DIN`, `GND`, `VCC` |
| Interface selector | `BS` marking observed; first HomeOS test used the module in 4-line SPI mode |

## First Hello-World Result

On 2026-08-03, the delivered Waveshare 4.2 inch e-Paper Module V2 Rev2.2 successfully displayed the HomeOS hello-world screen over SPI from the Edgehax S3-PRO. The test used full refresh only, USB power through the ESP32 board, and 3V3 display power. The display showed:

```text
HomeOS
ePaper hello-world
Waveshare 4.2 V2 Rev2.2
```

Known limitations after this result:

- partial refresh is not tested
- fast refresh is not tested
- long-term refresh interval behavior is not tested
- the display controller is inferred from the working driver class, not from a readable controller marking

## Version 0.2 Clock Screen

Version 0.2 replaces the hello-world screen with a simple clock screen path while keeping the same verified display driver, wiring, and full-refresh behavior.

Expected clock screen behavior:

- header: `HomeOS Clock` and WiFi status
- main area: local IST time and date when NTP sync succeeds
- fallback area: setup or failure status when WiFi credentials are missing, WiFi connection fails, or NTP sync fails
- footer: clock status and `Full refresh only`

The firmware intentionally avoids partial refresh and fast refresh. The clock redraws by full refresh on minute changes after time sync. This is simple and testable, but long-term full-refresh interval behavior is still a Version 0.2 validation item.

First user-reported clock-screen result on 2026-08-04:

- build, upload, and monitor were run from VS Code
- local WiFi credentials were provided through ignored `firmware/include/config.local.h`
- the screen showed the digital clock
- top-right WiFi status showed `WiFi`
- footer showed NTP sync status and `Full refresh only`
- the original `IST via NTP` footer text was visually ambiguous on the ePaper font, so the firmware label was changed to `NTP synced`
- after a USB power-cycle, the clock display recovered with WiFi/NTP as before
- after waiting for the next full refresh, the displayed time was correct

## Version 0.3 Button Navigation

Version 0.3 keeps the same verified ePaper wiring and still uses full refresh
only. Button navigation redraws the whole screen after a navigation action:

- Previous and Next switch between the Clock screen and a small Board diagnostics screen.
- Select logs and redraws the active screen.
- Partial refresh and fast refresh remain untested and unused.

Button upload and display validation passed on 2026-08-06 after the physical
button wiring matched `docs/Wiring.md`; the Clock and Board screens both rendered
correctly after navigation.

## Library

Preferred library:

- GxEPD2

Reasons:

- popular in ESP32 projects
- supports many Waveshare-compatible ePaper displays
- has examples
- works with Adafruit GFX-style drawing

## Display Design Rules

- Keep screens readable at a glance.
- Avoid tiny text.
- Use strong contrast.
- Use icons only when they improve clarity.
- Do not redraw constantly.
- Prefer clear modules over crowded all-in-one screens.
- Design for 400 x 300 from the beginning.

## Display Risk

The display choice is more sensitive than the ESP32 choice. Boards that look similar can use different controller ICs.

Before buying or coding deeply, confirm:

- size: 4.2 inch
- resolution: 400 x 300
- colors: black and white
- interface: SPI
- complete module, not raw panel
- GxEPD2 support or Waveshare example support
