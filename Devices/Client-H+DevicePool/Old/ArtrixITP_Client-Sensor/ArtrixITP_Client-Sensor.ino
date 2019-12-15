#define THIS_DEVICE_ID "CLI5F33Q"
//#define THIS_DEVICE_ID "CLI6E55S"
#include "ArtrixITP.h"

ArtrixITP client;

// For only Bool input
void sendUPDSENSOR(String sensorType, bool sensorData) {

  String sendMsg = "U,UPDSENSOR,";
  sendMsg += client.DEVICE_ID;
  sendMsg += ",";
  sendMsg += sensorType;
  sendMsg += ",";
  sendMsg += "BOOL";
  sendMsg += ",";

  if (sensorData) sendMsg += "1,END|";
  else sendMsg += "0,END|";

  client.send433(sendMsg);

  Serial.println("--------------------------Get Light!----------------------------");
    Serial.println("");
    Serial.println("");

    Serial.print("Send:");
    Serial.println(sensorData);

    Serial.println("");
    Serial.println("");
    Serial.println("--------------------------Get Light!----------------------------");

}
bool before = false;
long long lastTime = 0;
bool getHumanSensor() {
  if (millis() - lastTime >= 2000) {
    before = !before;
    lastTime = millis();
  }
  return before;
 // return digitalRead(5);
}

void setup() {

  Serial.begin(230400);
  pinMode(5, INPUT);

  client = ArtrixITP(THIS_DEVICE_ID);

}

bool lastState = false;
void loop() {

  client.checkAll();

  if (client.handShaked) {

    bool state = getHumanSensor();
    if (!state == lastState) {
      sendUPDSENSOR("HUMANSENSOR", getHumanSensor());
      Serial.print("State changed | New state = ");
      Serial.println(state);
    }
    lastState = state;

  }

  if (!client.handShaked)delay(1000);
  else delay(250);
}
