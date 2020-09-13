//The WiFi handlers must be enabled in ArtNet.h
#define ARTNET_ENABLE_WIFI true
#include "config.h"
#include "ota.h"
#include "fixture.h"
#include "pixel_mapped_output.h"
#include <Artnet.h>
#include <Adafruit_NeoPixel.h>
#include <esp8266wifi.h>
#include <esp8266httpclient.h>
#include <ArduinoJson.h>


ArtnetWiFiReceiver artnet;
Ota ota;
HTTPClient http;
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
  if (DATA_SOURCE == ARTNET ) {
    artnet.begin();
    artnet.subscribe(UNIVERSE_PIXEL_MAPPING, pixel_mapping_subscriber);
    artnet.subscribe(UNIVERSE_FIXTURE, fixture_subscriber);
  } 
  pixels.begin();
  pixels.clear();
}

void loop()
{
  ota.check();
  outputFixture.run();
}

void Inputs() {
  switch (DATA_SOURCE)
  {
  case ARTNET:
    artnet.parse();
    break;
  case DATA_SOURCE_SERVER:
    LoadConfigFromServer();
    break;
  default:
    break;
  }
}

void LoadConfigFromServer() {
  const size_t capacity = JSON_OBJECT_SIZE(5) + 40;
  DynamicJsonDocument doc(capacity);

  http.begin(DATA_SOURCE_URL);
  int code = http.GET();
  string payload;
  if (code >= 200 && code < 300) {
    payload = http.getString();
    JsonObject& root = doc.parseObject(payload);
    if (root.success()) {
      AnimationOptions opts;
      opts.opacity = root["opacity"];
      opts.animation = root["animation"];
      opts.option = root["option"];
      opts.speed = root["speed"];
      opts.strobe = root["strobe"];
    }

  }
}