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

  display.clear();

}
static const uint8_t PROGMEM Heart_16x16[] = {
  0x00, 0x00, 0x18, 0x18, 0x3C, 0x3C, 0x7E, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0x7F, 0xFE, 0x3F, 0xFC, 0x1F, 0xF8, 0x0F, 0xF0, 0x07, 0xE0, 0x03, 0xC0, 0x00, 0x00 //未命名文件0
};

static const uint8_t PROGMEM WIFI[] = {0x00, 0x00, 0x30, 0x00, 0xFE, 0x01, 0x03, 0x03, 0x78, 0x00,
                                       0xCC, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
                                      };
/*"C:\Users\a2010\Desktop\wifi2.bmp",0*/

void updateState() {
  
  display.clear();
  display.fillRect(0, 0, 128, 12, WHITE);
  display.setCursor(2, 2);
  display.setTextSize(1);
  display.setTextColor(WHITE);

  if (WiFi.status() == WL_CONNECTED) {
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.print("WiFi");
    display.setTextColor(WHITE);
  }
  else {
    display.setTextSize(1);
    display.print("WiFi");          //Fill the wifi by white As erasing
  }

  if (server.wifiClient.connected()) {
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.print(" SER");
    display.setTextColor(WHITE);
  }
  else {
    display.setTextSize(1);
    display.print(" SER");          //Fill the wifi by white As erasing
  }

  if (server.reactionClient.connected()) {
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.print(" REACT");
    display.setTextColor(WHITE);
  }
  else {
    display.setTextSize(1);
    display.print(" REACT");          //Fill the wifi by white As erasing
  }

  String Online = "Online:";
  Online.concat(server.devPool.getAliveCount());

  display.setTextSize(2);
  display.setCursor(14, 24);
  display.print(Online);

  //display.drawBitmap(10, 10, WIFI, 10, 10, WHITE);
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
int interval = 200;
long long lastScreenUpdate = 0;
void loop() {

  server.checkAll();

  if (millis() - lastScreenUpdate > interval) {
    updateState();
    lastScreenUpdate = millis();
  }

}
