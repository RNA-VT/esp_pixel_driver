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
  for (uint16_t i = 0; i < STRIP_LENGTH; ++i)
  {
    RGB c = getSelectedColor();
    uint32_t color = this->pixels->Color(c.r, c.g, c.b);
    this->pixels->setPixelColor(i, color);
  }
  showAndDelay(100);
}

void Animations::ColorWheelCycles()
{
  //Hue Modulation loops through the color wheel on each pixel
  //option specifies the number of loops through the color wheel
  for (unsigned char lap = 0; lap < options->option; ++lap)
  {
    for (long startHue = 0; startHue < 65536; startHue += 256)
    {
      for (int i = 0; i < STRIP_LENGTH; i++)
      {
        int pixelHue = startHue + (i * 65536L / STRIP_LENGTH);
        pixels->setPixelColor(i, pixels->gamma32(pixels->ColorHSV(pixelHue)));
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
      RGB c;
      for (int i = b; i < STRIP_LENGTH; i += 3)
      {
        c = getSelectedColor();
        this->pixels->setPixelColor(i, c.r, c.g, c.b);
      }
      showAndDelay(100);
    }
  }
}

void Animations::Wipe()
{
  RGB c;
  for (int i = 0; i < STRIP_LENGTH; ++i)
  {
    c = getSelectedColor();
    this->pixels->setPixelColor(i, c.r, c.g, c.b);
    showAndDelay(100);
  }
}
