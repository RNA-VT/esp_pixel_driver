# Esp Pixel Driver

Artnet LED Pixel Driver for the ESP8266 & ESP32 Microcontrollers.

<!-- markdownlint-disable MD001 -->

### Pixel Mapped Artnet Stream

<!-- markdownlint-enable MD001 -->

The pixel mapped artnet subscriber expects 3 channels of color data per pixel to be applied directly to particular leds.

| <-- Pixel Start Channel \
| `Red` | `Green` | `Blue` |

## Configuration

Set the following values in `config.h` before uploading to your microcontroller.

| Parameter        | Variable       | Default            | Options |
| ---------------- | -------------- | ------------------ |-|
| Output Mode      | OUTPUT_MODE    | OUTPUT_MODE_LED    | OUTPUT_MODE_LED, OUTPUT_MODE_MOCK |
| Output Pin       | OUTPUT_PIN     | 17                 | ESP GPIO Number |
| LED Strip Length | STRIP_LENGTH   | 250                | |
| Start Universe   | START_UNIVERSE | 1                  | |
| Start Channel    | CHANNEL_OFFSET | 0                  | |
| Serial Log Level | LOG_LEVEL      | LOG_LEVEL_STANDARD | LOG_LEVEL_STANDARD, LOG_LEVEL_DEBUG |

* Setting LOG_LEVEL to LOG_LEVEL_DEBUG may impact performance

---

### Secret Config

Create `secret.h` at the root of the repo. `#define` the following values:

| Parameter         | Variable  |
| ----------------- | --------- |
| Wifi Network SSID | WIFI_SSID |
| Wifi Password     | PASSWORD  |

---
