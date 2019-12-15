#include "ArtrixITP.h"
#include <MemoryFree.h>

ArtrixITP::ArtrixITP(String inputDeviceID): Serial433(14, 12, false, 4096) {   //If using the NodeMCU Board, replace with this line.
  //ArtrixITP::ArtrixITP(String inputDeviceID): Serial433(11, 10) {   //If using the Arduino Board, replace with this line.

  Serial.begin(230400);

  while (!Serial) ;

  this->DEVICE_ID = inputDeviceID;

  randomSeed(analogRead(0));

  String temp_ID = "";
  for (int i = 0; i < 3; i++)
    temp_ID += inputDeviceID[i];
  if (temp_ID == "SER")
    this->DEVICE_TYPE = "SERVER";
  else if (temp_ID == "CLI")
    this->DEVICE_TYPE = "CLIENT";
  else
    this->DEVICE_TYPE = "UNKNOWN";

  Serial.println(DEVICE_TYPE);
  Serial.print("DEVTYPE:");
  Serial.println(DEVICE_TYPE);

  this->devPool.deviceCount = 0;
  this->getSerial433();
  this->inited = true;

  delay(1000);

}

void ArtrixITP::checkControlSerial() {

  String strRecv = "";

  if (!Serial)Serial.begin(230400);

  while (!Serial);

  while (Serial.available() > 0) {
    strRecv += char(Serial.read());
    delay(2);
  }
  strRecv.replace("\n", "");

  if (strRecv == "NODEBUG")this->debug = false;
  if (strRecv == "NOWIFIDEBUG")this->wifiDebug = false;
  if (strRecv == "NOSERIALDEBUG")this->net433Debug = false;
  if (strRecv == "NOONLYSENSOR")this->onlySensorDebug = false;

  if (strRecv == "DEBUG")this->debug = true;
  if (strRecv == "WIFIDEBUG")this->wifiDebug = true;
  if (strRecv == "SERIALDEBUG")this->net433Debug = true;
  if (strRecv == "ONLYSENSOR")this->onlySensorDebug = true;

}

String ArtrixITP::getSerial433() {

  String strRecv = "";

  if (!Serial433) {
    this->Serial433.enableIntTx(false);
    this->Serial433.begin(4800);
  }
  while (!Serial433);

  while (this->Serial433.available() > 0) {
    strRecv += char(this->Serial433.read());
    delay(2);
  }
  strRecv.replace("\n", "");

  return strRecv;

}

void ArtrixITP::processAllMessage()
{

  if (this->inited) {

    String WTReturn ;

    WTReturn = getSerial433();                                                                  // Receiving the message from 433MHz Module's Serial

    while (!this->wifiDownlinkPool.empty()) {                                                      // Receiving the message from central server
      Message tmpMsg = this->wifiDownlinkPool.get();
      WTReturn += tmpMsg.data;
    }

    //---------------------------------------------------------------Data Processing--------------------------------------------------------------

    if (!WTReturn.length() == 0)
    {

      Serial.print('[');
      Serial.print(this->DEVICE_ID);
      Serial.print("]GET:");
      Serial.println(WTReturn);


      MultiCommand cmds(WTReturn);

      if (this->debug && this->net433Debug && !this->onlySensorDebug) {
        Serial.print("  [Multi]Got Command Count:");
        Serial.println(cmds.cmdCount);
      }

      int doCount = cmds.cmdCount;

      while (doCount) {

        if (!onlySensorDebug) {
          Serial.print("    [Multi]NowCommand:");
          Serial.println(cmds.commands[cmds.cmdCount - doCount]);
        }

        Command command(cmds.commands[cmds.cmdCount - doCount]);

        String commandName = command.getCommandName();
        /*
        if (!command.getFlag() == "S" && !commandName=="REGDEV") {
          String reply = "ACKED|";
          reply += command.deriveMsg;
          this->send433(reply);
        }
      */
        //Based on the connection, handle other commands

        if (command.getFlag() == "S" && this->DEVICE_TYPE == "SERVER") {

          if (commandName == "DOWNLINK")SER_DOWNLINK(command, true);                                                  //TODO:Delete the debug  mode

        }

        //If the message is send to the main Server.
        if (command.getFlag() == "U" && this->DEVICE_TYPE == "SERVER") {

          //This part is for functions to handle the commands.
          if (commandName == "SETPWR")SER_SETPWR(command, debug);
          if (commandName == "REGDEV")SER_REGDEV(command, debug);
          if (commandName == "ALIVE")SER_ALIVE(command, debug);
          if (commandName == "UPDSENSOR")SER_UPDSENSOR(command, true);

        }

        //If the message is send to this Client.
        if (command.getFlag() == "D" && this->DEVICE_TYPE == "CLIENT" && this->DEVICE_ID == command.getTargetDevice()) {

          //This part is for functions to handle the commands.
          if (command.getCommandName() == "SETPWR")CLI_SETPWR(command, debug);
          if (command.getCommandName() == "ALIVE")CLI_ALIVE(command);

        }

        // If not handshaked, do Handshake Check  (Only For Client)
        if (!handShaked) {

          //For Client
          if (command.getFlag() == "D" && this->DEVICE_TYPE == "CLIENT") {

            if (command.getCommandName() == "REGDEV")CLI_REGDEV(command);

          }

        }

        doCount--;

      }

    }
    //---------------------------------------------------------------RECEIVE HANDLING--------------------------------------------------------------

  }

}

