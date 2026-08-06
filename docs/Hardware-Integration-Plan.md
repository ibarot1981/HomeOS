# Hardware Integration Plan

## Purpose

This document plans a serviceable HomeOS hardware integration around the current
verified parts:

- Edgehax S3-PRO ESP32-S3 board
- Waveshare 4.2 inch black-and-white SPI ePaper Module V2 Rev2.2
- three buttons: Previous, Select, and Next
- USB power only

This is not a plan for a fully custom ESP32-S3 motherboard, and it is not an
immediate hardware freeze. It records the preferred direction for a future
hardware milestone after the HomeOS UI, interaction model, and physical layout
needs are stable enough to commit to a board shape.

When that future milestone starts, the preferred hardware step should be a custom
carrier PCB that accepts the current Edgehax board through headers, removes
breadboard wiring, and preserves the verified GPIO map.

Out of scope for this stage:

- relays
- sensors
- mains wiring
- external power input
- battery charging
- custom ESP32 module layout
- antenna design

## Preserved GPIO Map

The carrier PCB must preserve the current verified firmware pin map:

| Function | GPIO |
|---|---:|
| Previous button | GPIO4 |
| Select button | GPIO5 |
| Next button | GPIO6 |
| ePaper BUSY | GPIO7 |
| ePaper DC | GPIO8 |
| ePaper RST | GPIO9 |
| ePaper CS | GPIO10 |
| ePaper DIN / MOSI | GPIO11 |
| ePaper CLK / SCK | GPIO12 |

Button behavior remains active-low:

- one side of each button connects to its GPIO
- the other side connects to GND
- firmware enables internal pull-ups
- not pressed means HIGH
- pressed means LOW

The display continues to use 3.3 V from the Edgehax board and common GND. USB
through the Edgehax board remains the only power source.

## Carrier PCB Versus Fully Custom ESP32 Board

Recommended eventual hardware step: build a carrier PCB before considering a
fully custom ESP32-S3 board.

| Topic | Custom carrier PCB for Edgehax S3-PRO | Fully custom ESP32-S3 motherboard |
|---|---|---|
| Risk | Low. Keeps the verified controller, USB upload path, PSRAM, flash, and current firmware assumptions. | High. Requires correct ESP32-S3 module layout, boot strapping, USB, power, RF clearance, flashing behavior, and manufacturing validation. |
| Learning value | Strong. Teaches PCB layout, connectors, mounting, silkscreen, and design-for-assembly without also debugging the ESP32 core design. | Strong but too broad for the next step. Many failures would be hard to separate from firmware, USB, or RF issues. |
| Serviceability | Good if the Edgehax board is socketed on female headers and can be replaced. | Lower unless the custom board is designed, assembled, and debugged very carefully. |
| Firmware impact | Minimal to none if the GPIO map is preserved. | Medium to high. Board target, USB mode, boot behavior, pin availability, and diagnostics may need revalidation. |
| Manufacturing complexity | Simple 2-layer PCB, mostly through-hole headers/connectors, optional button footprints. | More complex 4-layer or carefully designed 2-layer board, fine-pitch ESP32 module pads, USB-C circuitry, regulator, boot/reset circuit, and RF layout constraints. |
| First-batch cost | Lower. Bare PCBs plus hand assembly are practical. | Higher. Assembly is more likely needed, and early board revisions may be scrapped. |
| Debuggability | Good. If something fails, the Edgehax board can be removed and tested independently. | Harder. Power, USB, boot, firmware, soldering, and RF problems all live on one board. |
| Size optimization | Moderate. The carrier must fit the Edgehax board footprint. | Best long-term path for a thin polished product. |
| Long-term product polish | Good enough for a first enclosed HomeOS unit. | Better later, after the product shape and electronics needs are stable. |

Direction:

- Use a carrier PCB for the first enclosed HomeOS hardware integration when the
  project reaches the hardware-freeze milestone.
- Consider a fully custom ESP32-S3 board only after the carrier version is built,
  documented, used for a while, and its limitations are clear.

## Carrier PCB Concept

The carrier should be mostly passive and easy to inspect.

Recommended features:

