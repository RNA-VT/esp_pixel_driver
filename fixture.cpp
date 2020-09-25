#include "fixture.h"
  
AnimationOptions opts;

Fixture::Fixture(Adafruit_NeoPixel pxls)
{
  opts.animation = 0;
  opts.option = 0;
  opts.opacity = 0;
  opts.speed = 0;
  opts.strobe = 0;
  animations = new Animations(pxls, opts);
}

void Fixture::updateConfiguration(AnimationOptions opts)
{
  options = opts;
  pixels.setBrightness(options.opacity);
}

void Fixture::updateConfiguration(unsigned char opacity, unsigned char animation, unsigned char subselect, unsigned char speed, unsigned char strobe)
{
  options.animation = animation;
  options.option = subselect;
  options.opacity = opacity;
  options.speed = speed;
  options.strobe = strobe;

  pixels.setBrightness(opacity);
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
    Serial.println("blergh");
    //updateConfiguration(opacity, animation, animation_sub, speed, strobe);
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

