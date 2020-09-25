# Esp Pixel Driver

LED Pixel Driver for the ESP8266 Microcontroller

2 mode are available:

- 3 Channel Pixel Mapped LED Data
- 5 Channel DMX Fixture Configuration

Both may be enabled, but overlap in pins or DMX addresses will result in unpredictable behavoir.
<!-- markdownlint-disable MD001 -->
### Pixel Mapped Artnet Stream
<!-- markdownlint-enable MD001 -->
The pixel mapped artnet subscriber expects 3 channels of color data per pixel to be applied directly to particular leds.

### DMX Fixture

The DMX fixture expects 5 channels of data:

- opacity
- animation
- animation subselect
- speed
- strobe

## Configuration

Set the following values in `config.h` before uploading to your microcontroller.

### Global

| Parameter            | Variable     | Default          |
| -------------------- | ------------ | ---------------- |
| Output Mode          | OUTPUT_MODE  | OUTPUT_MODE_MOCK |
| LED Max Strip Length | STRIP_LENGTH | 16               |

---

### Pixel Mapped Receiver Configuration

| Parameter                      | Variable                   | Default |
| ------------------------------ | -------------------------- | ------- |
| Pixel Mapped Output Enable     | ENABLE_PIXEL_MAPPED_OUTPUT | false   |
| Pixel Mapped Universe Id       | UNIVERSE_PIXEL_MAPPED      | 1       |
| Pixel Mapped DMX Start Channel | OFFSET_PIXEL_MAPPED        | 0       |

---

### Fixture Receiver Configuration

| Parameter                 | Variable              | Default                                       |
| ------------------------- | --------------------- | --------------------------------------------- |
| Fixture Output Enable     | ENABLE_FIXTURE_OUTPUT | false                                         |
| Fixture Universe Id       | UNIVERSE_FIXTURE      | 2                                             |
| Fixture DMX Start Channel | OFFSET_FIXTURE        | 0                                             |
| Fixture Count             | FIXTURE_COUNT         | 1                                             |
| Fixture Data Source       | FIXTURE_SOURCE        | DATA_SOURCE_ARNET                             |
| Fixture Server            | FIXTURE_SERVER        | "http://jsonplaceholder.typicode.com/users/1" |

### Pins

Select your gpio outputs by uncommenting and setting the pointers `pixels_mapped` & `pixels_fixture` in `esp_pixel_driver.ino`.

---

### Secret Config

Create `secret.h` at the root of the repo. `#define` the following values:

| Parameter         | Variable  |
| ----------------- | --------- |
| Wifi Network SSID | WIFI_SSID |
| Wifi Password     | PASSWORD  |

---
