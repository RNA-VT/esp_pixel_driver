//The WiFi handlers must be enabled in ArtNet.h
#define ARTNET_ENABLE_WIFI true
#include "config.h"
#include "ota.h"
#include "fixture.h"
#include "pixel_mapped_output.h"
#include <Artnet.h>
#include <Adafruit_NeoPixel.h>

#define PIN 13 //D7 on the 8266MOD pkg

ArtnetWiFiReceiver artnet;
Ota ota;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(STRIP_LENGTH, PIN, NEO_GRB + NEO_KHZ800);

//Output Objects
PixelMappedOutput pmo(&pixels);
Fixture outputFixture(&pixels);

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
  pmo.subscriber(data, size);
}

void fixture_subscriber(uint8_t *data, uint16_t size)
{
  outputFixture.subscriber(data, size);
}

void setup()
{
  Serial.begin(115200);
  setup_wifi();
  artnet.begin();
  artnet.subscribe(UNIVERSE_PIXEL_MAPPING, pixel_mapping_subscriber);
  artnet.subscribe(UNIVERSE_FIXTURE, fixture_subscriber);
  
  pixels.begin();
  pixels.clear();
}

void loop()
{
  ota.check();
  artnet.parse();
  outputFixture.run();
}
