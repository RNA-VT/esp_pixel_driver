#ifndef HANDLERS_H
#define HANDLERS_H

#include <Adafruit_NeoPixel.h>
#include <Artnet.h> //needed for types
#include "config.h"
#include "util.h"

class PixelMappedOutput
{
public:
  PixelMappedOutput(Adafruit_NeoPixel *pixels);
  void subscriber(uint8_t *data, uint16_t size);

private:
  Adafruit_NeoPixel *pixels;
  void mock_output(int i, uint8_t r, uint8_t g, uint8_t b)
  {
    char buf[16]; //formatting buffer
    sprintf(buf, "Pixel ID: %u", i);
    Serial.println(buf);

    sprintf(buf, "~~Green: %u", g);
    Serial.println(buf);

    sprintf(buf, "~~Red: %u", r);
    Serial.println(buf);

    sprintf(buf, "~~Blue: %u", b);
    Serial.println(buf);
  }
};

#endif