- two female header rows for the Edgehax S3-PRO so the board is removable
- clear silkscreen labels for GPIO4 through GPIO12, 3V3, GND, USB side, and display side
- one 8-pin ePaper connector or header carrying VCC, GND, DIN, CLK, CS, DC, RST, and BUSY
- one 4-pin button connector or a small separate button daughterboard connection:
  GND, Previous, Select, Next
- test pads for 3V3, GND, GPIO4, GPIO5, GPIO6, and ePaper BUSY
- mounting holes tied to the enclosure design, not placed as an afterthought
- no voltage regulator, no USB-C connector, no charger circuit, and no load control
- optional unpopulated footprints for small button debounce capacitors only if they
  are marked `DNI` and left unused in the first build

Keep the first revision boring:

- 2-layer FR-4
- large traces
- generous clearances
- through-hole connectors where practical
- wide silkscreen labels
- no tiny components unless necessary

The carrier should not block the Edgehax USB connector used for firmware upload
and power. If both Edgehax USB-C connectors remain physically accessible, mark the
preferred connector on the enclosure and documentation.

## Mechanical Enclosure Concept

Recommended enclosure style: a shallow display-first desktop or wall-mountable
case with a removable rear cover.

Front:

- Waveshare 4.2 inch ePaper visible through a clean rectangular window
- three buttons below or to one side of the display:
  Previous, Select, Next
- small printed or embossed button icons are acceptable if they do not clutter the face

Internal layout:

- display mounted to front standoffs or a display tray
- carrier PCB mounted behind the display or offset behind the lower button area
- Edgehax board socketed on the carrier with USB-C facing a side or bottom opening
- button wiring kept short and strain-relieved
- display cable or wires routed away from button hardware and screw bosses

Rear:

- removable back plate with screws
- access to the Edgehax USB-C connector without opening the case
- optional keyhole slots or VESA-like small mounting holes for wall mounting
- ventilation slots are optional; avoid creating dust openings directly above the PCB

Serviceability goals:

- open the rear cover without removing the display
- unplug and replace the Edgehax board
- unplug and replace the display harness
- unplug and replace the button harness or button daughterboard
- visually inspect connector labels after opening the case

Material and fabrication:

- first enclosure: 3D printed PLA/PETG is suitable
- later enclosure: laser-cut acrylic front plus 3D printed rear shell, or injection
  molding only after the design is stable

The enclosure dimensions must be driven by real measurements. Do not design final
CAD from seller drawings alone.

## Connector and Wiring Strategy

Preferred strategy: reduce loose jumper wires, but keep modules replaceable.

### Edgehax Board to Carrier

- use female headers on the carrier
- plug the Edgehax board into the carrier as a removable module
- do not solder the Edgehax board permanently in the first carrier revision
- ensure the header footprint matches the exact delivered board spacing and pin count
- leave enough vertical clearance for USB-C cable insertion and removal

### Carrier to ePaper Display

Options, in order of preference after measuring the display:

1. Matching 2.54 mm header/socket arrangement if the Waveshare module exposes a
   stable 8-pin through-hole header position.
2. A keyed 8-pin cable harness from the carrier to the display module.
3. A labeled Dupont-style harness for the first prototype only.

The ePaper connector order on the carrier should match the display's printed order
where possible:

```text
VCC
GND
DIN
CLK
CS
DC
RST
BUSY
```

If the chosen physical connector uses the reverse order, the carrier silkscreen
must make that obvious. Do not depend on wire color.

### Carrier to Buttons

Two acceptable approaches:

1. Button daughterboard mounted behind the front panel.
2. Three panel-mount buttons wired to a 4-pin carrier connector.

Recommended first enclosed prototype: a small button daughterboard, because it
keeps spacing neat and makes the front panel easier to assemble repeatedly.

Button connector:

```text
GND
PREV
SELECT
NEXT
```

Use one common ground for all three buttons. Do not add 3V3 to the button harness
unless a future illuminated button design is explicitly approved.

### Power

- USB remains the only power source.
- The USB cable plugs into the Edgehax S3-PRO.
- The carrier receives 3V3 and GND from the Edgehax board only for display/buttons.
- Do not add a second USB connector to the carrier in the first revision.
- Do not add an external barrel jack, screw terminal, battery, charger, boost
  converter, relay, or mains connection.

## Measurements Still Needed

Record these in `hardware/measurements/` before carrier PCB layout or enclosure CAD:

