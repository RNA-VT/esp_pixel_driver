//The WiFi handlers must be enabled in ArtNet.h
#define ARTNET_ENABLE_WIFI true
#include "config.h"
#include "ota.h"
#include "fixture.h"
#include "pixel_mapped_output.h"
#include <Artnet.h>
#include <Adafruit_NeoPixel.h>
#include <esp8266wifi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

ArtnetWiFiReceiver artnet;
Ota ota;
HTTPClient http;

Adafruit_NeoPixel *pixels_mapped = NULL;
PixelMappedOutput *pmo = NULL;

Adafruit_NeoPixel *pixels_fixture = NULL;
Fixture *fixture = NULL;

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
  pmo->subscriber(data, size);
}

void fixture_subscriber(uint8_t *data, uint16_t size)
{
  fixture->subscriber(data, size);
}

void setup()
{
  Serial.begin(115200);
  setup_wifi();

  if (ENABLE_PIXEL_MAPPED_OUTPUT)
  {
    pixels_mapped = new Adafruit_NeoPixel(STRIP_LENGTH, PIN_PIXEL_MAPPED_OUTPUT, NEO_GRB + NEO_KHZ800);
    pmo = new PixelMappedOutput(pixels_mapped);
  }

  if (ENABLE_FIXTURE)
  {
    pixels_fixture = new Adafruit_NeoPixel(STRIP_LENGTH, PIN_FIXTURE_OUTPUT, NEO_GRB + NEO_KHZ800);
    fixture = new Fixture(pixels_fixture);
  }

  if (ENABLE_PIXEL_MAPPED_OUTPUT || (ENABLE_FIXTURE && (FIXTURE_SOURCE == DATA_SOURCE_ARNET)))
  {
    artnet.begin();
  }

  if (ENABLE_PIXEL_MAPPED_OUTPUT)
  {
    pixels_mapped->begin();
    pixels_mapped->clear();
    artnet.subscribe(UNIVERSE_PIXEL_MAPPED, pixel_mapping_subscriber);
  }

  if (ENABLE_FIXTURE && (FIXTURE_SOURCE == DATA_SOURCE_ARNET))
  {
    pixels_fixture->begin();
    pixels_fixture->clear();
    artnet.subscribe(UNIVERSE_FIXTURE, fixture_subscriber);
  }
}

void loop()
{
  ota.check();
  if (ENABLE_FIXTURE)
  {
    fixture->run();
  }
}

void Inputs()
{
  if (ENABLE_FIXTURE)
  {
    switch (FIXTURE_SOURCE)
    {
    case DATA_SOURCE_ARNET:
      artnet.parse();
      break;
    case DATA_SOURCE_SERVER:
      LoadConfigFromServer();
      break;
    default:
      break;
    }
  }
}

void LoadConfigFromServer()
{
  const size_t capacity = JSON_OBJECT_SIZE(5) + 40;
  DynamicJsonDocument doc(capacity);

  http.begin(FIXTURE_SERVER);
  int code = http.GET();
  String payload;
  if (code >= 200 && code < 300)
  {
    payload = http.getString();
    deserializeJson(doc, payload);

    AnimationOptions opts;
    opts.opacity = doc["opacity"];
    opts.animation = doc["animation"];
    opts.option = doc["option"];
    opts.speed = doc["speed"];
    opts.strobe = doc["strobe"];
    fixture->updateConfiguration(opts);
  }
}