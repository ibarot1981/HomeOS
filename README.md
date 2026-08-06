# HomeOS

HomeOS is an ESP32-S3 and 4.2 inch ePaper home dashboard project.

Current firmware lives in `firmware/src` and builds with PlatformIO. Project documentation, hardware notes, wiring, testing, and deployment instructions are in `docs/`.

Current milestone: Version 0.3 Buttons and Navigation.

Version 0.3 adds three active-low buttons using the ESP32-S3 internal pull-ups:
Previous on GPIO4, Select on GPIO5, and Next on GPIO6. Previous and Next switch
between the Clock and Board diagnostics screens, while Select redraws the active
screen. The wiring, upload, debounce behavior, and Clock/Board navigation were
verified on the Edgehax S3-PRO using USB power only.

The verified ePaper setup remains full-refresh only. Partial refresh, fast refresh,
long-press actions, and the formal module manager remain future work.
