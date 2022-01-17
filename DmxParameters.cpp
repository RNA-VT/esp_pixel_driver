#include "DmxParameters.h"

DmxParameters::DmxParameters() {}

DmxParameters::DmxParameters(uint16_t universe, uint16_t length,
                             uint8_t sequence, uint8_t *data, CRGB *leds) {
  this->universe = universe;
  this->length = length;
  this->sequence = sequence;
  this->data = data;
  this->leds = leds;
}
