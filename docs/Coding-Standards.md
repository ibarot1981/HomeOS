# Coding Standards

## Goal

Code should be readable, modular, and easy to extend. The project should avoid becoming one long Arduino sketch.

## Framework

Preferred:

- PlatformIO
- Arduino framework
- C++

## File Organization

Suggested structure:

```text
firmware/src/
|
+-- main.cpp
+-- core/
+-- drivers/
+-- services/
+-- ui/
+-- modules/
```

## Naming

Use clear names.

Examples:

- `DisplayManager`
- `ButtonDriver`
- `BuzzerDriver`
- `ModuleManager`
- `ClockModule`
- `WeatherModule`
- `TelegramService`

Avoid vague names:

- `Helper`
- `Stuff`
- `Manager2`
- `newCode`

## Main Loop Rule

The main loop should stay small.

Good:

```cpp
void loop() {
  homeOS.tick();
}
```

Bad:

```cpp
void loop() {
  // hundreds of lines controlling everything
}
```

## Secrets

Do not hardcode secrets in committed source files.

Secrets include:

- WiFi password
- Telegram bot token
- Telegram chat ID
- API keys

Use a local ignored config file or provisioning flow.

## Logging

Use serial logging during development.

Logs should help answer:

- did WiFi connect?
- did time sync succeed?
- did the display initialize?
- which module is active?
- did an API call fail?

## Error Handling

Embedded projects fail in physical ways. Code should show useful fallback screens.

Examples:

- WiFi not connected
- time not synced
- weather unavailable
- display busy timeout
- Telegram failed

## Comments

Use comments to explain why something exists, especially around hardware behavior.

Avoid comments that repeat the obvious.

Good:

```cpp
// ePaper panels need a full refresh occasionally to reduce ghosting.
```

Less useful:

```cpp
// Set x to 5.
```

## Codex Task Style

When asking Codex to implement something, include:

- target milestone
- files to create or modify
- hardware assumptions
- expected behavior
- what should not be changed
- verification steps

Example:

```text
Implement Version 0.3 button navigation with a small direct button scanner.
Use internal pull-ups and active-low buttons.
Do not add Telegram yet.
Add serial logs for button press and screen change.
```
