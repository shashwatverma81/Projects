//receiver

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//network credentials
const char* ssid = "NCU";
const char* password = "wirelessncu";

// MQTT broker details
const char* mqttServer = "192.168.56.237";
const int mqttPort = 1883;
const char* mqttTopic = "voice";

WiFiClient espClient;
PubSubClient client(espClient);

int relay = D1;

void setup() {
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);

  setupWiFi();
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  reconnectMQTT();
  client.subscribe(mqttTopic);
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();
}

void setupWiFi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

   //WiFi.begin(ssid); 
   WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT broker...");
    if (client.connect("ReceiverESP8266L")) {
      Serial.println("Connected to MQTT broker");
      client.subscribe(mqttTopic);
    } else {
      Serial.print("Failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);

  String voice = "";
  for (int i = 0; i < length; i++) {
    voice += (char)payload[i];
  }

  Serial.print("Received data: ");
  Serial.println(voice);

  if (voice == "lock") {
    digitalWrite(relay, HIGH);
    Serial.println("Door locked");
  }
  else if (voice == "unlock") {
    digitalWrite(relay, LOW);
    Serial.println("Door Unlocked");
    delay(10000);
    digitalWrite(relay, HIGH);
    Serial.println("Door Locked");
  }
}
