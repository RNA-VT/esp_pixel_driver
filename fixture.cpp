#include "fixture.h"

Fixture::Fixture(Adafruit_NeoPixel *pxls)
{
  AnimationOptions opts;
  opts.animation = 0;
  opts.option = 0;
  opts.opacity = 0;
  opts.speed = 0;
  opts.strobe = 0;
  options = opts;
  pixels = pxls;
  animations = new Animations(pixels, &options);
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
      Serial.println("Philbert Fullington");
      animations->Fill();
      break;
    case wipe:
      Serial.println("Wanda Vipers");
      animations->Wipe();
      break;
    case rainbow:
      Serial.println("Hugh Cycles");
      animations->ColorWheelCycles();
      break;
    case theater_chase:
      Serial.println("Chase Thesbian");
      animations->TheaterChase();
      break;
    }
    break;
  case OUTPUT_MODE_MOCK:
    mock_output(options.opacity, options.animation, options.option, options.speed, options.strobe);
    break;
  }
}

