#ifndef ListProcess_h
#define ListProcess_h

#include "Arduino.h"

/*
 * 
 * How to access devices in the pool:
 * 1.Check if the device in the pool by DEVICE_ID (deviceExist)
 * 2.Use getDeviceByID(DEVICE_ID) to get the innerID of the target device
 * 3.Access this->allDevice[innerID] to access the device
 * 
 */

class DevicePool {

  public:

    //---------------------------DeviceClass-----------------------
    class Device {

      public:
        //innerID for inner recognizating, DEVICE_ID for transmiting.
        int innerID;
        String DEVICE_ID;
        bool isOnline;

        int lastAlive;
    };
    //---------------------------DeviceClass-----------------------

    //-------------------------------------------
    //| Connected Devices(Only For Server Use)  |
    //| TODO:Optimize the RAM usage             |
    //| Now limited to 8 Devices for one Server |
    //-------------------------------------------
    Device allDevice[1];
    int deviceCount;

    int getDeviceByID(String DEVICE_ID);
    bool deviceExist(String DEVICE_ID);

    void append(Device inDevice);
};
#endif
