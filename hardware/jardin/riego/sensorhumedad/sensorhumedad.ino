#include <ESP8266WiFi.h>
#include <Adafruit_ADS1015.h>
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

float humedad[10];
float adcs[4];
int row = 0;
const int RESET_PIN = 8;

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */

 
int ledPin = 13; // GPIO13
WiFiServer server(80);

void wifiManagerSetup(){ 
 //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    //reset saved settings

    if(digitalRead(RESET_PIN) == 1){
      Serial.println("Reset configuration.....");
      wifiManager.resetSettings();
      //set custom ip for portal
      wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
    }
    

      //fetches ssid and pass from eeprom and tries to connect
      //if it does not connect it starts an access point with the specified name
      //here  "AutoConnectAP"
      //and goes into a blocking loop awaiting configuration
      wifiManager.autoConnect("GardenController");
      //or use this for auto generated name ESP + ChipID
      //wifiManager.autoConnect();
  
      //if you get here you have connected to the WiFi
      Serial.println("connected...yeey :)");
   
}

void wifiSetup() { 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
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

void setupADC(){
  ads.setGain(GAIN_ONE);
  ads.begin();
}

 
void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println(F("Serial started at 115200"));
  Serial.println();
      
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  wifiManagerSetup();
  wifiSetup();
  setupADC();
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

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  leerHumedad();
  leerADCS(adcs); 
  visualizeData(client);
}

void visualizeData(WiFiClient client){
  
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("<table border=\"1\"><tr><td>Canal 0</td><td>Canal 1</td><td>Canal 2</td><td>Canal 3</td></tr>");
client.print("<tr>");

    client.print("<td>");
    client.print(adcs[0]);
    client.print("</td>");

 client.print("<td>");
    client.print(adcs[1]);
    client.print("</td>");

     client.print("<td>");
    client.print(adcs[2]);
    client.print("</td>");

     client.print("<td>");
    client.print(adcs[3]);
    client.print("</td>");
    
    client.print("</tr>");
  client.print("</table>");

 
  client.print("<h1>Feuncha, la humedad es:<h2>");
 
  client.print("Humedad Actual = <h2>");
  float lecturaHumedad = leerHumedad();
  client.print(lecturaHumedad);
  client.print("</h2>");

  humedad[row % 10] = lecturaHumedad;
  row++;
  
  client.print("<table border=\"1\"><tr><td>muestra</td><td>valor</td></tr>");
  for (int i = 0; i < 10; i ++) {
    client.print("<tr>");

    client.print("<td>");
    client.print(i+1);
    client.print("</td>");

    client.print("<td>");
    client.print(humedad[i]);
    client.print("</td>");

    
    client.print("</tr>");
  }
  client.print("</table>");
 
  client.println("<br><br>");
  client.println("<a href=\"/leer=1\"\"><button>leer humedad </button></a>");
  client.println("</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}

float* leerADCS(float lecturas[]){

  lecturas[0] = bitsToVoltage(ads.readADC_SingleEnded(0));
  lecturas[1] = bitsToVoltage(ads.readADC_SingleEnded(1));
  lecturas[2] = bitsToVoltage(ads.readADC_SingleEnded(2));
  lecturas[3] = bitsToVoltage(ads.readADC_SingleEnded(3));
  Serial.print("AIN0: "); Serial.println(ads.readADC_SingleEnded(0));
  Serial.print("AIN1: "); Serial.println(lecturas[1]);
  Serial.print("AIN2: "); Serial.println(lecturas[2]);
  Serial.print("AIN3: "); Serial.println(lecturas[3]);
  Serial.println(" ");
  return lecturas;
}

float bitsToVoltage(int bits){

  return (3.3/47800)*65342 - bits*(3.3/47800);
}



 
