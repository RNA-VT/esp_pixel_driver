#include "animation_options.h"

unsigned long AnimationOptions::scaleDelay(unsigned char maxDelay)
{
  return ((255 - this->speed) / 255) * maxDelay;
}

RGB AnimationOptions::getSelectedColor()
{
  RGB colors;

  colors.r = 0;
  colors.g = 0;
  colors.b = 0;

  switch (option)
  {
  case 0:
    //Black
    break;
  case 1:
    //Red
    colors.r = 255;
    break;
  case 2:
    //Green
    colors.g = 255;
    break;
  case 3:
    //Blue
    colors.b = 255;
    break;
  case 4:
    //Yellow
    colors.r = 255;
    colors.b = 255;
    break;
  case 5:
    //Purple
    colors.g = 255;
    colors.b = 255;
  default:
    //White
    colors.r = 255;
    colors.g = 255;
    colors.b = 255;
    break;
  }

  return colors;
}
