#ifndef MessagePool_h
#define MessagePool_h

#include "Arduino.h"

class Message {

  public:

    String data;
    int lastSentTry = 0;
    int tryCount = 0;

    bool sentSucceed = false;

};

class MessagePool {

  public:

    int maxMsgs = 50;
    Message allMsg[50];

    void append(Message inMessage);
    void priorityAppend(Message inMessage);
    bool empty() {
      if (this->msgCount == 0)return true;
      else return false;
    };
    void pop();
    Message get();

    int msgCount = 0;

  private:
    int rearIndex = 0;

};
#endif
