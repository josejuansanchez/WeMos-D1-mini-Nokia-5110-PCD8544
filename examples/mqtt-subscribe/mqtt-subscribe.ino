/*
 Basic ESP8266 MQTT example.

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then subscribes to the topic "MQTT_SUBSCRIBE_TOPIC", 
 printing out any messages it receives on a Nokia display 5110. 

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include <PubSubClient.h>

// WeMos Pinout
//---------------------------------------------------
const int8_t RST_PIN = D2;
const int8_t CE_PIN = D1;
const int8_t DC_PIN = D6;
const int8_t BL_PIN = D0;

// Nokia display
//---------------------------------------------------
Adafruit_PCD8544 display = Adafruit_PCD8544(DC_PIN, CE_PIN, RST_PIN);

// WiFi Setup
//---------------------------------------------------
#define WLAN_SSID             "...your SSID..."
#define WLAN_PASS             "...your PASS..."

// MQTT Setup
//---------------------------------------------------
#define MQTT_SERVER           "test.mosquitto.org"
#define MQTT_SERVERPORT       1883
#define MQTT_SUBSCRIBE_TOPIC  "...your TOPIC..."

WiFiClient espClient;
PubSubClient mqttClient(espClient);

//---------------------------------------------------
void setupWifi();
void callback(char* topic, byte* payload, unsigned int length);
void reconnectMqtt();

//---------------------------------------------------

void setup() {
  Serial.begin(115200);
  setupWifi();
  mqttClient.setServer(MQTT_SERVER, MQTT_SERVERPORT);
  mqttClient.setCallback(callback);

  // Turn LCD backlight on
  pinMode(BL_PIN, OUTPUT);
  digitalWrite(BL_PIN, HIGH);

  // Configure LCD
  //display.setRotation(2);
  display.begin();
  display.setContrast(50);
  display.setTextSize(3);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.clearDisplay();
}

//---------------------------------------------------

void loop() {
  if (!mqttClient.connected()) {
    reconnectMqtt();
  }
  mqttClient.loop();
}

//---------------------------------------------------

void setupWifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  
  WiFi.begin(WLAN_SSID, WLAN_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//---------------------------------------------------

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  display.clearDisplay();
  for (int i = 0; i < length; i++) {
    /*
    if ((char)payload[i] >= '0' && (char)payload[i] <= '9') {
      display.print((char)payload[i]);
    }
    */
    display.print((char)payload[i]);
  }
  display.display();
}

//---------------------------------------------------

void reconnectMqtt() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");

    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("connected");
      mqttClient.subscribe(MQTT_SUBSCRIBE_TOPIC);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

