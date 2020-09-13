#ifndef FIXTURE_H
#define FIXTURE_H

#include "Artnet.h"
#include "Adafruit_NeoPixel.h"
#include "animations.h"
#include "animation_options.h"
#include "config.h"

class Fixture
{
public:
  Fixture(Adafruit_NeoPixel *pxls);
  void updateConfiguration(unsigned char opacity, unsigned char animation, unsigned char subselect, unsigned char speed, unsigned char strobe);
  void subscriber(unsigned char *data, unsigned short size);
  void mock_output(unsigned char opacity, unsigned char animation, unsigned char subselect, unsigned char speed, unsigned char strobe);
  unsigned char getOpacity();
  void run();

private:
  Adafruit_NeoPixel *pixels;
  AnimationOptions options;
  Animations animations = Animations(pixels, &options);
};

#endif
