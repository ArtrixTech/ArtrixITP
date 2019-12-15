#include "ArtrixITP.h"
#include <MemoryFree.h>

ArtrixITP::ArtrixITP(String inputDeviceID): Serial433(10, 11) {

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

  Serial.print("DEVTYPE:");
  Serial.println(DEVICE_TYPE);

  this->inited = true;
  this->devPool.deviceCount = 0;

  Serial.println("433Initing");
  delay(1000);
  Serial.println("433Inited");

}

String ArtrixITP::getSerial433() {
  String strRecv = "";

  //Ensure the serial is opened
  if (!Serial433.isListening())this->Serial433.begin(9600);

  while (this->Serial433.available() > 0) {
    strRecv += char(this->Serial433.read());
    delay(2);
  }
  strRecv.replace("\n", "");
  return strRecv;

}

void ArtrixITP::check433()
{

  if (this->inited) {

    //Set the 433Serial to listing mode
    this->Serial433.listen();
    String WTReturn = getSerial433();

    //---------------------------------------------------------------RECEIVE HANDLING--------------------------------------------------------------

    if (!WTReturn.length() == 0)
    {

      Serial.print("[Before]Freememory:");
      Serial.println(freeMemory());

      Serial.print('[');
      Serial.print(this->DEVICE_ID);
      Serial.print("]GET:");
      Serial.println(WTReturn);

      MultiCommand cmds(WTReturn);

      Serial.print("  [Multi]Got Command Count:");
      Serial.println(cmds.cmdCount);

      int doCount = cmds.cmdCount;

      while (doCount) {

        Command command(cmds.commands[cmds.cmdCount - doCount]);

        String commandName = command.getCommandName();

        if (command.getFlag() == "D" && this->DEVICE_TYPE == "CLIENT" && this->DEVICE_ID == command.getTargetDevice()) {
          Serial.print("  [Multi]NowCommand:");
          Serial.println(cmds.commands[cmds.cmdCount - doCount]);
        }

        //Based on the connection, handle other commands

        //If the message is send to the main Server.
        if (command.getFlag() == "U" && this->DEVICE_TYPE == "SERVER") {

          //This part is for functions to handle the commands.
          if (commandName == "SETPWR")SER_SETPWR(command);
          if (commandName == "REGDEV")SER_REGDEV(command);
          if (commandName == "ALIVE")SER_ALIVE(command);

        }

        //If the message is send to this Client.
        if (command.getFlag() == "D" && this->DEVICE_TYPE == "CLIENT" && this->DEVICE_ID == command.getTargetDevice()) {

          //This part is for functions to handle the commands.
          if (command.getCommandName() == "SETPWR")CLI_SETPWR(command);
          if (command.getCommandName() == "ALIVE")CLI_ALIVE(command);

        }

        // If not handshaked, do Handshake Check  (Only For Client)
        if (!handShaked) {

          //For Client
          if (command.getFlag() == "D" && this->DEVICE_TYPE == "CLIENT") {

            if (command.getCommandName() == "REGDEV")CLI_REGDEV(command);

          }

        }

        Serial.print("[After]Freememory:");
        Serial.println(freeMemory());

        doCount--;

      }

    }
    //---------------------------------------------------------------RECEIVE HANDLING--------------------------------------------------------------

  }

}

void ArtrixITP::send433(String message)
{

  if (this->inited) this->Serial433.print(message);
  this->Serial433.flush();
  delay(random(4, 32));

}


void ArtrixITP::SEND_ALIVE(String targetDeviceID) {                   //A function to send an ALIVE command to the device in the pool

  String msg = "D,ALIVE,";
  msg += targetDeviceID;
  msg += ",END|";

  this->send433(msg);

  //delay(30);
  delay(random(20, 50));

}

void ArtrixITP::SERaliveRequest433()                                     //A function to iterate all devices in the pool and access SEND_ALIVE(DEVICE_ID) to send ALIVE command
{

  int checkDelay = 2500; //Millisecond

  if (millis() - this->lastAliveCheck > checkDelay) {

    Serial.print('[');
    Serial.print(this->DEVICE_ID);
    Serial.println("]ALIVECHECK");

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
        Serial.print("    [Offline]Device ");
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
      //Serial.println("[Server Offline]The server is offline");
      //digitalWrite(13, LOW);
      this->handShaked = false;
    } else {
      //digitalWrite(13, HIGH);
      //Serial.println("[Server Online]The server is online");
    }
  }

}


void ArtrixITP::checkAll()                                               //Check all communiting ways, this function is a base function.
{

  if (this->inited) {

    this->check433();

    //Client
    if (!handShaked && this->DEVICE_TYPE == "CLIENT")CLIhandShake();           //Hand shake (IF THIS DEVICE IS A CLIENT)
    if (this->DEVICE_TYPE == "CLIENT")this->CLIaliveStateUpdate();             //Server Alive State Update

    //Server
    if (this->DEVICE_TYPE == "SERVER") this->SERaliveStateUpdate();            //Alive State Update
    if (this->DEVICE_TYPE == "SERVER")this->SERaliveRequest433();              //Send ALIVE command to request response

  }

}
