#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
#include <ESP8266WiFi.h>
#include <Adafruit_ADS1015.h>
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <ESP8266HTTPClient.h>


typedef struct  {
  int sample_time;
  String id;
  float measure_coeficients[4];
}ChannelConf;

typedef struct {
  String id;
  int locationId;
  int ownerId;
  ChannelConf channels[5];
  String location;
  int gain;
  float convertion_factor;
}DeviceConf;

DeviceConf deviceConf;
float humedad[10];
float adcs[4];
int row = 0;
const int RESET_PIN = D7;
const int DEBUG_PIN = 3; //PIN RX
bool isDebugging = true;
bool isResetting = false;

const int PIN_PUMP_0 = D3;
const int PIN_PUMP_1 = D4;
const int PIN_PUMP_2 = D5;
const int PIN_PUMP_3 = D6;

int pumpState[4];
const int PUMP_PINS[] = { PIN_PUMP_0, PIN_PUMP_1, PIN_PUMP_2, PIN_PUMP_3 };

const float VOLT_FACTOR =   0.1250f;

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */

char backServer[40];
char deviceId[6];
 
int LED_PIN = D0; // GPIO13
ESP8266WebServer server(80);

//flag for saving data
bool shouldSaveConfig = false;

void wifiManagerSetup(){ 

  readCustomParam();
  // The extra parameters to be configured (can be either global or just in the setup)
  // After connecting, parameter.getValue() will get you the configured value
  // id/name placeholder/prompt default length
  WiFiManagerParameter customBackServer("back server", "Backend Server", backServer, 40);
  WiFiManagerParameter customDeviceId("device ID", "device ID", deviceId, 6);

  
 //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    //reset saved settings

    //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);

    if(isResetting){
      Serial.println("Reset configuration.....");
      wifiManager.resetSettings();
      //set custom ip for portal
      //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
    }
    
  //add all your parameters here
  wifiManager.addParameter(&customBackServer);
  wifiManager.addParameter(&customDeviceId);
      //fetches ssid and pass from eeprom and tries to connect
      //if it does not connect it starts an access point with the specified name
      //here  "AutoConnectAP"
      //and goes into a blocking loop awaiting configuration
      wifiManager.autoConnect("GardenController");
      //or use this for auto generated name ESP + ChipID
      //wifiManager.autoConnect();
  
      //if you get here you have connected to the WiFi
      Serial.println("Conectado :)");

   

        //read updated parameters
  strcpy(backServer, customBackServer.getValue());
  strcpy(deviceId, customDeviceId.getValue());
   Serial.print("Params:");
      Serial.print(" deviceId=");
      Serial.print(deviceId);
      Serial.print(" ,backServer=");
      Serial.print(backServer);
writeCustomParams();
   
}

void wifiStatus() { 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
    // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
}

void setupChannels(){
   HTTPClient http;
   WiFiClient client;
   String backServerStr(backServer);
   String deviceIdStr(deviceId);
   String confStr;

  String url = "http://" + backServerStr + "devices-ms/devices/" + deviceIdStr + "/detail";
 
   if (http.begin(client, url)) //Iniciar conexión
   {
      Serial.print("[HTTP] GET...\n");
      int httpCode = http.GET();  // Realizar petición
 
      if (httpCode > 0) {
         Serial.printf("[HTTP] GET... code: %d\n", httpCode);
 
         if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = http.getString();   // Obtener respuesta
            Serial.println(payload);   // Mostrar respuesta por serial

              StaticJsonDocument<200> doc;
                // Deserialize the JSON document
              DeserializationError error = deserializeJson(doc, payload);

            // Test if parsing succeeds.
            if (error) {
              Serial.print(F("deserializeJson() failed: "));
              Serial.println(error.c_str());
              return;
            }

            //const char* sensor = doc["channels"][0][];

         }
      }
      else {
         Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
 
      http.end();
   }
   else {
      Serial.printf("[HTTP} Unable to connect\n");
   }
 
   delay(30000);  
}

void setupADC(){
  ads.setGain(GAIN_ONE);
  ads.begin();
}


void setupAPI(){
   Serial.println(F("setupAPI.........."));
// Start the server
  server.begin();
  server.on("/",HTTP_GET, handleRoot); 
  server.on("/pumps/switch", handlePumps); 

}

void setupPumps(){
    pinMode(PIN_PUMP_0, OUTPUT);
    pinMode(PIN_PUMP_1, OUTPUT);
    pinMode(PIN_PUMP_2, OUTPUT);
    pinMode(PIN_PUMP_3, OUTPUT);
}

void setup() {
    Serial.begin(115200);
    delay(500);
    Serial.println(F("Serial started at 115200"));
    Serial.println();
  
    pinMode(DEBUG_PIN, INPUT);
    pinMode(RESET_PIN, INPUT);

  if (digitalRead(DEBUG_PIN) == LOW){
    isDebugging = true;
    Serial.println(F("DEBUG PIN ACTIVE"));
  }

  if (digitalRead(RESET_PIN) == LOW){
    Serial.println(F("RESET PIN ACTIVE"));

    isDebugging = false;
    isResetting = true;

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
  }

  if (isDebugging){
    setupAPI();
  }
  
  wifiManagerSetup();
  wifiStatus();
  setupADC();
  setupPumps();
}

