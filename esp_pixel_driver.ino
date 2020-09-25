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


Adafruit_NeoPixel gpio0 = Adafruit_NeoPixel(STRIP_LENGTH, 0, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel gpio1 = Adafruit_NeoPixel(STRIP_LENGTH, 1, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel gpio2 = Adafruit_NeoPixel(STRIP_LENGTH, 2, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel gpio3 = Adafruit_NeoPixel(STRIP_LENGTH, 3, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel gpio4 = Adafruit_NeoPixel(STRIP_LENGTH, 4, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel gpio5 = Adafruit_NeoPixel(STRIP_LENGTH, 5, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel gpio6 = Adafruit_NeoPixel(STRIP_LENGTH, 6, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel gpio7 = Adafruit_NeoPixel(STRIP_LENGTH, 7, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel gpio8 = Adafruit_NeoPixel(STRIP_LENGTH, 8, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel gpio9 = Adafruit_NeoPixel(STRIP_LENGTH, 9, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel gpio10 = Adafruit_NeoPixel(STRIP_LENGTH, 10, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel gpio11 = Adafruit_NeoPixel(STRIP_LENGTH, 11, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel gpio12 = Adafruit_NeoPixel(STRIP_LENGTH, 12, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel gpio13 = Adafruit_NeoPixel(STRIP_LENGTH, 13, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel gpio14 = Adafruit_NeoPixel(STRIP_LENGTH, 14, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel gpio15 = Adafruit_NeoPixel(STRIP_LENGTH, 15, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel gpio16 = Adafruit_NeoPixel(STRIP_LENGTH, 16, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel pixels_mapped = gpio13;
Adafruit_NeoPixel pixels_fixture = gpio0;

//
PixelMappedOutput *pmo;
Fixture *fixture;

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
    PixelMappedOutput output(pixels_mapped);
    pmo = &output;
  }

  if (ENABLE_FIXTURE)
  {
    //Fixture fxt(pixels_fixture);
    //fixture = &fxt;
  }

  if (ENABLE_PIXEL_MAPPED_OUTPUT || (ENABLE_FIXTURE && (FIXTURE_SOURCE == DATA_SOURCE_ARNET)))
  {
    artnet.begin();
  }

  if (ENABLE_PIXEL_MAPPED_OUTPUT)
  {
    pixels_mapped.begin();
    pixels_mapped.clear();
    artnet.subscribe(UNIVERSE_PIXEL_MAPPED, pixel_mapping_subscriber);
  }

  if (ENABLE_FIXTURE && (FIXTURE_SOURCE == DATA_SOURCE_ARNET))
  {
    pixels_fixture.begin();
    pixels_fixture.clear();
    artnet.subscribe(UNIVERSE_FIXTURE, fixture_subscriber);
  }
}

void loop()
{
  ota.check();
  Inputs();
  Outputs();
  delay(10);
}

void Inputs()
{
  if (ENABLE_PIXEL_MAPPED_OUTPUT || (ENABLE_FIXTURE && (FIXTURE_SOURCE == DATA_SOURCE_ARNET)))
  {
    artnet.parse();
  }
  else if (ENABLE_FIXTURE && FIXTURE_SOURCE == DATA_SOURCE_SERVER)
  {
    LoadConfigFromServer();
  }
}

void Outputs()
{
  if (ENABLE_FIXTURE)
  {
    //fixture->run();
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
    //fixture->updateConfiguration(opts);
  }
}