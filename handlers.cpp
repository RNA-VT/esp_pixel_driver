#include "handlers.h"
#include "config.h"
#include "util.h"

Handlers::Handlers(int mode)
{
  this->output_mode = mode;
  if (this->output_mode == OUTPUT_MODE_LED)
  {
    const byte numStrips = 1; // change for your setup
    this->pixels = Adafruit_NeoPixel(8, PIXEL_MAPPED_PIN, NEO_GRB + NEO_KHZ800)
  }
}

void Handlers::setup()
{
  if (this->output_mode == OUTPUT_MODE_LED)
  {
    this->pixels.begin();
  }
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
      this->pixels.setPixelColor(i, pixels.Color(r, g, b));
      break;
    case OUTPUT_MODE_MOCK:
      char buf[16]; //formatting buffer
      sprintf(buf, "Pixel ID: %u", i);
      Serial.println(buf);

      sprintf(buf, "~~Green: %u", g);
      Serial.println(buf);

      sprintf(buf, "~~Red: %u", r);
      Serial.println(buf);

      sprintf(buf, "~~Blue: %u", b);
      Serial.println(buf);
      break;
    }
  }
  if (this->output_mode == OUTPUT_MODE_LED)
  {
    this->pixels.show()
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

    uint8_t opacity = data[offset];
    uint8_t animation = data[offset + 1];
    uint8_t animation_sub = data[offset + 2];
    uint8_t speed = data[offset + 3];
    uint8_t strobe = data[offset + 4];

    switch (this->output_mode)
    {
    case OUTPUT_MODE_LED:
      //TODO: Add Animations
      break;
    case OUTPUT_MODE_MOCK:
      sprintf(buf, "--opacity: %u", opacity);
      Serial.println(buf);

      sprintf(buf, "--animation: %u", animation);
      Serial.println(buf);

      sprintf(buf, "--animation_sub: %u", animation_sub);
      Serial.println(buf);

      sprintf(buf, "--speed: %u", speed);
      Serial.println(buf);

      sprintf(buf, "--strobe: %u", strobe);
      Serial.println(buf);
      break;
    }
  }
}
