#include "handlers.h"
#include "config.h"
#include "util.h"
#include <Adafruit_NeoPixel.h>

Handlers::Handlers(int mode, Adafruit_NeoPixel *pixels = NULL)
{

  this->output_mode = mode;
  if (this->output_mode == OUTPUT_MODE_LED)
  {
    const byte numStrips = 1; // change for your setup
    this->pixels = pixels;
  }
}

void Handlers::setup()
{
  if (this->output_mode == OUTPUT_MODE_LED)
  {
    this->pixels->begin();
  }
}

int Handlers::getMode()
{
  return this->output_mode;
}

void Handlers::pixel_mapping(uint8_t *data, uint16_t size)
{
  const int pixels_per_channel = 3;
  for (int i = 0; i < STRIP_LENGTH; i++)
  {
    int offset = OFFSET_PIXEL_MAPPING + i * pixels_per_channel;
    //The order of the colors may vary by ArtNet source.
    //We assume GRB here
    uint8_t g = data[offset];
    uint8_t r = data[offset + 1];
    uint8_t b = data[offset + 2];

    switch (this->output_mode)
    {
    case OUTPUT_MODE_LED:
      this->pixels->setPixelColor(i, this->pixels->Color(r, g, b));
      if (pixels->canShow())
      {
        pixels->show();
      }
      break;
    case OUTPUT_MODE_MOCK:
      mock_output(i, r, g, b);
      break;
    }
  }
}

void Handlers::fixture_channels(uint8_t *data, uint16_t size)
{
  const int channels = 5;
  char buf[16]; //formatting buffer

  for (int i = 0; i < FIXTURE_COUNT; ++i)
  {
    int offset = OFFSET_FIXTURE + channels * i;
    sprintf(buf, "Fixture ID: %u", i);
    Serial.println(buf);

    //Parse Next Config Parameters
    uint8_t opacity = data[offset];
    uint8_t animation = data[offset + 1];
    uint8_t animation_sub = data[offset + 2];
    uint8_t speed = data[offset + 3];
    uint8_t strobe = data[offset + 4];

    switch (this->output_mode)
    {
    case OUTPUT_MODE_LED:
      //TODO: Select animation using animation & animation_sub
      //TODO: Calculate current values based on speed, strobe & opacity
      //TODO: Loop through pixels and set current values
      //TODO: Show Pixels
      break;
    case OUTPUT_MODE_MOCK:
      mockFixture(opacity, animation, animation_sub, speed, strobe);
      break;
    }
  }
}
