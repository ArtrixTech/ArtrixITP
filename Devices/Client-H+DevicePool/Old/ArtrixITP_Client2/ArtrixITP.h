#ifndef ArtrixITP_h
#define ArtrixITP_h

#include "Arduino.h"
#include <SoftwareSerial.h>
#include "StringProcess.h"

typedef void (*RecallFunction)(Command );
class ArtrixITP
{
  public:

    //Hardware definations
    SoftwareSerial Serial433;

    ArtrixITP(String DEVICE_ID);
    ArtrixITP(): Serial433(10, 11) {};

    bool inited = false;
    bool handShaked = false;

    String DEVICE_ID;
    String DEVICE_TYPE; //Types:SERVER/CLIENT

    //Base checking functions
    bool start433();
    void check433();
    void send433(String message);

    //-----------------------------Command Register-------------------------------
    //SETPWR Recall
    RecallFunction SER_SETPWR, CLI_SETPWR;
    void bindSETPWRRecall(RecallFunction func) {
      if (this->DEVICE_TYPE == "CLIENT")CLI_SETPWR = func;
    }
    //-----------------------------Command Register-------------------------------

    //Inner Functions

    void CLI_REGDEV(Command cmd);
    void CLI_ALIVE(Command cmd);

    void CLIaliveStateUpdate();
    void CLIhandShake();

    long lastAliveCheck;//Saved in milisecond
    void SEND_ALIVE(String targetDeviceID);//433 Heart Beat Pack Request
    void SERaliveRequest433();//433 Heart Beat Pack Request

    void checkAll();//A total function to do all checklist

  private:
    String getSerial433();
};
#endif