void loop() {
  debug();

  
}

void debug() {
  if(isDebugging){
     //Serial.println(F("Debugging.........."));
    server.handleClient(); //Handling of incoming requests
  }
}

String  paintPumpButton(int pump){
    String response = "<a href=\"/pumps/switch?pump=";
    response +=pump+1;
    
    if(pumpState[pump] == HIGH){
      response +="\"\"><button style=\"background-color: #4CAF50;\">";
      response +="Turn OFF";
    }

    if(pumpState[pump] == LOW){
      response +="\"\"><button style=\"background-color: #f44336;\">";
      response +="Turn ON";
    }
    
    response +=" Pump ";
    response +=pump+1;
    response +=" </button></a>";

    return response;
}

String rootResponse(){
// Return the response
  String response;
  response +=""; //  do not forget this one
  response +="<!DOCTYPE HTML>";
  response +="<html>";
  response +="<h1> Controlador Jardin</h1>";
  response +="<h2> Configs</h2>";
  response +="<table border=\"1\"><tr><td>Device Id</td><td>";
  response += deviceId;
  response += "</td><td>Backend Server</td><td>";
  response += backServer;
  response += "</td></tr>";

  response +="<h2>Sensores</h2>";
  response +="<table border=\"1\"><tr><td>Canal 0</td><td>Canal 1</td><td>Canal 2</td><td>Canal 3</td></tr>";
  response +="<tr>";

  response +="<td>";
  response +=adcs[0];
  response +="</td>";

  response +="<td>";
  response +=adcs[1];
  response +="</td>";

  response +="<td>";
  response +=adcs[2];
  response +="</td>";

  response +="<td>";
  response +=adcs[3];
  response +="</td>";
    
  response +="</tr>";
  response +="</table>";

  response +="<br><br>";
  response +="<a href=\"/\"><button>Leer canales </button></a>";

  response +="<br><br>";
  response += paintPumpButton(0);
  response += paintPumpButton(1);
  response += paintPumpButton(2);
  response += paintPumpButton(3);

  response +="</html>";
Serial.println(response);
  return response;
}

void handleRoot(){
  leerADCS();
  Serial.println("Request handleRoot");
  delay(1);
  server.send(200, "text/html", rootResponse());
  Serial.println("Request answered");
  Serial.println("");
}

void setPumpState(int pump){
   digitalWrite(PUMP_PINS[pump], pumpState[pump]);
   Serial.println("");
   Serial.print("PUMP ");
  Serial.print(pump);
  Serial.print(" = ");
  Serial.print(pumpState[pump]);
  Serial.print("on pin  ");
  Serial.println(PUMP_PINS[pump]);
}

void handlePumps(){
  Serial.print("Request handlePumps");
  int pump = server.arg("pump").toInt() -1;

  pumpState[pump] = !pumpState[pump];
  

  setPumpState(pump);

  server.send(200, "text/html", rootResponse());

  Serial.println("Request answered");
  Serial.println("");
}


void leerADCS(){
  leerHumedad();
  float channel0 =ads.readADC_SingleEnded(0);
  float channel1 =ads.readADC_SingleEnded(1);
  float channel2 =ads.readADC_SingleEnded(2);
  float channel3 =ads.readADC_SingleEnded(3);
  Serial.println("leyendo adcs---------");

  adcs[0] = bitsToVoltage(channel0);
  Serial.print("AIN0: "); Serial.print(channel0);
  Serial.print(" ,V0: "); Serial.println(adcs[0]);

  adcs[1] = bitsToVoltage(channel1);
  Serial.print("AIN1: "); Serial.print(channel1);
  Serial.print(" ,V1: "); Serial.println(adcs[1]);

  adcs[2] = bitsToVoltage(channel2);
  Serial.print("AIN2: "); Serial.print(channel2);
  Serial.print(" ,V2: "); Serial.println(adcs[2]);

  adcs[3] = bitsToVoltage(channel3);
  Serial.print("AIN3: "); Serial.print(channel3);
  Serial.print(" ,V3: "); Serial.println(adcs[3]);
  
  Serial.println(" ");
}

float bitsToVoltage(int bits){

  return (bits *  VOLT_FACTOR)/1000;
}

float leerHumedad(){
int sensorValue = analogRead(A0); //Lectura del ADC 
  float voltage = sensorValue * (3.3 / 1023.0); //escalamos a voltaje 

  
 //Enviamos por el puerto serie
  Serial.print("ADC= ");
  Serial.print(sensorValue);
  Serial.print("  Voltaje= ");
  Serial.println(voltage); 
  
  delay(100);  

  return voltage;
} 


void readCustomParam() {
  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, buf.get());
        serializeJson(doc, Serial);

        if (error){
          Serial.println("failed to load json config");
        } else {
          Serial.println("\nparsed json");

          strcpy(backServer, doc["back_server"]);
          strcpy(deviceId, doc["device_id"]);
        }
        configFile.close();
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
}

void writeCustomParams(){
    //save the custom parameters to FS
  if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonDocument doc(1024);
    doc["back_server"] = backServer;
    doc["device_id"] = deviceId;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }
    serializeJson(doc, Serial);
    serializeJson(doc, configFile);

    //json.printTo(Serial);
    //json.printTo(configFile);
    configFile.close();
    //end save
  }
}

//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}
