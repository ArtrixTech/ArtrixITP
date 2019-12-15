#define THIS_DEVICE_ID "SER23333"

#include "ArtrixITP.h"
#include <SoftwareSerial.h>
#include <Adafruit_ssd1306syp.h>

// OLED
#define SDA_PIN 2//oled_SDA
#define SCL_PIN 0//oled_SCL
Adafruit_ssd1306syp display(SDA_PIN, SCL_PIN);

// Artrix ITP
ArtrixITP server(THIS_DEVICE_ID);

void initOLED() {

  display.initialize();//oled初始化

  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0, 24);
  display.print("Artrix ITP");
  display.setTextSize(1);
  display.setCursor(60, 56);
  display.print("V2.0 ArtrixTech");
  display.update();

  delay(2000);

  display.clear();

}

void updateState() {

  display.setTextSize(2);
  display.setCursor(0, 24);
  display.print("Online=");

  display.setTextSize(1);

  display.print(server.devPool.deviceCount);
  display.update();

}

void initPower() {

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);

  delay(10);

  digitalWrite(D1, HIGH);

}

void setup() {

  initPower();
  server.bindUPDSENSORRecall(updSensor);
  server.bindDOWNLINKRecall(dLink);

  initOLED();

}

void updSensor(Command cmd, bool isDebug) {

  String data = cmd.deriveMsg;
  server.sendViaWIFI(data);

  if (isDebug) {

    Serial.println("--------------------------Get Light!----------------------------");
    Serial.println("");
    Serial.println("");

    Serial.print("    [UPDSENSOR]GET: ");
    Serial.println(data);

    Serial.println("");
    Serial.println("");
    Serial.println("--------------------------Get Light!----------------------------");

  }

}

void dLink(Command cmd, bool isDebug) {

  String data = cmd.deriveMsg;
  data.replace("S,DOWNLINK,", "D,");

  if (isDebug) {
    Serial.print(" [Downlink AdHOC]");
    Serial.println(data);
  }
  server.send433(data);

}

void loop() {

  server.checkAll();
  updateState();

}
