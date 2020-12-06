//The WiFi handlers must be enabled in ArtNet.h
#define ARTNET_ENABLE_WIFI true
#include "config.h"
#include "ota.h"
#include "pixel_mapped_output.h"
#include <Artnet.h>
#include <Adafruit_NeoPixel.h>
#include <esp8266wifi.h>
#include <ESP8266mDNS.h>        // Include the mDNS library

ArtnetWiFiReceiver artnet;
Ota ota;

//Adafruit_NeoPixel gpio0 = Adafruit_NeoPixel(STRIP_LENGTH, 0, NEO_GRB + NEO_KHZ800);
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

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(STRIP_LENGTH, 13, NEO_GRB + NEO_KHZ800);
PixelMappedOutput pmo(&pixels);

void setup_wifi()
{
  WiFi.begin(WIFI_SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("-~~<*}(~){*>~~-\n");
    delay(500);
  }
  Serial.println("WiFi connected, IP = ");
  Serial.println(WiFi.localIP());
  delay(500);
  char* zone = "pixeldriver69";

  //Multicast DNS
  if (!MDNS.begin(zone)) {             
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");
  
}

void pixel_mapping_subscriber(uint8_t *data, uint16_t size)
{
  pmo.subscriber(data, size);
}

void setup()
{
  Serial.begin(115200);
  setup_wifi();

  pixels.begin();
  pixels.clear();

  artnet.begin();
  artnet.subscribe(UNIVERSE_PIXEL_MAPPED, pixel_mapping_subscriber);
}

void loop()
{
  ota.check();
  artnet.parse();
  delay(10);
}