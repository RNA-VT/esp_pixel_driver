#ifndef ANIMATION_OPTIONS_H
#define ANIMATION_OPTIONS_H

struct RGB {
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

class AnimationOptions
{
public:
  unsigned char animation;
  unsigned char option;
  unsigned char opacity;
  unsigned char speed;
  unsigned char strobe;
  unsigned long scaleDelay(unsigned char maxDelay);
  RGB getSelectedColor();
};

#endif
