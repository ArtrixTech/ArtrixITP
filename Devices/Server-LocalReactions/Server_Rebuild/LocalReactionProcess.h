#ifndef Reaction_h
#define Reaction_h

#include "Arduino.h"
#include "StringProcess.h"

class Reaction {
  public:

    bool inited = false;

    /*
    Reaction() {};
    Reaction(String inputRule);
    */

    void input(String inputRule);

    String getCondition();
    String getReaction();

  private:

    char seperator = '>';
    String condition = "", reaction = "";

};
#endif
