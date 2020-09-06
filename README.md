# Esp Artnet Receiver Example

Example Wifi Artnet Receiver for the ESP 8266 Microcontroller

Receivers for 2 types of ArtNet/DMX data are demonstrated

- 3 Channel Pixel Mapped LED Data
- 5 Channel DMX Fixture Configuration

## Pixel Mapped Data

The pixel mapping receiver expects 3 channel (GRB) color data to be directly applied to particular pixel outputs

## Fixture Configuration

The fixture receiver expects 5 channels of data

- opacity
- animation
- animation subselect
- speed
- strobe

This example assumes you are broadcasting to 3 fixtures in the same universe with no offset between them.

## Usage

Set the following configuration values in config.h before uploading to your microcontroller

| Parameter                             | Variable                            | Description                                                                  |
|---------------------------------------|-------------------------------------|------------------------------------------------------------------------------|
| Pixel Mapping Universe Id | UNIVERSE_PIXEL_MAPPING | 1 |
| Pixel Mapping DMX Start Channel |OFFSET_PIXEL_MAPPING | 0 |
| Fixture Universe Id | UNIVERSE_FIXTURE | 2 |
| Fixture Mapping DMX Start Channel | OFFSET_FIXTURE | 0 |
| Wifi Network SSID | WIFI_SSID |  |
| Wifi Password | PASSWORD |  |

