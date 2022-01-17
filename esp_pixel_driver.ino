#include "config.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ArtnetWifi.h>
#include <EEPROM.h>
#include <Esp.h>
#include <FastLED.h>

#ifdef ESP8266
#include <esp8266wifi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

#include "DmxParameters.h"
#include "config.h"
#include "memory.h"
#include "pixel_server.h"
#include "wifimanager_adapter.h"

// LEDs
CRGB *leds;

Configuration config;

// Api Server
PixelServer pixel_server;

// Calculated Constants
int channels;
int maxUniverses;

// DMX Handler Globals
ArtnetWifi artnet;
bool *universesReceived;
int previousDataLength = 0;
bool dmxReceived;

// Network Config
const IPAddress ip(192, 168, 1, 249);
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet(255, 255, 255, 0);

QueueHandle_t dmxQueue = xQueueCreate(1, sizeof(DmxParameters));

void setup() {

  // Serial Start
  Serial.begin(115200);
  delay(500);

  if (dmxQueue == NULL) {
    Serial.println("Error creating the queue");
  }

  xTaskCreatePinnedToCore(dmxTask,          /* Function to implement the task */
                          "DMX Frame Task", /* Name of the task */
                          100000,           /* Stack size in words */
                          NULL,             /* Task input parameter */
                          100,              /* Priority of the task */
                          NULL,             /* Task handle. */
                          1);               /* Core where the task should run */

  // Load Config from memory, apply static overrides, and run wm setup
  init_config();

  // LED Init
  leds = (CRGB *)malloc(sizeof(CRGB) * config.strip_length);
  if (!leds) { // failed malloc returns null
    Serial.println(
        "Failed to allocate memory for LED Array. Reduce Strip Length.");
    Serial.println("Returning to Configuration Portal...");
    WifiManagerAdapter::setup(&config);
  }
  FastLED.addLeds<WS2812, OUTPUT_PIN, RGB>(leds, config.strip_length);

  // Status - Connecting to Wifi
  status(0);
  setup_wifi();
  artnet.begin();
  delay(500);

  pixel_server.begin();
  delay(500);

  // Status - Waiting for Artnet
  status(1);
  artnet.setArtDmxCallback(onDmxFrame);
  delay(500);
}

void loop() {
  // handle web requests
  pixel_server.Listen();
  // listen for artnet
  artnet.read();
}

void init_config() {
  Memory memory;

  // Load Config From Memory
  config = memory.Load();

  // Apply Overrides
  config.applyOverrides();
#ifndef DISABLE_WIFIMANAGER_SETUP
  WifiManagerAdapter::setup(&config);
#endif
  pixel_server.config = &config;

  channels = 3 * config.strip_length;
  maxUniverses = channels / 512 + ((channels % 512) ? 1 : 0);
  bool received[maxUniverses];
  universesReceived = (bool *)malloc(sizeof(bool) * maxUniverses);
  if (!universesReceived) { // failed malloc returns null
    Serial.println(
        "Failed to allocate memory for LED Array. Reduce Strip Length.");
    Serial.println("Returning to Configuration Portal...");
    WifiManagerAdapter::setup(&config);
  }

  // Save
  memory.Save(config);
}

void setup_wifi() {
#ifdef WIFI_SSID
  WiFi.begin(WIFI_SSID, PASSWORD);
#else
  WiFi.begin();
#endif

#ifdef ESP32
  WiFi.setSleep(false);
#endif
  WiFi.config(ip, gateway, subnet);
  int loop_limit = 30;
  int count = 0;
  while (WiFi.status() != WL_CONNECTED && count < loop_limit) {
    Serial.println("-~~<*}(~){*>~~-\n");
    delay(500);
    count++;
  }
  if (count == loop_limit) {
    ESP.restart();
  }
  Serial.println("WiFi connected, IP = ");
  Serial.println(WiFi.localIP());
  delay(500);
}

void status(uint8_t state) {
  for (int i = 0; i < config.strip_length; i++) {
    uint8_t g = 0;
    uint8_t r = 0;
    uint8_t b = 0;

    // States
    // 0 - Connecting to Wifi
    // 1 - Waiting For ArtNet
    switch (state) {
    case 0:
      r = 255;
      b = 255;
      break;
    case 1:
      g = 255;
    default:
      break;
    }

    if (config.output_leds) {
      leds[i] = CRGB(r, g, b);
    }
    debug_led_output(i, r, g, b);
  }
  if (config.output_leds) {
    delay(500);
    FastLED.show();
  }
}

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence,
                uint8_t *data) {
  DmxParameters params = DmxParameters(universe, length, sequence, data, leds);
  TaskHandle_t dxmHandle = NULL;
  if (xQueueSend(dmxQueue, (void *)&params, (TickType_t)10) != pdPASS) {
    /* Failed to post the message, even after 10 ticks. */
  }
}

void dmxTask(void *parameters) {
  bool sendFrame = 1;
  for (;;) {
    if (dmxQueue != NULL) {
      DmxParameters params;
      if (xQueueReceive(dmxQueue, &(params), (TickType_t)10) == pdPASS) {
        sendFrame = 1;

        // Mark received Universe
        if ((params.universe - config.start_universe) < maxUniverses) {
          universesReceived[params.universe - config.start_universe] = 1;
        }

        for (int i = 0; i < maxUniverses; i++) {
          if (universesReceived[i] == 0) {
            // if we're missing an expected universe, do not playback
            sendFrame = 0;
            break;
          }
        }

        // read universe and put into the right part of the display buffer
        for (int i = 0; i < params.length / 3; i++) {
          int led = i + (params.universe - config.start_universe) *
                            (previousDataLength / 3);
          if (led < config.strip_length && config.output_leds) {

            params.leds[led] = CRGB(params.data[i * 3], params.data[i * 3 + 1],
                                    params.data[i * 3 + 2]);

            debug_led_output(i, params.data[i * 3], params.data[i * 3 + 1],
                             params.data[i * 3 + 2]);
          }
        }
        previousDataLength = params.length;

        if (sendFrame) {
          FastLED.show();
          // Reset universeReceived to 0
          memset(universesReceived, 0, maxUniverses);
        }
      }
    }
  }
}

void debug_led_output(int i, uint8_t r, uint8_t g, uint8_t b) {
  if (config.debug_logs) {
    char buf[16]; // formatting buffer
    sprintf(buf, "Pixel ID: %u", i);
    Serial.println(buf);

    sprintf(buf, "~~Green: %u", g);
    Serial.println(buf);

    sprintf(buf, "~~Red: %u", r);
    Serial.println(buf);

    sprintf(buf, "~~Blue: %u", b);
    Serial.println(buf);
  }
}
