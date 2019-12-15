#include "StringProcess.h"

Command::Command(String message)
{
  this->deriveMsg = message;
  this->parasCount = this->calcSepCount();

  for (int i = 0; i < this->parasCount; i++)this->paras[i] = this->innerSplit(i);
  inited = true;
}

int Command::calcSepCount()
{
  int count = 0;
  for (int i = 0; i < this->deriveMsg.length(); i++)
  {
    if (this->deriveMsg[i] == this->seperator)
    {
      count++;
    }
  }
  return count;
}

String Command::getFlag()
{
  if (this->inited)return this->paras[0];
  else return "ERROR";
}

String Command::getCommandName()
{
  if (this->inited)return this->paras[1];
  else return "ERROR";
}

String Command::getTargetDevice()
{
  if (this->inited)return this->paras[2];
  else return "ERROR";
}

String Command::getPara(int index)
{
  if (this->inited) {
    if (index < this->parasCount) {
      return this->paras[index];
    }
    else {
      return "ERROR";
    }
  }
  else return "ERROR";
}

String Command::innerSplit(int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = this->deriveMsg.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (this->deriveMsg.charAt(i) == this->seperator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? this->deriveMsg.substring(strIndex[0], strIndex[1]) : "";
}

//-------------------------------------------Downside for command spliting------------------------------------

MultiCommand::MultiCommand(String message)
{
  this->deriveMsg = message;
  this->cmdCount = this->calcCommandCount();

  for (int i = 0; i < this->cmdCount; i++)this->commands[i] = this->innerSplit(i);
  inited = true;
}


String MultiCommand::innerSplit(int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = this->deriveMsg.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (this->deriveMsg.charAt(i) == this->seperator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? this->deriveMsg.substring(strIndex[0], strIndex[1]) : "";
}


int MultiCommand::calcCommandCount()
{
  int count = 0;
  char seperator = '|';

  for (int i = 0; i < this->deriveMsg.length(); i++)
  {
    if (this->deriveMsg[i] == seperator)
    {
      count++;
    }
  }
  return count;
}

String MultiCommand::getCommand(int index) {
  return this->commands[index];
}



void MultiCommand::prioritySort(String commandName, int argumentMatchIndex1, String anticipatingArgumentMatchResult1) {  // Overrride!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!-----------------------

  int priCount = 0;

  for (int i = 0; i < this->cmdCount; i++) {                            // Count the quantity of matched priority messages

    Command cmd(this->getCommand(i));
    if (cmd.getCommandName().equals(commandName) && cmd.getPara(argumentMatchIndex1) == anticipatingArgumentMatchResult1)
      priCount++;

  }

  if (priCount) {

    String priorityCommands[priCount];
    int priorityIndex[priCount];
    int iterIndex = 0;

    for (int i = 0; i < this->cmdCount; i++) {                              // Get all priority command's index

      Command cmd(this->getCommand(i));
      if (cmd.getCommandName().equals(commandName) && cmd.getPara(argumentMatchIndex1) == anticipatingArgumentMatchResult1) {
        priorityIndex[iterIndex] = i;
        priorityCommands[iterIndex] = cmd.deriveMsg;
        Serial.print("Matched Priority:");
        Serial.println(cmd.deriveMsg);
        iterIndex++;
      }

    }

    for (int i = 0; i < priCount; i++) {                              // Replace those commands to the head
      String tempCmd = this->commands[i];
      this->commands[i] = this->commands[priorityIndex[0]];
      this->commands[priorityIndex[0]] = tempCmd;
    }

  }
}                                                    // Overrride!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!-----------------------


void MultiCommand::prioritySort(String commandName) {

  int priCount = 0;

  for (int i = 0; i < this->cmdCount; i++) {                            // Count the quantity of matched priority messages

    Command cmd(this->getCommand(i));
    if (cmd.getCommandName().equals(commandName))priCount++;

  }

  if (priCount) {

    String priorityCommands[priCount];
    int priorityIndex[priCount];
    int iterIndex = 0;

    for (int i = 0; i < this->cmdCount; i++) {                              // Get all priority command's index

      Command cmd(this->getCommand(i));
      if (cmd.getCommandName().equals(commandName)) {
        priorityIndex[iterIndex] = i;
        priorityCommands[iterIndex] = cmd.deriveMsg;
        iterIndex++;
      }

    }

    for (int i = 0; i < priCount; i++) {                              // Replace those commands to the head
      String tempCmd = this->commands[i];
      this->commands[i] = this->commands[priorityIndex[0]];
      this->commands[priorityIndex[0]] = tempCmd;
    }

  }
}

//-------------------------------------------Downside for reactions spliting------------------------------------

MultiReactions::MultiReactions(String message)
{

  this->deriveMsg = message;
  this->reactionsCount = this->calcReactionCount();

  for (int i = 0; i < this->reactionsCount; i++) {
    this->reactions[i] = this->innerSplit(i);
    this->reactions[i] .replace("#", "");
  }
  inited = true;

}


String MultiReactions::innerSplit(int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = this->deriveMsg.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (this->deriveMsg.charAt(i) == this->seperator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? this->deriveMsg.substring(strIndex[0], strIndex[1]) : "";
}


int MultiReactions::calcReactionCount()
{
  int count = 0;

  for (int i = 0; i < this->deriveMsg.length(); i++)
  {
    if (this->deriveMsg[i] == this->seperator)
    {
      count++;
    }
  }
  return count;
}

