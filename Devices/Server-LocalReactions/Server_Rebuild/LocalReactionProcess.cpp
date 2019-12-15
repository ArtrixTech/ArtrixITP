#include "LocalReactionProcess.h"
#include "ArtrixITP.h"

void Reaction::input(String inputRule) {

  int splitLocation = inputRule.indexOf(this->seperator);

  this->condition = inputRule.substring(0, splitLocation);
  this->reaction = inputRule.substring(splitLocation + 1);

  this->inited = true;

}

String Reaction::getCondition() {

  if (this->inited)return this->condition;
  else return "NOT INITED";

}

String Reaction::getReaction() {

  if (this->inited)return this->reaction;
  else return "NOT INITED";

}

long long reactionLastCheck = 0;
int reactionReconnectCount = 0;

String ArtrixITP::getReactionsResponse() {

  String result = "";
  bool startRead = false;
  reactionClient.setTimeout(1000);

  while (this->reactionClient.available()) {    // If meet the $, start read.

    char read = this->reactionClient.read();
    if (startRead)result += read;
    if (read == '$')startRead = true;

  }

  if (!this->reactionClient.connected()) {
    if (!this->reactionClient.connect(reactionHost, reactionPort)) {

      Serial.println(F("reactionServer:Failed!"));

      reactionReconnectCount++;                                                             // Restart ESP8266 when stucked
      if (reactionReconnectCount >= 3)this->restartESP();

      return "FAILED";
    }
    reactionReconnectCount = 0;
  }

  String url = "/reactions/";
  url += this->DEVICE_ID;

  this->reactionClient.print(String("GET ") + url + " HTTP/1.1\r\n" +
                             "Host: " + reactionHost + "\r\n" +
                             "Connection: close\r\n\r\n");


  return result;

}


void ArtrixITP::updateReactions() {

  if (millis() - reactionLastCheck > 7500) {

    int startTime = millis();
    Serial.println(F("      -----------------Start ReactionCheck---------------- "));
    Serial.println(F(""));
    Serial.println(F(""));

    String response = this->getReactionsResponse();
    MultiReactions reacts(response);

    /*
      Serial.println(response);
      Serial.println("");
    */

    int doCount = reacts.reactionsCount;
    this->reactionsCount = reacts.reactionsCount;

    while (doCount) {

      int nowIndex = reacts.reactionsCount - doCount;

      Reaction r;
      r.input(reacts.reactions[nowIndex]);
      this->reactions[nowIndex] = r;
      Serial.print(F("    [Get]"));
      Serial.println(reacts.reactions[nowIndex]);

      doCount--;
    }


    Serial.println("");
    Serial.print(F("      -----------------END ReactionCheck Time:"));
    Serial.print(millis() - startTime);
    Serial.println(F("---------------- "));

    reactionLastCheck = millis();
  }
}

Reaction ArtrixITP::matchReactionByCondition(String condition) {

  for (int i = 0; i < this->reactionsCount; i++) {

    if (condition.equals(this->reactions[i].getCondition())) {

      Serial.print(F("---------------------Matched!!"));
      Serial.println(this->reactions[i].getCondition());

      return this->reactions[i];
      //this->send433(this->reactions[i].getReaction());

    }

  }

  Reaction empty;
  return empty;

}

