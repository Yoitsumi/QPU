#pragma once

class Processor;

class ConsoleDevice {
private:
	Processor& proc;
	int writePort;
	int readPort;

public:
	ConsoleDevice(Processor& p, int w, int r);
	~ConsoleDevice();

	void run();
};

