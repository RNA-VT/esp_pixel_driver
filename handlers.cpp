#include "handlers.h"
#include "config.h"

void Handlers::pixel_mapping(uint8_t *data, uint16_t size){
  const int pixels_per_channel = 3;
  int pixels_received = size / pixels_per_channel;
  
  for (int i=0; i< pixels_received; i++ ) {
    //The order of the colors may vary by ArtNet source. 
    //We assume GRB here
    uint8_t r = data[i * pixels_per_channel + 1];
    uint8_t g = data[i * pixels_per_channel];
    uint8_t b = data[i * pixels_per_channel + 2]; 
    
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
  uint16_t fixtures = size/channels;
  char buf[16]; //formatting buffer

  for (int i=0; i< fixtures; ++i) {
    
    sprintf(buf, "Fixture ID: %u", i);
    Serial.println(buf);

    uint8_t opacity = data[i * channels];
    sprintf(buf, "opacity: %u", opacity);
    Serial.println(buf);

    uint8_t animation = data[i * channels + 1];
    sprintf(buf, "animation: %u", animation);
    Serial.println(buf);

    uint8_t animation_sub = data[i * channels + 2];
    sprintf(buf, "animation_sub: %u", animation_sub);
    Serial.println(buf);

    uint8_t speed = data[i * channels + 3];
    sprintf(buf, "speed: %u", speed);
    Serial.println(buf);

    uint8_t strobe = data[i * channels + 4];
    sprintf(buf, "strobe: %u", strobe);
    Serial.println(buf);
  }
}

