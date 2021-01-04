#include <WiFi.h>
#include <ESPmDNS.h>
#include <WebSocketsServer.h>
#include <DallasTemperature.h>
#include "MAX30100_PulseOximeter.h"
#include <OneWire.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <Ticker.h>
#define DS18B20 19
#define DHTPIN 25
#define LED1 33
#define LED2 32
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
OneWire oneWire(DS18B20);
DallasTemperature sensors(&oneWire);
PulseOximeter pox;

void send_sensor();

Ticker timer;

char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<script>
var connection = new WebSocket('ws://'+location.hostname+':81/');
var button_1_status = 0;
var button_2_status = 0;
var temp_data = 0;
var hum_data = 0;
var bpm_data = 0;
var SpO2_data = 0;
var bodytemperature_data = 0;
connection.onmessage = function(event){
  var full_data = event.data;
  console.log(full_data);
  var data = JSON.parse(full_data);
  temp_data = data.temp;
  hum_data = data.hum;
  var bpm_data = data.bpm;
  var SpO2_data = data.SpO2;
  var bodytemperature_data = data.bodytemperature;
  document.getElementById("temp_meter").value = temp_data;
  document.getElementById("temp_value").innerHTML = temp_data;
  document.getElementById("hum_meter").value = hum_data;
  document.getElementById("hum_value").innerHTML = hum_data;
  document.getElementById("bpm_meter").value = bpm_data;
  document.getElementById("bpm_value").innerHTML = bpm_data;
  document.getElementById("SpO2_meter").value = SpO2_data;
  document.getElementById("SpO2_value").innerHTML = SpO2_data;
  document.getElementById("bodytemperature_meter").value = bodytemperature_data;
  document.getElementById("bodytemperature_value").innerHTML = bodytemperature_data;
}
function button_1_on()
{
   button_1_status = 1; 
  console.log("LED 1 is ON");
  send_data();
}
function button_1_off()
{
  button_1_status = 0;
console.log("LED 1 is OFF");
send_data();
}
function button_2_on()
{
   button_2_status = 1; 
  console.log("LED 2 is ON");
  send_data();
}
function button_2_off()
{
  button_2_status = 0;
console.log("LED 2 is OFF");
send_data();
}
function send_data()
{
  var full_data = '{"LED1" :'+button_1_status+',"LED2":'+button_2_status+'}';
  connection.send(full_data);
}
</script>
<body>
<center>
<h1>Systém pro monitorovaní zdravotního stavu pacienta</h1>
<h3> LED 1 </h3>
<button onclick= "button_1_on()" >On</button><button onclick="button_1_off()" >Off</button>
<h3> LED 2 </h3>
<button onclick="button_2_on()">On</button><button onclick="button_2_off()">Off</button>
</center>
<div style="text-align: center;">
<h3>Teplota</h3><meter value="2" min="0" max="100" id="temp_meter"> </meter><h3 id="temp_value" style="display: inline-block;"> 2 </h3>
<h3>Vlhkost</h3><meter value="2" min="0" max="100" id="hum_meter"> </meter><h3 id="hum_value" style="display: inline-block;"> 2 </h3>
<h3>Tep</h3><meter value="2" min="0" max="100" id="bpm_meter"> </meter><h3 id="bpm_value" style="display: inline-block;"> 2 </h3>
<h3>Kyslík</h3><meter value="2" min="0" max="100" id="SpO2_meter"> </meter><h3 id="SpO2_value" style="display: inline-block;"> 2 </h3>
<h3>Teplota těla</h3><meter value="2" min="0" max="100" id="bodytemperature_meter"> </meter><h3 id="bodytemperature_value" style="display: inline-block;"> 2 </h3>
</body>
</html>
)=====";

#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);
WebSocketsServer websockets(81);

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Page Not found");
}

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

void onBeatDetected()
{
  Serial.println("Beat!");
}

void setup(void)
{
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  dht.begin();

  WiFi.softAP("kontrola", "");
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());

  if (MDNS.begin("ESP"))
  { //esp.local/
    Serial.println("MDNS responder started");

    pinMode(19, OUTPUT);
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
      pox.setOnBeatDetectedCallback(onBeatDetected);
    }
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  }

  server.on("/", [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/html", webpage);
  });

  server.on("/led1/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(LED1, HIGH);
    request->send_P(200, "text/html", webpage);
  });

  server.onNotFound(notFound);

  server.begin();
  websockets.begin();
  websockets.onEvent(webSocketEvent);
  timer.attach(2, send_sensor);
}

void loop(void)
{
  websockets.loop();
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
  if (isnan(BPM) || isnan(SpO2))
  {
    Serial.println(F("Nepodařilo se číst z MAX30100 senzoru"));
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