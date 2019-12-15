#include "ClientProcess.h"

void ArtrixITP::CLIhandShake() {

  String msg = "U,REGDEV,";
  msg += this->DEVICE_ID;
  msg += ",END|";

  Serial.print("    [REGDEV]Send:");
  Serial.println(msg);

  this->send433(msg);

}

void ArtrixITP::CLI_REGDEV(Command cmd) {

  Serial.print("    [REGDEV]Get response from:");
  Serial.println(cmd.getPara(3));

  Serial.print("    [REGDEV]Result:");
  Serial.println(cmd.getPara(4));

  if (cmd.getPara(4) == "OK") {
    Serial.println("    [HandShaked]Succeed");
    this->handShaked = true;
    this->lastAliveCheck = millis();
  }
  else {
    Serial.println("    [HandShaked]Failed");
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

