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
    String paras[8];

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
    String commands[8];

  private:
    String innerSplit(int index);
    int calcCommandCount();

    //Put the paragrams buffer into the private part to avoid illegal access.

};

//---------------------Those function are for multi-command spliting---------------



#endif
