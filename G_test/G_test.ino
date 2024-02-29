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

String SendMac = "dafult";
String ReceiveMac = "dafult";
String Ontime = "dafult"; // time(ms)
String Offtime = "dafult"; // time(ms)
String Pattern = "dafult"; // pattern LED
String DeviceMode = "dafult"; // 0 is slave 1 is master
String Trigpair = "dafult";
String TrigMode = "dafult";

const char* param01 = "sendToMac";
const char* param02 = "receiveFromMac";
const char* param03 = "onTime";
const char* param04 = "offTime";
const char* param05 = "ledPattern";
const char* param06 = "deviceMode";
const char* param07 = "pairingToggle";
const char* param08 = "pairingMode";


// Replaces placeholder with LED state value
String processor(const String& var){
  Serial.println(var);
  if(var == "MacSend")
    return SendMac;
  if(var == "MacReceive")
    return ReceiveMac;
  if(var == "V_on")
    return Ontime;
  if(var == "V_off")
    return Offtime;
  if(var == "Patt")
    return Pattern;
  if(var == "D_status")
    return DeviceMode;
  if(var == "TrigP")
    return Trigpair;
  if(var == "TrigM")
    return TrigMode;
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
    request->send(SPIFFS, "/main.html", String(), false, processor);
  });
  
  // Route to load style.css file
  // server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
  //   request->send(SPIFFS, "/style.css", "text/css");
  // });
  server.on("/main.html", HTTP_GET, [](AsyncWebServerRequest *request){
   if(request->hasParam(param01)){
      SendMac = request->getParam(param01)->value();
      Serial.print("SendMac is ");Serial.println(SendMac);
    }
    if(request->hasParam(param02)){
      ReceiveMac = request->getParam(param02)->value();
      Serial.print("ReceiveMac is ");Serial.println(ReceiveMac);
    }
    if(request->hasParam(param03)){
      Ontime = request->getParam(param03)->value();
      Serial.print("Ontime is ");Serial.println(Ontime);
    }
    if(request->hasParam(param04)){
      Offtime = request->getParam(param04)->value();
      Serial.print("Offtime is ");Serial.println(Offtime);
    }
    if(request->hasParam(param05)){
      Pattern = request->getParam(param05)->value();
      Serial.print("Pattern is ");Serial.println(Pattern);
    }
    if(request->hasParam(param06)){
      DeviceMode = request->getParam(param06)->value();
      Serial.print("DeviceMode is ");Serial.println(DeviceMode);
    }
    if(request->hasParam(param07)){
      Trigpair = request->getParam(param07)->value();
      Serial.print("Trigpair is ");Serial.println(Trigpair);
    }
    if(request->hasParam(param08)){
      TrigMode = request->getParam(param08)->value();
      Serial.print("TrigMode is ");Serial.println(TrigMode);
    }
    request->send(SPIFFS, "/main.html", String(), false, processor);
  });

}
 
void loop(){

}