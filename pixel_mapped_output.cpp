#include "pixel_mapped_output.h"

PixelMappedOutput::PixelMappedOutput(Adafruit_NeoPixel *pixels)
{
  this->pixels = pixels;
}

void PixelMappedOutput::subscriber(uint8_t *data, uint16_t size)
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

    switch (OUTPUT_MODE)
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
