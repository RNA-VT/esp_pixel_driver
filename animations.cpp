#include "animations.h"

#include <Artnet.h>
#include <Adafruit_NeoPixel.h>

Animations::Animations(Adafruit_NeoPixel *pixels, AnimationOptions *opts)
{
  this->pixels = pixels;
  this->options = opts;
}

void Animations::Fill()
{
  //Fill sets all LEDs on this strip to a single color
  this->pixels->fill(getSelectedColor());
  showAndDelay(100);
}

void Animations::HueModulation()
{
  //Hue Modulation loops through the color wheel on each pixel
  //option specifies the number of loops through the color wheel
  for (unsigned char lap = 0; lap < options->option; ++lap)
  {
    for (long startHue = 0; startHue < 65536; startHue += 256)
    {
      for (int i = 0; i < pixels->numPixels(); i++)
      {
        int pixelHue = startHue + (i * 65536L / this->pixels->numPixels());
        pixels->setPixelColor(i, this->pixels->gamma32(this->pixels->ColorHSV(pixelHue)));
      }
      showAndDelay(100);
    }
  }
}

void Animations::TheaterChase()
{
  for (unsigned char lap = 0; lap < options->option; ++lap)
  {
    for (int b = 0; b < 3; b++)
    {
      pixels->clear();
      for (int c = b; c < pixels->numPixels(); c += 3)
      {
        pixels->setPixelColor(c, getSelectedColor());
      }
      showAndDelay(100);
    }
  }
}

void Animations::Wipe()
{
  for (int i = 0; i < pixels->numPixels(); ++i)
  {
    this->pixels->setPixelColor(i, getSelectedColor());
    showAndDelay(100);
  }
}