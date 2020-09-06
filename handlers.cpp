#include "handlers.h"
#include "config.h"

void Handlers::pixel_mapping(uint8_t *data, uint16_t size){
  const int pixels_per_channel = 3;
  const int offset = OFFSET_PIXEL_MAPPING + i * pixels_per_channel;
  for (int i=0; i< STRIP_LENGTH; i++ ) {
    //The order of the colors may vary by ArtNet source. 
    //We assume GRB here
    uint8_t g = data[ offset ];
    uint8_t r = data[ offset + 1 ];
    uint8_t b = data[ offset + 2 ]; 
    
    char buf[16]; //formatting buffer
    sprintf(buf, "Pixel ID: %u", i);
    Serial.println(buf);
    
    sprintf(buf, "Green: %u", g);
    Serial.println(buf);
    
    sprintf(buf, "Red: %u", r);
    Serial.println(buf);
    
    sprintf(buf, "Blue: %u", b);
    Serial.println(buf);
  }
}

void Handlers::fixture_channels(uint8_t *data, uint16_t size) {
  const int channels = 5;
  char buf[16]; //formatting buffer

  for (int i=0; i< FIXTURE_COUNT; ++i) {
    int offset = OFFSET_FIXTURE + channels * i;
    sprintf(buf, "Fixture ID: %u", i);
    Serial.println(buf);

    uint8_t opacity = data[offset];
    sprintf(buf, "opacity: %u", opacity);
    Serial.println(buf);

    uint8_t animation = data[offset + 1];
    sprintf(buf, "animation: %u", animation);
    Serial.println(buf);

    uint8_t animation_sub = data[offset + 2];
    sprintf(buf, "animation_sub: %u", animation_sub);
    Serial.println(buf);

    uint8_t speed = data[offset + 3];
    sprintf(buf, "speed: %u", speed);
    Serial.println(buf);

    uint8_t strobe = data[offset + 4];
    sprintf(buf, "strobe: %u", strobe);
    Serial.println(buf);
  }
}

