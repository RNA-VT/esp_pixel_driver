#include "ota.h"

void Ota::setup(){
    // Define OTA Event Handlers
    ArduinoOTA.onStart([this]() {
      String type = ArduinoOTA.getCommand() == U_FLASH
                        ? "sketch"
                        : "filesystem";
      // NOTE: if updating FS this would be the place to unmount FS using FS.end()
      Serial.println("Start updating %" + type);
    });
    ArduinoOTA.onEnd([this]() {
      Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([this](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      switch (error)
      {
      case OTA_AUTH_ERROR:
        Serial.println("Auth Failed");
        break;
      case OTA_BEGIN_ERROR:
        Serial.println("Begin Failed");
        break;
      case OTA_CONNECT_ERROR:
        Serial.println("Connect Failed");
        break;
      case OTA_RECEIVE_ERROR:
        Serial.println("Receive Failed");
        break;
      case OTA_END_ERROR:
        Serial.println("End Failed");
        break;
      default:
        break;
      }
    });
    ArduinoOTA.begin();
    Serial.println("OTA Ready");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP().toString());
  }

  void Ota::check() {
    ArduinoOTA.handle();
  }