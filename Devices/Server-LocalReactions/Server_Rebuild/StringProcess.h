#ifndef StringProcess_h
#define StringProcess_h

#include "Arduino.h"

class Command
{
  public:
    bool inited = false;;
    String deriveMsg;
    int parasCount;
    char seperator = ',';

    Command(String message);
    String getFlag();
    String getCommandName();
    String getTargetDevice();

    //Access all the paragrams in this function.
    String getPara(int index);
    String paras[12];

  private:
    int calcSepCount();
    String innerSplit(int index);

    //Put the paragrams buffer into the private part to avoid illegal access.

};


class MultiCommand
{
  public:
    bool inited = false;;
    String deriveMsg;
    int cmdCount;
    char seperator = '|';

    MultiCommand(String message);

    //Access all the paragrams in this function.
    //Maximium Command Count = 5
    String getCommand(int index);
    String commands[15];
    
    void prioritySort(String commandName);  // Resort low-latency-accquired commands to the priority pool head
    void prioritySort(String commandName, int argumentMatchIndex1, String anticipatingArgumentMatchResult1);  // Override version, second-layer match added

  private:
    String innerSplit(int index);
    int calcCommandCount();

    //Put the paragrams buffer into the private part to avoid illegal access.

};

class MultiReactions
{
  public:
    bool inited = false;;
    String deriveMsg;
    int reactionsCount;
    char seperator = '#';

    MultiReactions(String message);

    //Access all the paragrams in this function.
    //Maximium Command Count = 5
    String getReaction(int index);
    int maxReactions = 10;
    String reactions[10];

  private:
    String innerSplit(int index);
    int calcReactionCount();

    //Put the paragrams buffer into the private part to avoid illegal access.

};

//---------------------Those function are for multi-command spliting---------------



#endif
