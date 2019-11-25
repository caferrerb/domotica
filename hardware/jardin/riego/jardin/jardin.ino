#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include <EEPROM.h>
#define WIFI_CONFIG_ADDRESS 10
struct package {
  uint val = 0;
  char str[20] = "";
  char WIFI_SSID[20] = "";
  char WIFI_PASS[20] = "";
  uint8 bssid[6];
  IPAddress ip; //Node static IP
  IPAddress gateway;
  IPAddress subnet;
  uint8 APchannel = 0;
};
typedef struct package Package;
Package data;
Package new_data;


void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);

    EEPROM.begin(sizeof(package) + WIFI_CONFIG_ADDRESS);
    Serial.print("sizeof(package): "); Serial.println(sizeof(package) + WIFI_CONFIG_ADDRESS);

}

void loop() {
    // put your main code here, to run repeatedly:
    
}
