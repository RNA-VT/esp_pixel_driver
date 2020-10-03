#ifndef CONFIG_H
#define CONFIG_H

#include "util.h"

#define OUTPUT_MODE OUTPUT_MODE_LED
#define STRIP_LENGTH 16

// Pixel Mapped Output Configuration
#define ENABLE_PIXEL_MAPPED_OUTPUT false
#define UNIVERSE_PIXEL_MAPPED 1 //DMX Universe to listen in
#define OFFSET_PIXEL_MAPPED 0 //DMX Start Channel

//Must define:
/*
#define WIFI_SSID "hfsjdkf"
#define PASSWORD "sdjfhdskjfn"
*/
#include "secret.h"

#endif
