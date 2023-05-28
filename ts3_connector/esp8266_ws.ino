/*
  Teamspeak3 Connector untuk ESP8266 atau WEMOS D1 Mini
  Protokol: Websocket
  Pointer: ROOM INDONESIA

  oleh JZ13OUK/YG3AWJ
  http://roipmerdeka.id
*/

#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <WebSocketsClient.h>
WiFiManager wm;
const char* webSocketHost = "159.65.132.218";
const int webSocketPort = 1880;
const char* webSocketPath = "/ws/roip";
WebSocketsClient webSocket;
unsigned long lastHeartbeatTime = 0;
const unsigned long heartbeatInterval = 30000;
const byte pin_cos = 5; //GPIO5/D1 ACTIVE LOW
const byte pin_cor = 4; //GPIO4/D2 ACTIVE LOW
const byte pin_led = 2; //GPIO2/D4
byte rx_signal = 0;
byte flag_conn = 0;
unsigned long lastHeartbeatTime_led = 0;
const unsigned long heartbeatInterval_led = 250;

void setup() {
  WiFiManager wifiManager;
  wifiManager.autoConnect("ROIP-MERDEKA");
  pinMode(pin_cos, INPUT_PULLUP);
  pinMode(pin_cor, OUTPUT);
  pinMode(pin_led, OUTPUT);
  digitalWrite(pin_cor, HIGH);
  digitalWrite(pin_led, LOW);
  webSocket.begin(webSocketHost, webSocketPort, webSocketPath);
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
  if (millis() - lastHeartbeatTime > heartbeatInterval) {
    webSocket.sendTXT("hb");
    lastHeartbeatTime = millis();
  }
  if (millis() - lastHeartbeatTime_led > heartbeatInterval_led) {
    digitalWrite(pin_led, !digitalRead(pin_led));
    lastHeartbeatTime_led = millis();
  }
  if (digitalRead(pin_cos) == 0) {
    rx_signal = 1;
    delay(10);
  } else {
    rx_signal = 0;
    delay(10);
  }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      flag_conn = 0;
      break;
    case WStype_CONNECTED:
      digitalWrite(pin_led, HIGH);
      flag_conn = 1;
      break;
    case WStype_TEXT:
      String c_payload, i_payload;
      for (int i = 0; i < length; i++) {
        c_payload  =  (char)payload[i];
        i_payload  += c_payload;
      }
      if (i_payload == "0") {
        digitalWrite(pin_cor, HIGH);
      } else if (i_payload == "1") {
        if (rx_signal == 0) {
          digitalWrite(pin_cor, LOW);
        }
      }
      break;
  }
}
