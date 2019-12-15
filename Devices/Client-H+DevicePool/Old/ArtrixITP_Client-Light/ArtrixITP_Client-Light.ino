//#define THIS_DEVICE_ID "CLI5F33Q"
#define THIS_DEVICE_ID "CLI6E55S"
#include "ArtrixITP.h"

ArtrixITP client;

void SETPWR(Command cmd) {

  bool pwrState = (cmd.getPara(3) == "ON") ? true : false;

  Serial.println("-----------------------Light Update!--------------------------");
  Serial.println("");
  Serial.println("");
  Serial.println(pwrState);
  Serial.println("");
  Serial.println("");
  Serial.println("-----------------------Light Update!--------------------------");
  
  if (pwrState) digitalWrite(13, HIGH);
  else  digitalWrite(13, LOW);

}

void setup() {
  Serial.begin(9600);
  client = ArtrixITP(THIS_DEVICE_ID);
  client.bindSETPWRRecall(SETPWR);
}

void loop() {
  client.checkAll();
  if (!client.handShaked)delay(1000);
  else delay(100);
}
