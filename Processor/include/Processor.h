#include "Architecture.h"

#include <memory>

#include "InterruptQueue.h"
#include "AddressTranslation.h"

typedef unsigned int uint;

using namespace std;

#pragma once
class Processor
{
public:
	Processor();
	~Processor();

	class Registers{
	public:
		inline reg& operator[](int i){
			if (i == 0 || i > 31){
				vals[0] = 0;
				return vals[0];
			}
			else
				return vals[i];
		}
		inline const reg operator[](int i)const{
			if (i == 0 || i > 31){
				return 0;
			} else {
				return vals[i];
			}
		}
	private:
		reg vals[32];
	};

	class Memory {
		
		Processor& proc;

	public:
		Memory(Processor& p) : proc(p), byte(proc), half(proc), word(proc) {}

	private:
		class ByteAcc {
			Processor& proc;
		public:
			ByteAcc(Processor& p) : proc(p) {}

			inline char read(int addr) {
				return *((char*) memory::prepare(proc, memory::READ, addr));
			}

			inline char& write(int addr) {
				return (char&) *((char*) memory::prepare(proc, memory::WRITE, addr));
			}

			inline char exec(int addr) {
				return *((char*) memory::prepare(proc, memory::EXEC, addr));
			}
		};
		class HalfAcc {
			Processor& proc;
		public:
			HalfAcc(Processor& p) : proc(p) {}

			inline short read(int addr) {
				return *((short*) memory::prepare(proc, memory::READ, addr));
			}
			inline short& write(int addr) {
				return (short&) *((short*) memory::prepare(proc, memory::WRITE, addr));
			}
			inline short exec(int addr) {
				return *((short*) memory::prepare(proc, memory::EXEC, addr));
			}

		};
		class WordAcc {
			Processor& proc;
		public:
			WordAcc(Processor& p) : proc(p) {}

			inline int read(int addr) {
				return *((int*) memory::prepare(proc, memory::READ, addr));
			}
			inline int& write(int addr) {
				return (int&) *((int*) memory::prepare(proc, memory::WRITE, addr));
			}
			inline int exec(int addr) {
				return *((int*) memory::prepare(proc, memory::EXEC, addr));
			}
		};

	public:
		ByteAcc byte;
		HalfAcc half;
		WordAcc word;

	};

	InterruptQueue intQueue;
	Registers r;
	reg sregs[0xff];
	reg pc;
	reg flags;
	reg o;
	bool broken = false;
	
	Memory mem;

	unique_ptr<char> ram;
	unique_ptr<char> rom;
	unique_ptr<char> dev;

	void step();

private:
	void aluStep(uint opcode, uint ir);
	void memStep(uint opcode, uint ir);
	void bStep(uint opcode, uint ir);
	void jStep(uint opcode, uint ir);
	void rrStep(uint opcode, uint ir);
	void rimmStep(uint opcode, uint ir);

};