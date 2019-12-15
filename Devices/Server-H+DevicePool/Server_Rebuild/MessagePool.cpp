#include "MessagePool.h"

Message MessagePool::get() {

  Message rt = this->allMsg[0];
  this->pop();
  Serial.print("        [MSGPOOL]Msg Count:");
  Serial.println(this->msgCount);
  return rt;

}

void MessagePool::append(Message inMessage) {

  if (this->rearIndex < this->maxMsgs - 1) {
    this->allMsg[this->rearIndex + 1] = inMessage;
  } else {
    Serial.println("MSGPOOL Overloaded!");
    this->pop();
    this->allMsg[this->rearIndex + 1] = inMessage;
  }

  this->rearIndex++;
  this->msgCount = this->rearIndex + 1;

}

void MessagePool::priorityAppend(Message inMessage) {

  // Clone the current stack
  Message tempMsg[50] ;
  for (int i = 0; i < 50; i++)tempMsg[i] = this->allMsg[i];

  if (this->rearIndex < this->maxMsgs - 1) {

    this->allMsg[0] = inMessage;

  } else {

    Serial.println("MSGPOOL Overloaded!");
    for (int i = 0; i <= 48; i++) this->allMsg[i + 1] = tempMsg[i];
    this->allMsg[0] = inMessage;

  }

  this->rearIndex++;
  this->msgCount = this->rearIndex + 1;

}

void MessagePool::pop() {

  for (int i = 1; i <= this->rearIndex; i++) this->allMsg[i - 1] = this->allMsg[i];

  Message msgEmpty;
  this->allMsg[this->rearIndex] = msgEmpty;

  this->rearIndex--;
  this->msgCount = this->rearIndex + 1;

}




