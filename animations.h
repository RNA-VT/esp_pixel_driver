#ifndef AIMATIONS_H
#define ANIMATIONS_H

#include "Adafruit_NeoPixel.h"
#include "animation_options.h"

class Animations
{

public:
  Animations(Adafruit_NeoPixel *pixels, AnimationOptions *opts);
  void Fill();
  void Wipe();
  void HueModulation();
  void TheaterChase();

private:
  Adafruit_NeoPixel *pixels;
  AnimationOptions *options;
  void showAndDelay(unsigned char maxDelay){
    pixels->show();
    delay(options->scaleDelay(maxDelay));
  };
  unsigned int getSelectedColor(){
    RGB rgb = options->getSelectedColor();
    return pixels->Color(rgb.r, rgb.g, rgb.b);
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