- Edgehax S3-PRO board length, width, thickness
- Edgehax header row count, pitch, row spacing, and pin count
- exact position of both USB-C connector openings relative to board edges
- height of the tallest Edgehax component when plugged into female headers
- position of BOOT and RESET buttons, if they need enclosure access
- Waveshare display PCB length, width, thickness
- display active-area size and bezel offset from PCB edges
- display mounting-hole diameter and center-to-center spacing
- display header position and connector height
- total stack height from display front to rear of plugged-in Edgehax board
- preferred button diameter, cap height, travel, and panel cutout size
- minimum comfortable spacing between the three buttons
- desired viewing orientation: landscape or portrait
- desired case margin around the display
- USB cable plug dimensions for the chosen cable

Use calipers if available. If not, record ruler measurements clearly and mark them
as approximate.

## Photos Still Needed

Add clear photos before CAD or PCB layout:

- Edgehax board top side, straight-on, with a ruler in frame
- Edgehax board bottom side, straight-on, with a ruler in frame
- close-up of both Edgehax header rows and pin labels
- close-up of both USB-C connectors and surrounding clearance
- Waveshare display front, straight-on, with a ruler in frame
- Waveshare display rear, straight-on, with a ruler in frame
- close-up of Waveshare connector/header labels
- side view of the current wired stack showing height and cable bends
- current three-button breadboard setup, top view and side view
- any candidate button parts next to a ruler
- rough placement mockup of display, Edgehax board, and buttons on paper

Photos should avoid private information and should not include WiFi credentials,
purchase invoices, or personal documents in the background.

## Staged Prototype Plan

### Stage 1: Physical Layout Mockup

Goal: prove the product shape before PCB design.

Steps:

- place the display, Edgehax board, and three buttons on paper or cardboard
- choose landscape or portrait orientation
- mark USB access direction
- confirm button placement is comfortable
- photograph the mockup

Done when:

- the intended layout is clear enough to measure
- USB cable access is visible
- the display and buttons feel natural to use

### Stage 2: Carrier Pinout Schematic

Goal: capture only the known-good wiring.

Steps:

- create a schematic with Edgehax headers, ePaper connector, button connector,
  test pads, and mounting holes
- preserve GPIO4 through GPIO12 exactly
- include no sensors, relays, power regulator, battery circuit, or custom ESP32
- label all pins in human-readable names

Done when:

- schematic net names match `docs/Wiring.md`
- an electrical rules check passes
- the schematic can be reviewed against the breadboard wiring

### Stage 3: Carrier PCB Revision A

Goal: replace breadboard wiring with a passive carrier.

Steps:

- lay out a 2-layer PCB with generous spacing
- keep USB connector clearance open
- add clear silkscreen labels and mounting holes
- order a small bare-PCB batch
- hand solder headers/connectors

Done when:

- continuity checks pass before plugging in hardware
- no shorts are found between 3V3 and GND
- Edgehax board plugs in without mechanical stress
- display and buttons connect without crossed wires

### Stage 4: Firmware Revalidation on Carrier

Goal: prove the carrier did not change behavior.

Steps:

- power only through Edgehax USB
- upload existing firmware without changing GPIO assignments
- verify Clock screen
- verify Board screen
- verify Previous, Select, and Next button behavior
- verify USB power-cycle recovery

Done when:

- Version 0.3 behavior matches the breadboard result
- no firmware pin changes were required
- the carrier wiring is documented with photos

### Stage 5: Enclosure Prototype

Goal: make the device physically usable and serviceable.

Steps:

- build a 3D printed enclosure around the verified carrier stack
- check display alignment, button feel, USB access, and rear-cover access
- run the device for a normal desk/wall trial using USB power

Done when:

- display is square and readable through the front opening
- buttons are comfortable and do not bind
- USB cable plugs in cleanly
- rear cover opens without disturbing the display
- internal wiring is strain-relieved

### Stage 6: Small First Batch

Goal: make a few repeatable units after one carrier/enclosure works.

Steps:

- update PCB silkscreen and enclosure CAD from prototype lessons
- order 5 to 10 carrier PCBs
- assemble a small batch by hand or through low-volume PCBA
- verify every unit with the same checklist

Done when:

- each unit passes continuity checks, firmware upload, display refresh, button
  navigation, and USB power-cycle recovery
- assembly notes and known limitations are documented

