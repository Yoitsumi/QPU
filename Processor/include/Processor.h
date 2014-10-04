#include "Architecture.h"

typedef unsigned int uint;

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
		
		char* ptr;

	public:
		Memory(char* p) : ptr(p), byte(p), half(p), word(p){}
		Memory() : ptr(new char[1 << 20]), byte(ptr), half(ptr), word(ptr) {}

	private:
		class ByteAcc {
			const char* ptr;
		public:
			ByteAcc(char* p) : ptr(p) {}
			inline char& operator[](int addr) {
				return (char&) ptr[addr];
			}
		};
		class HalfAcc {
			const char* ptr;
		public:
			HalfAcc(char* p) : ptr(p) {}
			inline short& operator[](int addr) {
				return (short&) (ptr[addr]);
			}
		};
		class WordAcc {
			const char* ptr;
		public:
			WordAcc(char* p) : ptr(p) {}
			inline int& operator[](int addr) {
				return (int&) (ptr[addr]);
			}
		};

	public:
		ByteAcc byte;
		HalfAcc half;
		WordAcc word;

	};

	Registers r;
	reg pc;
	reg o;
	bool broken = false;
	
	Memory mem;

	void step();

private:
	void aluStep(uint opcode, uint ir);
	void memStep(uint opcode, uint ir);
	void bStep(uint opcode, uint ir);
	void jStep(uint opcode, uint ir);
	void rrStep(uint opcode, uint ir);

};