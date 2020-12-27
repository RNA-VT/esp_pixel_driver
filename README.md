# Esp Pixel Driver

Artnet LED Pixel Driver for the ESP8266 & ESP32 Microcontrollers.

<!-- markdownlint-disable MD001 -->

### Pixel Mapped Artnet Stream

<!-- markdownlint-enable MD001 -->

The pixel mapped artnet subscriber expects 3 channels of color data per pixel to be applied directly to particular leds.

| <-- Pixel Start Channel \
| `Green` | `Red` | `Blue` |

## Configuration

Set the following values in `config.h` before uploading to your microcontroller.

| Parameter                      | Variable                   | Default          |
| ------------------------------ | -------------------------- | ---------------- |
| Output Mode                    | OUTPUT_MODE                | OUTPUT_MODE_LED  |
| LED Max Strip Length           | STRIP_LENGTH               | 25               |
| Pixel Mapped Output Enable     | ENABLE_PIXEL_MAPPED_OUTPUT | false            |
| Pixel Mapped Universe Id       | UNIVERSE_PIXEL_MAPPED      | 1                |
| Pixel Mapped DMX Start Channel | OFFSET_PIXEL_MAPPED        | 0                |

---

### Pins

Select your gpio outputs by uncommenting and setting the pointer `pixels_mapped` in `esp_pixel_driver.ino`.

---

### Secret Config

Create `secret.h` at the root of the repo. `#define` the following values:

| Parameter         | Variable  |
| ----------------- | --------- |
| Wifi Network SSID | WIFI_SSID |
| Wifi Password     | PASSWORD  |

---
