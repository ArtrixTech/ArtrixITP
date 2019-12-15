#define THIS_DEVICE_ID "CLI5F33Q"

//#define THIS_DEVICE_ID "CLI6E55S"
#include "ArtrixITP.h"

#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <dht11.h>

ArtrixITP client;
Adafruit_BMP085 bmp;
dht11 DHT11;

#define DHT11PIN 8

// For only Bool input
void sendUPDSENSOR(String sensorType, String dataType, bool sensorData) {

  String sendMsg = "U,UPDSENSOR,";
  sendMsg += client.DEVICE_ID;
  sendMsg += ",";
  sendMsg += sensorType;
  sendMsg += ",";
  sendMsg += dataType;
  sendMsg += ",";

  if (sensorData) sendMsg += "1,END|";
  else sendMsg += "0,END|";

  client.send433(sendMsg);

  Serial.println(F("--------------------------Get Light!----------------------------"));
  Serial.println("");
  Serial.println("");

  Serial.print("Send:");
  Serial.println(sensorData);

  Serial.println("");
  Serial.println("");
  Serial.println(F("--------------------------Get Light!----------------------------"));

}

void sendUPDSENSOR(String sensorType, String dataType, float sensorData) {

  String sendMsg = "U,UPDSENSOR,";
  sendMsg += client.DEVICE_ID;
  sendMsg += ",";
  sendMsg += sensorType;
  sendMsg += ",";
  sendMsg += dataType;
  sendMsg += ",";

  sendMsg.concat(sensorData);
  sendMsg += ",END|";

  client.send433(sendMsg);

  Serial.println(F("--------------------------Get Sensor----------------------------"));
  Serial.println("");
  Serial.println("");

  Serial.print("Send:");
  Serial.println(sensorData);

  Serial.println("");
  Serial.println("");
  Serial.println(F("--------------------------Get Sensor----------------------------"));

}
//bool before = false;
//long long lastTime = 0;
/*
  bool getHumanSensor() {
  if (millis() - lastTime >= 2000) {
    before = !before;
    lastTime = millis();
  }
  return before;
  // return digitalRead(5);
  }
*/
bool getHumanSensor(bool last) {

  bool res = !digitalRead(5);
  delay(5);
  if (!digitalRead(5) == res)return res;
  else return last;
  //return analogRead(A1) > 573;

}

void setup() {

  Serial.begin(9600);
  pinMode(A2, INPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

  pinMode(9, OUTPUT);
  pinMode(8, INPUT);
  pinMode(7, OUTPUT);
  digitalWrite(9, HIGH);
  digitalWrite(7, LOW);


  bmp.begin();

  client = ArtrixITP(THIS_DEVICE_ID);

}

bool lastState = false;
long long lastTemp = 0;

bool secondSend = false;
long long firstSend = 0;
void loop() {

  client.checkAll();

  if (client.handShaked) {

    bool state = getHumanSensor(lastState);

    if (secondSend && millis() - firstSend >= 200) {
      sendUPDSENSOR("HUMANSENSOR", "BOOL", state); secondSend = false;
    }

    if (!state == lastState) {
      sendUPDSENSOR("HUMANSENSOR", "BOOL", state);
      firstSend = millis();
      secondSend = true;

      Serial.print(F("State changed | New state = "));
      Serial.println(state);
    }
    lastState = state;

    if (millis() - lastTemp > 2500) {

      sendUPDSENSOR("TEMP", "FLOAT", (float)bmp.readTemperature());
      sendUPDSENSOR("PRES", "FLOAT", (float)(bmp.readPressure() * 0.01));

      DHT11.read(DHT11PIN);
      sendUPDSENSOR("HUMI", "FLOAT", (float)DHT11.humidity);
      
      lastTemp = millis();
    }

  }

  if (!client.handShaked)delay(1000);
  else delay(20);
}