void ArtrixITP::send433(String message)
{

  delay(random(4, 15));
  if (this->inited) this->Serial433.print(message);
  this->Serial433.flush();
  delay(random(4, 15));

}


void ArtrixITP::SEND_ALIVE(String targetDeviceID) {                   //A function to send an ALIVE command to the device in the pool

  String msg = "D,ALIVE,";
  msg += targetDeviceID;
  msg += ",END|";

  this->send433(msg);

  delay(random(10, 50));

}

void ArtrixITP::SERaliveRequest433()                                     //A function to iterate all devices in the pool and access SEND_ALIVE(DEVICE_ID) to send ALIVE command
{

  int checkDelay = random(2500, 4500); //Millisecond

  if (millis() - this->lastAliveCheck > checkDelay) {

    //--//Serial.print('[');
    //--//Serial.print(this->DEVICE_ID);
    //--//Serial.println("]ALIVECHECK");

    for (int i = 0; i < this->devPool.deviceCount; i++) SEND_ALIVE(this->devPool.allDevice[i].DEVICE_ID);
    this->lastAliveCheck = millis();

  }
}

void ArtrixITP::SERaliveStateUpdate()                                    //To update the online state by the property "lastAlive"  (This Function is for Server)
{
  for (int i = 0; i < this->devPool.deviceCount; i++) {

    int aliveThreshold = 9000; //Millisecond
    if (this->devPool.allDevice[i].isOnline) {
      if (millis() - this->devPool.allDevice[i].lastAlive > aliveThreshold) {
        Serial.print("[Offline]Device ");
        Serial.println(this->devPool.allDevice[i].DEVICE_ID);
        this->devPool.allDevice[i].isOnline = false;
      }
    }
  }
}


void ArtrixITP::CLIaliveStateUpdate()                                  //To update the online state by the property "lastAlive"  (This Function is for Client)
{

  int aliveThreshold = 9000; //Millisecond
  if (this->handShaked) {
    if (millis() - this->lastAliveCheck > aliveThreshold) {
      Serial.println("[Server Offline]The server is offline");
      digitalWrite(13, LOW);
      this->handShaked = false;
    } else {
      digitalWrite(13, HIGH);
      Serial.println("[Server Online]The server is online");
    }
  }

}

