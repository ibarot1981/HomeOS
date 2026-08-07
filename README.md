# HomeOS

HomeOS is an ESP32-S3 and 4.2 inch ePaper home dashboard project.

Current firmware lives in `firmware/src` and builds with PlatformIO. Project documentation, hardware notes, wiring, testing, and deployment instructions are in `docs/`.

Current milestone: Version 0.4 Module Manager.

Version 0.4 replaces direct screen selection with a small two-module registry:
Clock and Status. Previous and Next wrap through the registered modules, while
Select redraws the current module. Status keeps the existing board diagnostics.
The active-low GPIO4/GPIO5/GPIO6 wiring and 50 ms debounce are unchanged.

The verified ePaper setup remains full-refresh only. Partial refresh, fast refresh,
and long-press actions remain deferred.
