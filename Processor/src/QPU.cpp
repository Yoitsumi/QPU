// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "main.h"

#include <iostream>
#include <fstream>
#include <windows.h>
#include <thread>

#include "Processor.h"
#include "Opcodes.h"
#include "ConsoleDevice.h"

using namespace processor;
using namespace std;

int _tmain(int argc, _TCHAR* argv[]) {
	Processor proc = Processor();
	int pc = 0;
	
	/*
	proc.mem.byte[0] = 0x00;
	proc.mem.byte[1] = 0x11;
	proc.mem.byte[2] = 0x22;
	proc.mem.byte[3] = 0x33;
	cout << proc.mem.word[1] << endl;
	*/

	ifstream in;
	in.open("./test.bin", ios::in | ios::binary);
	if(!in.is_open()) {
		cout << "Oh noes!" << endl;
		system("pause");
		return 0;
	}
	in.seekg(0, ios::end);
	int size = in.tellg();
	char* buffer = new char[size];
	in.seekg(0);
	in.read(buffer, size);
	in.close();
	for(int i = 0; i < size; i++) {
		proc.ram.get()[i] = buffer[i];
	}
	delete buffer;

	ConsoleDevice console(proc, 0, 4);
	thread consthr(&ConsoleDevice::run, &console);
	while(!proc.broken)
		proc.step();
	for(int i = 0; i < 32; i++) {
		cout << "$" << i << ": " << proc.r[i] << endl;
	}
	consthr.join();
	system("pause");
}

