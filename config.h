#ifndef CONFIG_H
#define CONFIG_H

// TODO: replace with Wifi manger form config

#include "enums.h"

#define OUTPUT_MODE OUTPUT_MODE_LED
#define OUTPUT_PIN 17
#define STRIP_LENGTH 250

// Pixel Mapped Output Configuration
#define START_UNIVERSE 1 //DMX Universe to listen in
#define CHANNEL_OFFSET 0 //DMX Start Channel

#define LOG_LEVEL LOG_LEVEL_STANDARD // 0: normal, 1: debug

//Must define:
/*
#define WIFI_SSID "hfsjdkf"
#define PASSWORD "sdjfhdskjfn"
*/
#include "secret.h"

#endif
 