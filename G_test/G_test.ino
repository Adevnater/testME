/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"


// Replace with your network credentials
const char* ssid = "ESP32_access";
const char* password = "12345678";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
// WiFiServer server(80);

// Set LED GPIO
const int LEDin = 2;
// Stores LED state
String ledState;
String DEVICE;

String setD = "dafult"; // 0 is slave 1 is master
String Ontime = "dafult"; // time(ms)
String Offtime = "dafult"; // time(ms)
String Pattern = "dafult"; // pattern LED
const char* param01 = "setD";
const char* param02 = "ONTIME";
const char* param03 = "OFFTIME";
const char* param04 = "PATTERN";




// Replaces placeholder with LED state value
String processor(const String& var){
  Serial.println(var);
  if(var == "DEVICESTATUS"){
    if(setD == "1"){
      DEVICE = "MASTER";
    }
    else if (setD == "0"){
      DEVICE = "SLAVE";
    }
    Serial.println(DEVICE);
    return DEVICE;
  }
  if(var == "timeON")
    return Ontime;
  if(var == "timeOFF")
    return Offtime;
  if(var == "Patt")
    return Pattern;
  return String();
}
    


void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode(LEDin, OUTPUT);

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid,password);
  // WiFi.softapAPConfig(local_ip,gateway,subnet);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address:");
  Serial.println(IP);
  
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println("Connecting to WiFi..");
  // }
  delay(500);

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

// Start server
  server.begin();
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to load style.css file
  // server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
  //   request->send(SPIFFS, "/style.css", "text/css");
  // });
  server.on("/submit", HTTP_GET, [](AsyncWebServerRequest *request){
   if(request->hasParam(param01)){
      setD = request->getParam(param01)->value();
      Serial.print("setD is ");Serial.println(setD);
    }
    if(request->hasParam(param02)){
      Ontime = request->getParam(param02)->value();
      Serial.print("ONTIME is ");Serial.println(Ontime);
    }
    if(request->hasParam(param03)){
      Offtime = request->getParam(param03)->value();
      Serial.print("OFFTIME is ");Serial.println(Offtime);
    }
    if(request->hasParam(param04)){
      Pattern = request->getParam(param04)->value();
      Serial.print("Pattern is ");Serial.println(Pattern);
    }
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

}
 
void loop(){
  delay(1000);
    if (setD == "0"){
      Serial.print("Device is Slave  "); Serial.println(setD);
    } else if (setD == "1"){
      Serial.print("Device is Master  "); Serial.println(setD);
    }
    Serial.print("ontime is ");Serial.println(Ontime);
    Serial.print("offtime is ");Serial.println(Offtime);
    Serial.print("Pattern is ");Serial.println(Pattern);
    Serial.println("NEWWWWWW");
    delay(1000);
}