## Manufacturing Options for a Small First Batch

For Revision A, prefer bare PCBs and hand assembly unless the connector count or
quantity makes assembly inconvenient.

| Option | Best use | Notes |
|---|---|---|
| Local hand-built perfboard or soldered proto board | one physical proof before PCB layout | Fast, cheap, but not mechanically polished. Useful only to confirm connector strategy. |
| Bare PCB from a prototype PCB service | first real carrier PCB | Good for 5 to 10 boards. Hand solder through-hole headers/connectors locally. |
| JLCPCB PCB or PCBA | low-cost prototype carrier and possible assembly | JLCPCB documents prototype-to-production PCBA, SMT/THT/mixed assembly, and starting from small board quantities. Good candidate if using their available parts library. |
| PCBWay PCB or PCBA | prototype or low-volume batch | PCBWay documents prototype, small-volume, and turn-key assembly services. Useful if part sourcing or assembly support is preferred. |
| Seeed Fusion PCB/PCBA | alternative prototype service | Worth quoting if shipping, price, or preferred workflow is better. |
| Local PCB assembler in India | small batch after the design is stable | May simplify communication, GST/import handling, and rework. Usually needs clean Gerbers, BOM, placement files, and assembly drawings. |
| 3D printing service or local printer | enclosure prototypes | Best for enclosure Revision A and B. Expect at least one mechanical revision. |

Manufacturing files expected later:

- Gerber files
- drill files
- BOM
- pick-and-place file if assembled by a service
- assembly drawing
- PCB render or annotated image
- enclosure STL or CAD export
- short test checklist for each assembled unit

Sources checked on 2026-08-06:

- JLCPCB PCB assembly: https://jlcpcb.com/pcb-assembly
- PCBWay PCB assembly: https://www.pcbway.com/pcb-assembly.html
- PCBWay low-volume PCB production: https://www.pcbway.com/low-volume-production.html
- Seeed Fusion PCB/PCBA FAQ: https://support.seeed.cc/portal/en/kb/fusion

Always generate fresh quotes before ordering. Prices, part availability, shipping,
and service rules change.

## Firmware Implications

Expected firmware impact for the carrier PCB: none.

The carrier should preserve:

- the current PlatformIO target
- current display driver
- current button logic
- current debounce behavior
- current active-low wiring
- current full-refresh display behavior
- current USB upload and power path through the Edgehax board

Firmware changes are only needed if the hardware plan changes one of these:

- GPIO assignment changes
- button electrical behavior changes from active-low to another scheme
- display connector pin order causes a different signal map
- reset or boot behavior needs enclosure-access handling
- future power management is added

For the first carrier revision, changing firmware to fit the PCB is the wrong
direction. The PCB should fit the verified firmware and wiring.

## Future Roadmap Milestone

### Carrier PCB and Enclosure Prototype

Goal: move HomeOS from breadboard wiring to a serviceable enclosed prototype
after the UI, interaction model, and physical layout needs are stable enough to
freeze, without changing the verified controller, display, buttons, GPIO map, or
USB-only power model.

Scheduling note:

- do not schedule this as Version 0.3.5
- continue through the software and UI milestones first
- freeze the carrier PCB only when the display layout, button placement, and
  enclosure shape are no longer changing frequently

Scope:

- custom passive carrier PCB for the Edgehax S3-PRO
- connectorized ePaper wiring
- connectorized or daughterboard-based three-button input
- 3D printed enclosure prototype
- USB access through the enclosure
- no sensors, relays, external power input, batteries, or mains wiring

Definition of done:

- measurements and required photos are stored under `hardware/measurements/` and
  `hardware/photos/`
- carrier schematic preserves GPIO4 through GPIO12 exactly
- carrier PCB passes continuity and short checks before hardware is plugged in
- existing firmware uploads without GPIO changes
- Clock and Board screens render correctly
- Previous, Select, and Next buttons behave as in Version 0.3
- USB power-cycle recovery still works
- enclosure holds the display, carrier, Edgehax board, and buttons without stress
- USB cable can be connected without opening the enclosure
- wiring, hardware, test, and enclosure notes are documented

Known limitations:

- fully custom ESP32-S3 motherboard remains deferred
- partial refresh and fast refresh remain separate display validation work
- enclosure aesthetics may need at least one more revision after daily use
