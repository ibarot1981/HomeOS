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
- local reference PDF: `hardware/photos/Waveshare 4.2-inch e-Ink Paper Display module with SPI Interface/Waveshare eink display.pdf`

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
| Display controller | TBD until verified from vendor documentation or first working example |
| GxEPD2 driver class | TBD until verified by example build and display test |
| Supply-voltage instructions | TBD until checked against vendor documentation for this revision |
| Logic-voltage compatibility | TBD until checked against vendor documentation for this revision |
| Vendor example used for first testing | TBD until first display bring-up |
| Front photograph | TBD - not present in current artifact set |
| Back/interface photograph | `hardware/photos/Waveshare 4.2-inch e-Ink Paper Display module with SPI Interface/PXL_20260729_154404151_sm.jpg` |
| Printed pin labels | `BUSY`, `RST`, `DC`, `CS`, `CLK`, `DIN`, `GND`, `VCC` |
| Interface selector | `BS` marking observed; verify 4-line SPI setting before first display test |

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
