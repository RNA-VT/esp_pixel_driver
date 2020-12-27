//The WiFi handlers must be enabled in ArtNet.h
#define ARTNET_ENABLE_WIFI true
#include "config.h"
#include <Artnet.h>
#include <Adafruit_NeoPixel.h>
#include <Esp.h>

#ifdef ESP8266
  #include <esp8266wifi.h>
#elif defined(ESP32)
  #include <WiFi.h>
#endif

ArtnetWiFiReceiver artnet;

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
//Adafruit_NeoPixel gpio13 = Adafruit_NeoPixel(STRIP_LENGTH, 13, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel gpio14 = Adafruit_NeoPixel(STRIP_LENGTH, 14, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel gpio15 = Adafruit_NeoPixel(STRIP_LENGTH, 15, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel gpio16 = Adafruit_NeoPixel(STRIP_LENGTH, 16, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel *pixels = &gpio0;

//Network Config
const IPAddress ip(192, 168, 1, 200);
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet(255, 255, 255, 0);

void setup_wifi()
{
  WiFi.begin(WIFI_SSID, PASSWORD);
  WiFi.setSleep(false);
  WiFi.config(ip, gateway, subnet);
  int loop_limit = 60;
  int count = 0;
  while (WiFi.status() != WL_CONNECTED && count < loop_limit)
  {
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
  //Multicast DNS
  if (!MDNS.begin("idplaceholder.pixel.driver")) {             
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");
  
}

void mock_output(int i, uint8_t r, uint8_t g, uint8_t b)
  {
    char buf[16]; //formatting buffer
    sprintf(buf, "Pixel ID: %u", i);
    Serial.println(buf);

    sprintf(buf, "~~Green: %u", g);
    Serial.println(buf);

    sprintf(buf, "~~Red: %u", r);
    Serial.println(buf);

    sprintf(buf, "~~Blue: %u", b);
    Serial.println(buf);
  }

void pixel_mapping_subscriber(const uint8_t *data, const uint16_t size)
{
  const int pixels_per_channel = 3;
  for (int i = 0; i < STRIP_LENGTH; i++)
  {
    int offset = OFFSET_PIXEL_MAPPED + i * pixels_per_channel;
    //The order of the colors may vary by ArtNet source.
    //We assume GRB here
    uint8_t g = data[offset];
    uint8_t r = data[offset + 1];
    uint8_t b = data[offset + 2];

    switch (OUTPUT_MODE)
    {
    case OUTPUT_MODE_LED:
      pixels->setPixelColor(i, pixels->Color(g, r, b));
      if (pixels->canShow())
      {
        pixels->show();
      }
      mock_output(i, r, g, b);
      break;
    case OUTPUT_MODE_MOCK:
      mock_output(i, r, g, b);
      break;
    }
  }
}

void setup()
{
  //Serial Start
  Serial.begin(115200);

  pixels->begin();
  pixels->clear();
  
  status(0);

  setup_wifi();
  
  status(1);

  pixels.begin();
  pixels.clear();
  
  artnet.begin();
  artnet.subscribe(UNIVERSE_PIXEL_MAPPED, pixel_mapping_subscriber);
}

void loop()
{
  artnet.parse();
  delay(10);
}


void status(uint8_t state)
{
  const int pixels_per_channel = 3;
  for (int i = 0; i < STRIP_LENGTH; i++)
  {
    int offset = OFFSET_PIXEL_MAPPED + i * pixels_per_channel;
    uint8_t g = 0;
    uint8_t r = 0;
    uint8_t b = 0;

    // States
    // 0 - Connecting to Wifi
    // 1 - Waiting For ArtNet
    switch (state)
    {
    case 0:
      r = 255;
      b = 255;
      break;
    case 1:
      g = 255;    
    default:
      break;
    }

    switch (OUTPUT_MODE)
    {
    case OUTPUT_MODE_LED:
      pixels->setPixelColor(i, pixels->Color(g, r, b));
      pixels->show();
      mock_output(i, r, g, b);
      break;
    case OUTPUT_MODE_MOCK:
      mock_output(i, r, g, b);
      break;
    }
  }
}
