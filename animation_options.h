#ifndef ANIMATION_OPTIONS_H
#define ANIMATION_OPTIONS_H

struct RGB {
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

/*
  AnimationOptions houses config parameters from an external source
*/
class AnimationOptions
{
public:
  unsigned char animation = 0;
  unsigned char option = 0;
  unsigned char opacity = 0;
  unsigned char speed = 0;
  unsigned char strobe = 0;
  unsigned long scaleDelay(unsigned char maxDelay);
  RGB getSelectedColor();
};

#endif
