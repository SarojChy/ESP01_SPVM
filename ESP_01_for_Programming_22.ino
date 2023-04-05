
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>
#include "FS.h"
#define trig_pin 2


const char* host = "maker.ifttt.com";
bool SendMsg = false;
int data;
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
const unsigned long eventInterval = 15000;
unsigned long previousTime = 0;
unsigned long currentTime;
// Search for parameter in HTTP POST request
const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";
const char* PARAM_INPUT_3 = "uid";

//Variables to save values from HTML form
String ssid;
String pass;
String ip;
String gateway;
String uid;

// File paths to save input values permanently
const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";
const char* uidPath = "/uid.txt";
IPAddress localIP;
//IPAddress localIP(192, 168, 1, 200); // hardcoded

// Set your Gateway IP address
//IPAddress localGateway;
IPAddress localGateway(192, 168, 1, 1); //hardcoded
IPAddress subnet(255, 255, 0, 0);

void setup() {
  // Serial port for debugging purposes
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  initSPIFFS();
  pinMode(trig_pin, INPUT_PULLUP);
  // Load values saved in SPIFFS
  ssid = readFile(SPIFFS, ssidPath);
  pass = readFile(SPIFFS, passPath);
  uid = readFile(SPIFFS, uidPath);
  Serial.println(ssid);
  Serial.println(pass);
  Serial.println(uid);
  WiFi.begin(ssid.c_str(), pass.c_str());
  delay(500);
  Serial.println(WiFi.localIP());
  delay(1000);
}

void loop() {
  currentTime = millis();
  if (digitalRead(trig_pin) == LOW) {
    if (currentTime - previousTime >= eventInterval) {
      AP_Mode();
      previousTime = currentTime;
    }
  }
  if (Serial.available() > 0) {
    String msg = Serial.readStringUntil('\n');
    delay(1000);
    data = msg.toInt();
    Serial.println(data);

  }
  if (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting....");
    delay(2000);
  }
  if (data == 60) {
    delay(1000);
    SendMsg = false;
  }

  if (SendMsg == false && data == 0) {
    sendSMS();
    SendMsg = true;
  }
  Serial.println(ssid);
  Serial.println(pass);
  Serial.println(uid);
  delay(1000);
}
