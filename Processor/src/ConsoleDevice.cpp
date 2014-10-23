#include "..\include\ConsoleDevice.h"

#include <iostream>

#include "Processor.h"

ConsoleDevice::ConsoleDevice(Processor& p, int w, int r) : proc(p), writePort(w), readPort(r) {
	p.dev.get()[w] = 0;
	p.dev.get()[r] = 0;
}

ConsoleDevice::~ConsoleDevice() {
}

void ConsoleDevice::run() {
	while(!proc.broken) {
		if(proc.dev.get()[writePort] != 0) {
			std::cout << proc.dev.get()[writePort];
			proc.dev.get()[writePort] = 0;
		}
	}
}