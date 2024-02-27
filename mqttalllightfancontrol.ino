//sender 
#include "BluetoothSerial.h"
#include <WiFi.h>
#include <PubSubClient.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Replace with your network credentials
const char* ssid = "NCU";
const char* password = "wirelessncu";

// MQTT broker details
const char* mqttServer = "192.168.56.237";
const int mqttPort = 1883;
const char* mqttTopic = "voice";

WiFiClient espClient;
PubSubClient client(espClient);
BluetoothSerial SerialBT;
String voice;

int
  lightc1 = 15,
  lightc2 = 2,
  lightc3 = 4,
  fan1 = 5,
  fan2 = 18,
  fan3 = 19,
  fan4 = 21,
  fan5 = 22,
  fan6 = 23;

void setup() {
  Serial.begin(9600);
  setupWiFi();
  client.setServer(mqttServer, mqttPort);
  SerialBT.begin("Tinkeringlab");  //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  pinMode(lightc1, OUTPUT);
  pinMode(lightc2, OUTPUT);
  pinMode(lightc3, OUTPUT);
  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  pinMode(fan3, OUTPUT);
  pinMode(fan4, OUTPUT);
  pinMode(fan5, OUTPUT);
  pinMode(fan6, OUTPUT);
  //
  digitalWrite(lightc1, HIGH);
  digitalWrite(lightc2, HIGH);
  digitalWrite(lightc3, HIGH);
  digitalWrite(fan1, HIGH);
  digitalWrite(fan2, HIGH);
  digitalWrite(fan3, HIGH);
  digitalWrite(fan4, HIGH);
  digitalWrite(fan5, HIGH);
  digitalWrite(fan6, HIGH);
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  while (SerialBT.available()) {  //Check if there is an available byte to read
    delay(10);                    //Delay added to make thing stable
    char c = SerialBT.read();     //Conduct a serial read
    if (c == '#') { break; }      //Exit the loop when the # is detected after the word
    voice += c;                   //Shorthand for voice = voice + c
  }
  if (voice.length() > 0) {
    Serial.println(voice);  // Clear the voice variable
    if ((voice == "l1") || (voice == "all lights on")) {
    digitalWrite(lightc1, LOW);
    digitalWrite(lightc2, LOW);
    digitalWrite(lightc3, LOW);
  } else if ((voice == "f11") || (voice == "all fans on")) {
    digitalWrite(fan1, LOW);
    digitalWrite(fan2, LOW);
    digitalWrite(fan3, LOW);
    digitalWrite(fan4, LOW);
    digitalWrite(fan5, LOW);
    digitalWrite(fan6, LOW);
  } else if ((voice == "lc1") || (voice == "column one on") || (voice == "column 1 on")) {
    digitalWrite(lightc1, LOW);
  } else if ((voice == "lc2") || (voice == "column two on") || (voice == "column 2 on") || (voice == "column to on")) {
    digitalWrite(lightc2, LOW);
  } else if ((voice == "lc3") || (voice == "column three on") || (voice == "column 3 on")) {
    digitalWrite(lightc3, LOW);
  } else if ((voice == "f1") || (voice == "fan one on") || (voice == "fan 1 on") || (voice == "1 on") || (voice == "one on")) {
    digitalWrite(fan1, LOW);
  } else if ((voice == "f2") || (voice == "fan two on") || (voice == "fan 2 on") || (voice == "fan to on") || (voice == "2 on") || (voice == "two on") || (voice == "to on")) {
    digitalWrite(fan2, LOW);
  } else if ((voice == "f3") || (voice == "fan three on") || (voice == "fan 3 on") || (voice == "3 on") || (voice == "three on")) {
    digitalWrite(fan3, LOW);
  } else if ((voice == "f4") || (voice == "fan four on") || (voice == "fan 4 on") || (voice == "fan for on") || (voice == "four on") || (voice == "4 on") || (voice == "for on")) {
    digitalWrite(fan4, LOW);
  } else if ((voice == "f5") || (voice == "fan five on") || (voice == "fan 5 on") || (voice == "5 on") || (voice == "five on")) {
    digitalWrite(fan5, LOW);
  } else if ((voice == "f6") || (voice == "fan six on") || (voice == "fan 6 on") || (voice == "fan sex on") || (voice == "6 on") || (voice == "six on") || (voice == "sex on")) {
    digitalWrite(fan6, LOW);
  }

  //turn off
  else if ((voice == "l0") || (voice == "all lights off") || (voice == "all lights of")) {
    digitalWrite(lightc1, HIGH);
    digitalWrite(lightc2, HIGH);
    digitalWrite(lightc3, HIGH);
  } else if ((voice == "f0") || (voice == "all fans off") || (voice == "all fans of")) {
    digitalWrite(fan1, HIGH);
    digitalWrite(fan2, HIGH);
    digitalWrite(fan3, HIGH);
    digitalWrite(fan4, HIGH);
    digitalWrite(fan5, HIGH);
    digitalWrite(fan6, HIGH);
  } else if ((voice == "lc10") || (voice == "column one off") || (voice == "column 1 of") || (voice == "column one of") || (voice == "column 1 off")) {
    digitalWrite(lightc1, HIGH);
  } else if ((voice == "lc20") || (voice == "column two off") || (voice == "column 2 of") || (voice == "column two of") || (voice == "column 2 off") || (voice == "column 2 of") || (voice == "column to of") || (voice == "column to off")) {
    digitalWrite(lightc2, HIGH);
  } else if ((voice == "lc30") || (voice == "column three off") || (voice == "column 3 of") || (voice == "column three of") || (voice == "column 3 off")) {
    digitalWrite(lightc3, HIGH);
  } else if ((voice == "f10") || (voice == "fan one off") || (voice == "fan one of") || (voice == "fan 1 off") || (voice == "fan 1 of") || (voice == "one of") || (voice == "one off") || (voice == "1 of") || (voice == "1 off")) {
    digitalWrite(fan1, HIGH);
  } else if ((voice == "f20") || (voice == "fan two off") || (voice == "fan two of") || (voice == "fan 2 off") || (voice == "fan 2 of") || (voice == "fan to of") || (voice == "fan to off")  || (voice == "two of") || (voice == "two off") || (voice == "2 of") || (voice == "2 off") || (voice == "to of") || (voice == "to off")) {
    digitalWrite(fan2, HIGH);
  } else if ((voice == "f30") || (voice == "fan three off") || (voice == "fan three of") || (voice == "fan 3 off") || (voice == "fan 3 of") || (voice == "three of") || (voice == "three off") || (voice == "3 of") || (voice == "3 off")) {
    digitalWrite(fan3, HIGH);
  } else if ((voice == "f40") || (voice == "fan four off") || (voice == "fan four of") || (voice == "fan 4 off") || (voice == "fan 4 of") || (voice == "fan for off") || (voice == "fan for of")  || (voice == "four of") || (voice == "four off") || (voice == "4 of") || (voice == "4 off") || (voice == "for of") || (voice == "for off")) {
    digitalWrite(fan4, HIGH);
  } else if ((voice == "f50") || (voice == "fan five off") || (voice == "fan five of") || (voice == "fan 5 off") || (voice == "fan 5 of") || (voice == "five of") || (voice == "five off") || (voice == "5 of") || (voice == "5 off")  || (voice == "five of") || (voice == "five off") || (voice == "5 of") || (voice == "5 off")) {
    digitalWrite(fan5, HIGH);
  } else if ((voice == "f60") || (voice == "fan six off") || (voice == "fan six of") || (voice == "fan 6 off") || (voice == "fan 6 of") || (voice == "fan sex off") || (voice == "fan sex of")  || (voice == "six of") || (voice == "six off") || (voice == "6 of") || (voice == "6 off")  || (voice == "sex of") || (voice == "sex off")) {
    digitalWrite(fan6, HIGH);
  } else if ((voice == "a1") || (voice == "everything on")) {
    allon();
  } else if ((voice == "a0") || (voice == "everything off") || (voice == "everything of")) {
    alloff();
  } else {
    Serial.println("Publishing data: " + voice);
    client.publish(mqttTopic, voice.c_str());
  }

  voice = "";
  }

}

void setupWiFi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
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
    if (client.connect("SenderESP32")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void allon() {
  digitalWrite(lightc1, LOW);
  digitalWrite(lightc2, LOW);
  digitalWrite(lightc3, LOW);
  digitalWrite(fan1, LOW);
  digitalWrite(fan2, LOW);
  digitalWrite(fan3, LOW);
  digitalWrite(fan4, LOW);
  digitalWrite(fan5, LOW);
  digitalWrite(fan6, LOW);
}

void alloff() {
  digitalWrite(lightc1, HIGH);
  digitalWrite(lightc2, HIGH);
  digitalWrite(lightc3, HIGH);
  digitalWrite(fan1, HIGH);
  digitalWrite(fan2, HIGH);
  digitalWrite(fan3, HIGH);
  digitalWrite(fan4, HIGH);
  digitalWrite(fan5, HIGH);
  digitalWrite(fan6, HIGH);
}