void ArtrixITP::checkWIFI() {

  this->connectWIFI();
  this->connectServer();

  String resp = this->getWIFIResponse();                                                        // Check the acknowledgement from the server.
  String anti; // Anticipation of receiving message


  if (!resp.equals("FALSE")) {
    anti.concat(this->messageID);
    anti += "-";
    anti += this->lastSentMessage.data;

    resp.replace("|", "");
    anti.replace("|", "");

    resp.replace(" ", "");
    anti.replace(" ", "");

    resp.replace("\n", "");
    anti.replace("\n", "");

    resp.trim();
    anti.trim();

    if (resp.length()) {

      Serial.print("[WIFI-Rx]:");
      Serial.println(resp);

      if (resp.startsWith("##ACKRESPONSE##")) {                                                               // Ack Response

        resp.replace("##ACKRESPONSE##", "");

        if (this->debug && this->wifiDebug && this->serverTransmittingDebug && !this->onlySensorDebug) {

          Serial.print("    [Received]:");
          Serial.print(resp);
          Serial.print("    Length=");
          Serial.println(resp.length());

          Serial.print("    [Anticipating]");
          Serial.print(anti);
          Serial.print("    Length=");
          Serial.println(anti.length());

        }

        if (resp.equals(anti)) {
          //--//Serial.print("    [Acked MessageID=");
          //--//Serial.print(this -> messageID);
          //--//Serial.print("]TimeCost(MilliSecond):");
          //--//Serial.println(millis() - this->lastSentMessage.lastSentTry);
          this->lastSentMessage.sentSucceed = true;
        }

      }

      if (resp.startsWith("##DOWNLINK##")) {                                                              // Downlink Data

        resp.replace("##DOWNLINK##", "");
        resp += '|';
        Serial.print("[WIFI-Rx]Get Downlink:");
        Serial.println(resp);
        Message msg;
        msg.data = resp;

        this->wifiDownlinkPool.append(msg);

      }

    }

  }

  if (this->messageID > 9999)this->messageID = 0;

  if (!this->msgPool.empty())if (this->lastSentMessage.sentSucceed) {                         // Get a new message from the pool

      this->lastSentMessage = this->msgPool.get();
      this->messageID++;

      if (this->debug && this->wifiDebug && !this->onlySensorDebug) {
        Serial.print("[WIFI-Pool]GetNewMSG:");
        Serial.println(this->lastSentMessage.data);
      }

    }

  if (!this->lastSentMessage.sentSucceed) {                                                   // Judge for two times to increase the efficiency

    int thres = 2200;
    if (millis() - this->lastSentMessage.lastSentTry > thres) {                                     // This data is gonna be set for retry
      this->lastSentMessage.lastSentTry = 0;
      this->lastSentMessage.tryCount++;

      if (this->debug && this->wifiDebug && this->serverTransmittingDebug && !this->onlySensorDebug) {
        Serial.print("    [WIFI-Tx]MSG:SendPreparing...Try count:");
        Serial.println(this->lastSentMessage.tryCount);
      }

    }

    int thres2 = 3; // If retry time exceeded this threshold, reconnect the Server
    if (lastSentMessage.lastSentTry == 0) {                                                   // Including this msg havn't been sent yet or the msg is gonna be resent,totally two situations.

      if (this->debug && this->wifiDebug && this->serverTransmittingDebug) {
        Serial.println("    [WIFI-Tx]MSG:Check Layer...");
      }

      if (lastSentMessage.tryCount > thres2)this->forceReconnectServer();
      else {

        this->lastSentMessage.lastSentTry = millis();
        String send;
        send.concat(this->messageID);
        send += "-";
        send += this->lastSentMessage.data;
        send += "|";
        send.trim();

        //--//Serial.print("    [WIFI-MSG]MSG:Now Sending:");
        //--//Serial.println(send);
        this->wifiClient.print(send);

      }

    }

    int thres3 = 5; // Limit of trashing this jamed message
    if (lastSentMessage.tryCount > thres3)this->lastSentMessage.sentSucceed = true;

  }

}

void ArtrixITP::reportDeviceState() {

  if (millis() - this->lastReport > reportIntervalThreshold) {

    this->lastReport = millis();

    String msg = "REPORTDEVICE,";
    msg += this->DEVICE_ID;
    msg += ",";

    for (int i = 0; i < this->devPool.deviceCount; i++) {

      if (this->devPool.allDevice[i].isOnline) {
        msg += this->devPool.allDevice[i].DEVICE_ID;
        msg += ",";
      }

    }

    //--//Serial.print("[Server-Report]:");
    //--//Serial.println(msg);
    this->sendViaWIFI(msg);

  }

}

void ArtrixITP::checkAll()                                               //Check all communiting ways, this function is a base function.
{

  if (this->inited) {

    this->processAllMessage();
    this->checkWIFI();
    this->checkControlSerial();
    this->reportDeviceState();

    //Client
    if (!handShaked && this->DEVICE_TYPE == "CLIENT")CLIhandShake();           //Hand shake (IF THIS DEVICE IS A CLIENT)
    if (this->DEVICE_TYPE == "CLIENT")this->CLIaliveStateUpdate();             //Server Alive State Update

    //Server
    if (this->DEVICE_TYPE == "SERVER") this->SERaliveStateUpdate();            //Alive State Update
    if (this->DEVICE_TYPE == "SERVER")this->SERaliveRequest433();              //Send ALIVE command to request response

  }

}
