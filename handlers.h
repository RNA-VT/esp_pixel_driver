#ifndef HANDLERS_H
#define HANDLERS_H

#include <Artnet.h> //needed for types
#include "config.h"

class Handlers {
  public:
    void pixel_mapping(uint8_t *data, uint16_t size);
    void fixture_channels(uint8_t *data, uint16_t size);
  private:
    OctoWS2811 leds;
};

#endif
