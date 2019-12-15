#include "ServerProcess.h"
#include "DevicePool.h"

void ArtrixITP::SER_REGDEV(Command cmd, bool isDebug) {

  Serial.print("    [REGDEV]DeriveMSG=");
  Serial.println(cmd.deriveMsg);

  String msg = "D,";
  msg += cmd.getCommandName();
  msg += ",";
  msg += cmd.getTargetDevice();
  msg += ",";
  msg += this->DEVICE_ID;
  msg += ",OK,END|";

  if (isDebug) {
    Serial.print("    [REGDEV]Send:");
    Serial.println(msg);
    Serial.println("    [REGDEV]Succeed");
  }

  //If the device have connected this Server before
  if (this->devPool.deviceExist(cmd.getTargetDevice())) {
    this->devPool.allDevice[this->devPool.getDeviceByID(cmd.getTargetDevice())].lastAlive = millis();
  }
  else {
    DevicePool::Device thisDevice;
    thisDevice.DEVICE_ID = cmd.getTargetDevice();
    thisDevice.isOnline = true;
    thisDevice.lastAlive = millis();

    this->devPool.append(thisDevice);
  }

  if (isDebug && ! this->onlySensorDebug) {
    Serial.print("    [DeviceCount]");
    Serial.println(this->devPool.deviceCount);
  }

  this->send433(msg);
}


void ArtrixITP::SER_ALIVE(Command cmd, bool isDebug) {

  if (this->devPool.deviceExist(cmd.getTargetDevice())) {
    int ID = this->devPool.getDeviceByID(cmd.getTargetDevice());
    this->devPool.allDevice[ID].isOnline = true;
    this->devPool.allDevice[ID].lastAlive = millis();

    if (isDebug) {
      Serial.print("    [Alive]Device=");
      Serial.println(this->devPool.allDevice[ID].DEVICE_ID);
    }

  }

}


