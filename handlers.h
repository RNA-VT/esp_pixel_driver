#ifndef HANDLERS_H
#define HANDLERS_H

#define PIXEL_MAPPED_PIN D8

#include <Artnet.h> //needed for types
#include "config.h"
#include <Adafruit_NeoPixel.h>

class Handlers {
  public:
    Handlers(int mode);
    void setup();
    void pixel_mapping(uint8_t *data, uint16_t size);
    void fixture_channels(uint8_t *data, uint16_t size);
  private:
    Adafruit_NeoPixel pixels;
    int output_mode;
};

#endif
