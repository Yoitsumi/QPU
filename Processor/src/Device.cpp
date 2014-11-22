#include "..\include\Device.h"


Device::Device(unsigned int MID, unsigned int PID) : data({MID, PID, 0, 0, 0, 0}) {
}


Device::~Device() {
}
