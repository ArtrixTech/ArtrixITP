#define THIS_DEVICE_ID "CLITE6RM"

//#define THIS_DEVICE_ID "CLI6E55S"
#include "ArtrixITP.h"

#include <Wire.h>

ArtrixITP client;

#define DIRTPIN A3

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
bool getDirtHumiSensor(int thres) {

  int res = analogRead(A3);
  Serial.println(res);
  if (res<thres)return !true;
  else return !false;

}

void setup() {

  Serial.begin(9600);
  pinMode(A3, INPUT);
  
  client = ArtrixITP(THIS_DEVICE_ID);

}

bool lastState = false;
long long lastTemp = 0;

bool secondSend = false;
long long firstSend = 0;
void loop() {

  client.checkAll();

  if (client.handShaked) {

    bool state = getDirtHumiSensor(500);

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

  }

  if (!client.handShaked)delay(1000);
  else delay(20);
}
