#ifndef ArtrixITP_h
#define ArtrixITP_h

#include "Arduino.h"
#include <SoftwareSerial.h>
#include <WiFiClientSecure.h>
#include "StringProcess.h"
#include "DevicePool.h"
#include "MessagePool.h"

typedef void (*RecallFunction)(Command , bool );
class ArtrixITP
{
  public:

    //Hardware definations
    SoftwareSerial Serial433;
    WiFiClient wifiClient;

    ArtrixITP(String inputDeviceID);

    DevicePool devPool;

    bool inited = false;
    bool handShaked = false;
    bool wifiConnected = false;

    String DEVICE_ID;
    String DEVICE_TYPE; //Types:SERVER/CLIENT

    //433 checking functions
    bool start433();
    void processAllMessage();
    void send433(String message);

    //------------------------------WIFI Functions-------------------------------
    bool connectWIFI();
    bool connectServer();
    bool forceReconnectServer();

    void sendViaWIFI(String data);
    void prioritySendViaWIFI(String data);

    void reportDeviceState();
    long long lastReport = 0;
    int reportIntervalThreshold = 10000;     // report device state per 5 seconds

    String getWIFIResponse();
    void checkWIFI();


    Message lastSentMessage;
    MessagePool msgPool, wifiDownlinkPool;
    int messageID;


    //------------------------------WIFI Functions-------------------------------


    //-----------------------------Command Register-------------------------------

    //SETPWR Recall
    RecallFunction SER_SETPWR, CLI_SETPWR;
    void bindSETPWRRecall(RecallFunction func) {
      if (this->DEVICE_TYPE == "SERVER")SER_SETPWR = func;
      if (this->DEVICE_TYPE == "CLIENT")CLI_SETPWR = func;
    }

    //UPDSENSOR Recall
    RecallFunction SER_UPDSENSOR;
    void bindUPDSENSORRecall(RecallFunction func) {
      if (this->DEVICE_TYPE == "SERVER")SER_UPDSENSOR = func;
    }

    //DOWNLINK Recall
    RecallFunction SER_DOWNLINK;
    void bindDOWNLINKRecall(RecallFunction func) {
      if (this->DEVICE_TYPE == "SERVER")SER_DOWNLINK = func;
    }

    //-----------------------------Command Register-------------------------------

    //Inner Functions

    void SER_REGDEV(Command cmd, bool isDebug);
    void CLI_REGDEV(Command cmd);

    void SER_ALIVE(Command cmd, bool isDebug);
    void CLI_ALIVE(Command cmd);

    long long lastAliveCheck;//Saved in milisecond
    void SEND_ALIVE(String targetDeviceID);//433 Heart Beat Pack Request
    void SERaliveRequest433();//433 Heart Beat Pack Request

    void SERaliveStateUpdate();
    void CLIaliveStateUpdate();

    void CLIhandShake();

    void checkAll();//A total function to do all checklist
    String getSerial433();

    void checkControlSerial();

    //private:

  private:

    bool debug = true;
    bool wifiDebug = true;
    bool net433Debug = true;
    bool onlySensorDebug = false;

    bool serverTransmittingDebug = false;


};
#endif
