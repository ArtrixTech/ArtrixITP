#include "ClientProcess.h"

void ArtrixITP::CLIhandShake() {

  String msg = "U,REGDEV,";
  msg += this->DEVICE_ID;
  msg += ",END|";

  Serial.print(F("    [REGDEV]Send:"));
  Serial.println(msg);

  this->send433(msg);

}

void ArtrixITP::CLI_REGDEV(Command cmd) {

  Serial.print(F("    [REGDEV]SER:"));
  Serial.println(cmd.getPara(3));

  if (cmd.getPara(4) == "OK") {
    Serial.println(F("    [Handshake]OK"));
    this->handShaked = true;
    this->lastAliveCheck = millis();
  }
  else {
    Serial.println(F("    [Handshake]BAD"));
  }

}

void ArtrixITP::CLI_ALIVE(Command cmd) {

  this->handShaked = true;
  this->lastAliveCheck = millis();

  String msg = "U,ALIVE,";
  msg += this->DEVICE_ID;
  msg += ",END|";
  this->send433(msg);

}

