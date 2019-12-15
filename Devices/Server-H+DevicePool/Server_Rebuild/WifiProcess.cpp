#include <ESP8266WiFi.h>
#include "ArtrixITP.h"
#include "MessagePool.h"

//WIFI
char ssid[] = "Artrix";  // Replace with your own WIFI-SSID
char pass[] = "23336666";  // Replace with your own WiFi Password

bool ArtrixITP::connectWIFI() {

  if (WiFi.status() != WL_CONNECTED) {

    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);

    long long startTime = millis();
    bool succeed = true;
    int thres = 30000; // Force stop time cost limit = 30 Seconds

    while (WiFi.status() != WL_CONNECTED) {

      delay(500);
      Serial.print(".");

      if (millis() - startTime > thres) {
        succeed = false;
        break;
      }

    }
    if (succeed) {
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
    }
    else {
      Serial.println("WIFI-ConnectFailed(TimeOut)");
    }

    return succeed;
  }
  return true;

}

const char* host = "121.42.232.71";
int port = 48903;

/*
  const char* host = "121.42.232.71";
  int port = 45517;
*/

/*
  const char* host = "118.89.25.199";
  int port = 6652;
*/
bool ArtrixITP::connectServer() {

  if (!this->wifiClient.connected()) {
    if (!this->wifiClient.connect(host, port)) {
      Serial.println("connection failed");
      return false;
    } else {

      String msg = "REGDEV,";                                                                   // Eg.REGDEV,SER233666
      msg += this->DEVICE_ID;

      this->sendViaWIFI(msg);

    }
  }

}

bool ArtrixITP::forceReconnectServer() {

  this->wifiClient.stop();

  if (!this->wifiClient.connect(host, port)) {
    Serial.println("connection failed");
    return false;
  } else {

    String msg = "REGDEV,";                                                                   // Eg.REGDEV,SER233666
    msg += this->DEVICE_ID;

    this->prioritySendViaWIFI(msg);

  }


}

void ArtrixITP::prioritySendViaWIFI(String data) {

  if (data) {

    Message msg;
    msg.data = data;
    msg.lastSentTry = 0;
    msg.tryCount = 0;

    this->msgPool.priorityAppend(msg);

  }

}

void ArtrixITP::sendViaWIFI(String data) {

  if (data) {

    Message msg;
    msg.data = data;
    msg.lastSentTry = 0;
    msg.tryCount = 0;

    this->msgPool.append(msg);

  }

}

String ArtrixITP::getWIFIResponse() {

  while (this->wifiClient.available()) {

    String line = this->wifiClient.readStringUntil('|');
    line += '|';

    line.replace(" ", "");
    line.replace("\n", "");

    if (line && line != " " && line != "|"  && line != "|") {
      //Serial.print("WIFI_IN:");
      //Serial.println(line);
      return line;
    }

  }
  return "FALSE";
}
