#ifndef AIMATIONS_H
#define ANIMATIONS_H

#include "Adafruit_NeoPixel.h"
#include "animation_options.h"
#include "config.h"

/* 
  Animations - this class defines and house helper functions for all animations
*/

class Animations
{

public:
  Animations();
  Animations(Adafruit_NeoPixel *pixels, AnimationOptions *opts);
  void Fill();
  void Wipe();
  void ColorWheelCycles();
  void TheaterChase();

private:
  Adafruit_NeoPixel *pixels;
  AnimationOptions *options;
  void showAndDelay(unsigned char maxDelay)
  {
    if (pixels->canShow())
    {
      pixels->show();
    }
    delay(options->scaleDelay(maxDelay));
  };
  RGB getSelectedColor()
  {
    return options->getSelectedColor();
  }
};

enum Animation
{
  fill = 0,
  wipe = 1,
  rainbow = 2,
  theater_chase = 3
};

#endif
