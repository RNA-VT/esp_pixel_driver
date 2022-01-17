#ifndef DMX_PARAMETERS_H
#define DMX_PARAMETERS_H

#include <Arduino.h>
#include "config.h"
#include <FastLED.h>

class DmxParameters {
public:
  uint16_t universe;
  uint16_t length;
  uint8_t sequence;
  uint8_t *data;
  CRGB *leds;
  DmxParameters(uint16_t universe, uint16_t length, uint8_t sequence,
                uint8_t *data, CRGB *leds);
  DmxParameters();
};

#endif