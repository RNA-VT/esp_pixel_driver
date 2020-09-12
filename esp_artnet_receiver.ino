//The WiFi handlers must be enabled in ArtNet.h
#define ARTNET_ENABLE_WIFI true
#include "config.h"
#include "ota.h"
#include "handlers.h"
#include <Artnet.h>
#include <Adafruit_NeoPixel.h>

#define PIN 13 //D7 on the 8266MOD pkg

ArtnetWiFiReceiver artnet;
Ota ota;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(STRIP_LENGTH, PIN, NEO_GRB + NEO_KHZ800);
Handlers handlers(OUTPUT_MODE, &pixels);

//Network Config
const IPAddress ip(192, 168, 1, 201);
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet(255, 255, 255, 0);

void setup_wifi()
{
  WiFi.begin(WIFI_SSID, PASSWORD);
  WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("-~~<}(~){>~~-\n");
    delay(500);
  }
  Serial.print("WiFi connected, IP = ");
  Serial.println(WiFi.localIP());
}

void pixel_mapping_subscriber(uint8_t *data, uint16_t size)
{
  //Pixel Mapped data is color data by pixel to be applied immediatly
  handlers.pixel_mapping(data, size);
}

void fixture_subscriber(uint8_t *data, uint16_t size)
{
  //Fixture data is a set of parameters that configures animation playback
  handlers.fixture_channels(data, size);
}

void setup()
{
  Serial.begin(115200);
  setup_wifi();
  artnet.begin();
  artnet.subscribe(UNIVERSE_PIXEL_MAPPING, pixel_mapping_subscriber);
  artnet.subscribe(UNIVERSE_FIXTURE, fixture_subscriber);
  handlers.setup();
}

void loop()
{
  ota.check();
  artnet.parse();
  //TODO: Execute Fixture Animation here
}
