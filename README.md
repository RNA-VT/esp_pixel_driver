# Esp Pixel Driver

Wifi Artnet Receiver for the ESP8266 Microcontroller

Receivers for 2 types of ArtNet/DMX data are available

- 3 Channel Pixel Mapped LED Data
- 5 Channel DMX Fixture Configuration

## Usage

Set the following values before uploading to your microcontroller.

### Led Configuration (config.h)

| Parameter        | Required           | Variable     | Default          |
| ---------------- | ------------------ | ------------ | ---------------- |
| Output Mode      | :heavy_check_mark: | OUTPUT_MODE  | OUTPUT_MODE_MOCK |
| LED Strip Length | :heavy_check_mark: | STRIP_LENGTH | 16               |
---

### Pixel Mapped Data Receiver

The pixel mapped data receiver expects 3 channel (GRB) color data to be directly applied to particular pixel outputs.

#### Receiver Configuration (config.h)

| Parameter                      | Required           | Variable                   | Default |
| ------------------------------ | ------------------ | -------------------------- | ------- |
| Pixel Mapped Output Enable     | :heavy_check_mark: | ENABLE_PIXEL_MAPPED_OUTPUT | false   |
| Pixel Mapped Output Pin        |                    | PIN_PIXEL_MAPPED_OUTPUT    | 13      |
| Pixel Mapped Universe Id       |                    | UNIVERSE_PIXEL_MAPPED      | 1       |
| Pixel Mapped DMX Start Channel |                    | OFFSET_PIXEL_MAPPED        | 0       |
---

### DMX Lighting Fixture

The lighting fixture expects 5 channels of data:

- opacity
- animation
- animation subselect
- speed
- strobe

#### Fixture Configuration (config.h)

| Parameter                 | Required           | Variable              | Default                                       |
| ------------------------- | ------------------ | --------------------- | --------------------------------------------- |
| Fixture Output Enable     | :heavy_check_mark: | ENABLE_FIXTURE_OUTPUT | false                                         |
| Fixture Output Pin        |                    | PIN_FIXTURE_OUTPUT    | 13                                            |
| Fixture Universe Id       |                    | UNIVERSE_FIXTURE      | 2                                             |
| Fixture DMX Start Channel |                    | OFFSET_FIXTURE        | 0                                             |
| Fixture Count             |                    | FIXTURE_COUNT         | 1                                             |
| Fixture Data Source       |                    | FIXTURE_SOURCE        | DATA_SOURCE_ARNET                             |
| Fixture Server            |                    | FIXTURE_SERVER        | "http://jsonplaceholder.typicode.com/users/1" |
---

### Secret Config

Create `secret.h` at the root of the repo. `#define` the following values:

| Parameter         | Variable  |
| ----------------- | --------- |
| Wifi Network SSID | WIFI_SSID |
| Wifi Password     | PASSWORD  |
---
