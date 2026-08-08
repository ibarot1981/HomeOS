# HomeOS

HomeOS is an ESP32-S3 and 4.2 inch ePaper home dashboard project.

Current firmware lives in `firmware/src` and builds with PlatformIO. Project documentation, hardware notes, wiring, testing, and deployment instructions are in `docs/`.

Current milestone: Version 0.5 Display Modes.

Version 0.5 adds compile-time Slideshow, Fixed, and Smart display modes to the
small Clock/Status registry. Slideshow advances every 60 seconds; Fixed retains
the module selected with Previous or Next; Smart temporarily displays Status for
a configured WiFi/NTP failure and then returns to the previous module. Select
still redraws the current module. The active-low GPIO4/GPIO5/GPIO6 wiring and 50
ms debounce are unchanged.

The verified ePaper setup remains full-refresh only. Partial refresh, fast refresh,
and long-press actions remain deferred.
