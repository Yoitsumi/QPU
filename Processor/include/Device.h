#pragma once

struct DeviceData {
	const unsigned int MID;
	const unsigned int PID;
	unsigned int address;
	unsigned int status;
	unsigned int INTCODE;
	unsigned int customData;
};

class Device {
public:
	Device(unsigned int MID, unsigned int PID);
	virtual ~Device();

	DeviceData data;
};

