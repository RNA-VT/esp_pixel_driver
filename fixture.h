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
  void updateConfiguration(AnimationOptions opts);
  void updateConfiguration(unsigned char opacity, unsigned char animation, unsigned char subselect, unsigned char speed, unsigned char strobe);
  void subscriber(unsigned char *data, unsigned short size);
  void run();

private:
  AnimationOptions options;
  Adafruit_NeoPixel *pixels = NULL;
  Animations *animations = NULL;

  void mock_output(unsigned char opacity, unsigned char animation, unsigned char option, unsigned char speed, unsigned char strobe)
  {

    char buf[16]; //formatting buffer
    sprintf(buf, "--opacity: %u", opacity);
    Serial.println(buf);

    sprintf(buf, "--animation: %u", animation);
    Serial.println(buf);

    sprintf(buf, "--animation_sub: %u", option);
    Serial.println(buf);

    sprintf(buf, "--speed: %u", speed);
    Serial.println(buf);

    sprintf(buf, "--strobe: %u", strobe);
    Serial.println(buf);
  }
};

#endif
