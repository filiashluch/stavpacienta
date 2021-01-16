#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <WebSocketsServer.h>
#include <DallasTemperature.h>
#include "MAX30100_PulseOximeter.h"
#include <OneWire.h>
#include <Wire.h>
#include "SPIFFS.h"
#include <ArduinoJson.h>
#include <DHT.h>
#include "Ticker.h"

#define DS18B20 19
#define DHTPIN 25
#define LED1 33
#define LED2 32
#define DHTTYPE DHT11

const char *ssid = "ESP32-AP";
const char *password = "LetMeInPlz";

DHT dht(DHTPIN, DHTTYPE);
OneWire oneWire(DS18B20);
DallasTemperature sensors(&oneWire);
PulseOximeter pox;

Ticker timer;

AsyncWebServer server(80);
WebSocketsServer websockets(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
  switch (type)
  {
  case WStype_DISCONNECTED:
    Serial.printf("[%u] Odpojeno!\n", num);
    break;
  case WStype_CONNECTED:
  {
    IPAddress ip = websockets.remoteIP(num);
    Serial.printf("[%u] Připojeno z: %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
  }
  break;
  case WStype_TEXT:
    Serial.printf("[%u] get Text: %s\n", num, payload);
    String message = String((char *)(payload));
    Serial.println(message);

    DynamicJsonDocument doc(200);
    DeserializationError error = deserializeJson(doc, message);
    if (error)
    {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    int LED1_status = doc["LED1"];
    int LED2_status = doc["LED2"];
    digitalWrite(LED1, LED1_status);
    digitalWrite(LED2, LED2_status);
  }
}

void onIndexRequest(AsyncWebServerRequest *request)
{
  IPAddress remote_ip = request->client()->remoteIP();
  Serial.println("[" + remote_ip.toString() +
                 "] HTTP GET request of " + request->url());
  request->send(SPIFFS, "/index.html", "text/html");
}

void onCSSRequest(AsyncWebServerRequest *request)
{
  IPAddress remote_ip = request->client()->remoteIP();
  Serial.println("[" + remote_ip.toString() +
                 "] HTTP GET request of " + request->url());
  request->send(SPIFFS, "/style.css", "text/css");
}

/*void onJSRequest(AsyncWebServerRequest *request) {
  IPAddress remote_ip = request->client()->remoteIP();
  Serial.println("[" + remote_ip.toString() +
                  "] HTTP GET request of " + request->url());
  request->send(SPIFFS, "/index.js", "text/js");
}*/

void onPageNotFound(AsyncWebServerRequest *request)
{
  IPAddress remote_ip = request->client()->remoteIP();
  Serial.println("[" + remote_ip.toString() +
                 "] HTTP GET request of " + request->url());
  request->send(404, "text/plain", "Not found");
}

void send_sensor()
{
  pox.update();
  sensors.requestTemperatures();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float BPM = pox.getHeartRate();
  float SpO2 = pox.getSpO2();
  float bodytemperature = sensors.getTempCByIndex(0);

  if (isnan(h) || isnan(t))
  {
    Serial.println(F("Nepodařilo se číst z DHT senzoru"));
    return;
  }
  String JSON_Data = "{\"temp\":";
  JSON_Data += t;
  JSON_Data += ",\"hum\":";
  JSON_Data += h;
  JSON_Data += ",\"tep\":";
  JSON_Data += BPM;
  JSON_Data += ",\"ox\":";
  JSON_Data += SpO2;
  JSON_Data += ",\"bodytemp\":";
  JSON_Data += bodytemperature;
  JSON_Data += "}";
  Serial.println(JSON_Data);
  websockets.broadcastTXT(JSON_Data);
}

void onBeatDetected()
{
  Serial.println("Tep!");
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  dht.begin();

  if (!SPIFFS.begin())
  {
    Serial.println("Error mounting SPIFFS");
    while (1)
      ;
  }

  WiFi.softAP(ssid, password);

  Serial.println();
  Serial.println("Access point bezi");
  Serial.print("IP adresa: ");
  Serial.println(WiFi.softAPIP());

  Serial.print("Inicializace MAX30100..");

  if (!pox.begin())
  {
    Serial.println("FAILED");
    for (;;)
      ;
  }
  else
  {
    Serial.println("SUCCESS");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_46_8MA);

  pinMode(14, OUTPUT);

  server.on("/", HTTP_GET, onIndexRequest);

  server.on("/style.css", HTTP_GET, onCSSRequest);

  //server.on("/index.js", HTTP_GET, onJSRequest);

  server.onNotFound(onPageNotFound);

  send_sensor();
  server.begin();
  websockets.begin();
  websockets.onEvent(webSocketEvent);
  timer.attach(0.2, send_sensor);
}

void loop()
{
  websockets.loop();
}