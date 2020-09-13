#ifndef CONFIG_H
#define CONFIG_H

#include "util.h"

#define OUTPUT_MODE OUTPUT_MODE_LED
#define STRIP_LENGTH 16

// Pixel Mapped Output Configuration
#define ENABLE_PIXEL_MAPPED_OUTPUT false
#define PIN_PIXEL_MAPPED_OUTPUT 13 //D7 on the 8266MOD pkg
#define UNIVERSE_PIXEL_MAPPED 1 //DMX Universe to listen in
#define OFFSET_PIXEL_MAPPED 0 //DMX Start Channel

// Fixture Output Configuration
#define ENABLE_FIXTURE_OUTPUT false
#define PIN_FIXTURE_OUTPUT 13
#define UNIVERSE_FIXTURE 2 //DMX Universe to listen in
#define OFFSET_FIXTURE 0 //DMX Start Channel

#define PIN_FIXTURE_OUTPUT 13
#define FIXTURE_COUNT 1
#define FIXTURE_SOURCE DATA_SOURCE_ARNET
#define FIXTURE_SERVER "http://jsonplaceholder.typicode.com/users/1"


//Must define:
/*
#define WIFI_SSID "hfsjdkf"
#define PASSWORD "sdjfhdskjfn"
*/
#include "secret.h"

#endif
