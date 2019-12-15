#ifndef ArtrixITP_h
#define ArtrixITP_h

#include "Arduino.h"
#include <SoftwareSerial.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include "StringProcess.h"
#include "DevicePool.h"
#include "MessagePool.h"
#include "LocalReactionProcess.h"

typedef void (*RecallFunction)(Command , bool );
class ArtrixITP
{
  public:

    void(* restartESP) (void) = 0;

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

    //-----------------------------Local Reactions--------------------------------

    void updateReactions();// Port = 57927
    String getReactionsResponse();

    WiFiClient reactionClient;
    //const int reactionPort = 57927;
    const int reactionPort = 30126;
    //const int reactionPort = 5000;

    //const char* reactionHost = "118.89.25.199";
    const char* reactionHost = "iot.rapi.link";

    int reactionsCount = 0;
    int reactionsMax = 6;
    Reaction reactions[6];

    Reaction matchReactionByCondition(String condition);

    //-----------------------------Local Reactions--------------------------------

    //------------------------------WIFI Functions-------------------------------
    bool connectWIFI();
    bool connectServer();
    bool forceReconnectServer();

    void sendViaWIFI(String data);
    void prioritySendViaWIFI(String data);

    void reportDeviceState();
    long long lastReport = 0;
    int reportIntervalThreshold = 4000;     // report device state per 5 seconds

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
