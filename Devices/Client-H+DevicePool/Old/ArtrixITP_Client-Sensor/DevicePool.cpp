#include "DevicePool.h"

bool DevicePool::deviceExist(String DEVICE_ID) {

  for (int i = 0; i < this->deviceCount; i++) if (this->allDevice[i].DEVICE_ID == DEVICE_ID)return true;
  return false;

}


int DevicePool::getDeviceByID(String DEVICE_ID) {

  for (int i = 0; i < this->deviceCount; i++) if (this->allDevice[i].DEVICE_ID == DEVICE_ID)return i;
  return -1;

}

void DevicePool::append(Device inDevice) {

  inDevice.innerID = this->deviceCount;
  this->allDevice[inDevice.innerID] = inDevice;
  this->deviceCount++;

}

