#ifndef HANDLERS_H
#define HANDLERS_H

#include <Adafruit_NeoPixel.h>
#include <Artnet.h> //needed for types
#include "config.h"

class Handlers
{
public:
  Handlers(int mode, Adafruit_NeoPixel *pixels);
  void setup();
  void pixel_mapping(uint8_t *data, uint16_t size);
  void fixture_channels(uint8_t *data, uint16_t size);
  int getMode();

private:
  Adafruit_NeoPixel *pixels;
  int output_mode;
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
  void mockFixture(uint8_t opacity, uint8_t animation, uint8_t animation_sub, uint8_t speed, uint8_t strobe)
  {
    sprintf(buf, "--opacity: %u", opacity);
    Serial.println(buf);

    sprintf(buf, "--animation: %u", animation);
    Serial.println(buf);

    sprintf(buf, "--animation_sub: %u", animation_sub);
    Serial.println(buf);

    sprintf(buf, "--speed: %u", speed);
    Serial.println(buf);

    sprintf(buf, "--strobe: %u", strobe);
    Serial.println(buf);
  }
};

#endif
