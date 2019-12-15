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

  Serial.println("433Initing");
  this->getSerial433();
  delay(3000);
  Serial.println("433Inited");

}

String ArtrixITP::getSerial433() {

  String strRecv = "";

  //Ensure the serial is opened
  if (!Serial433)this->Serial433.begin(9600);
  while (!Serial433);

  while (this->Serial433.available() > 0) {
    strRecv += char(this->Serial433.read());
    delay(1);
  }

  strRecv.replace("\n", "");
  return strRecv;

}

void ArtrixITP::check433()
{

  if (this->inited) {

    //Set the 433Serial to listing mode
    //this->Serial433.listen();
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

        Serial.print("  [Multi]NowCommand:");
        Serial.println(cmds.commands[cmds.cmdCount - doCount]);

        Command command(cmds.commands[cmds.cmdCount - doCount]);

        String commandName = command.getCommandName();

        //Based on the connection, handle other commands
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
  
  if (!Serial433)this->Serial433.begin(9600);
  while (!Serial433);

  Serial.println(Serial433);
  this->Serial433.println("asdasdasd");
  
  if (this->inited) this->Serial433.print(message);
  delay(random(5, 30));
}

void ArtrixITP::CLIaliveStateUpdate()                                  //To update the online state by the property "lastAlive"  (This Function is for Client)
{

  int aliveThreshold = 9000; //Millisecond
  if (this->handShaked) {
    if (millis() - this->lastAliveCheck > aliveThreshold) {
      Serial.println("[Server Offline]The server is offline");
      //digitalWrite(13, LOW);
      this->handShaked = false;
    } else {
      //digitalWrite(13, HIGH);
      Serial.println("[Server Online]The server is online");
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

  }

}
