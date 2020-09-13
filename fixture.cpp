#include "fixture.h"

Fixture::Fixture(Adafruit_NeoPixel *pxls)
{
  pixels = pxls;
}

void Fixture::updateConfiguration(unsigned char opacity, unsigned char animation, unsigned char subselect, unsigned char speed, unsigned char strobe)
{
  AnimationOptions opts;
  opts.animation = animation;
  opts.option = subselect;
  opts.opacity = opacity;
  opts.speed = speed;
  opts.strobe = strobe;
  options = opts;

  pixels->setBrightness(opacity);
}

unsigned char Fixture::getOpacity()
{
  return options.opacity;
}

void Fixture::subscriber(unsigned char *data, unsigned short size)
{
  const int channels = 5;
  char buf[16]; //formatting buffer

  for (int i = 0; i < FIXTURE_COUNT; ++i)
  {
    int offset = OFFSET_FIXTURE + channels * i;
    sprintf(buf, "Fixture ID: %u", i);
    Serial.println(buf);

    //Parse Next Config Parameters
    unsigned char opacity = data[offset];
    unsigned char animation = data[offset + 1];
    unsigned char animation_sub = data[offset + 2];
    unsigned char speed = data[offset + 3];
    unsigned char strobe = data[offset + 4];

    updateConfiguration(opacity, animation, animation_sub, speed, strobe);
  }
}

void Fixture::run()
{
  switch (OUTPUT_MODE)
  {
  case OUTPUT_MODE_LED:
    switch (static_cast<Animation>(options.animation))
    {
    case fill:
      this->animations.Fill();
      break;
    case wipe:
      this->animations.Wipe();
      break;
    case rainbow:
      this->animations.HueModulation();
      break;
    case theater_chase:
      this->animations.TheaterChase();
      break;
    }
    break;
  case OUTPUT_MODE_MOCK:
    mock_output(options.opacity, options.animation, options.option, options.speed, options.strobe);
    break;
  }
}

void Fixture::mock_output(unsigned char opacity, unsigned char animation, unsigned char option, unsigned char speed, unsigned char strobe)
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
