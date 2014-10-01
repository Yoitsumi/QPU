#include "main.h"

#include <iostream>

#include "Processor.h"
#include "Opcodes.h"

using namespace processor;
using namespace std;

Processor::Processor() : pc(0), mem(new char[1 << 20]) {
}


Processor::~Processor() {
}

void Processor::step() {
	uint ir = mem.word[pc];
	if(ir == 0xffffffff)
		broken = true;
	if(broken)
		return;
	pc += 4;
	uint opcode = (ir&OPCODE_MASK) >> OPCODE_SHIFT;
	switch(opcode) {
		case OP_ARITH:
		case OP_LOGIC:
			aluStep(opcode, ir);
			break;
		case OP_LB:
		case OP_LH:
		case OP_LW:
		case OP_SB:
		case OP_SH:
		case OP_SW:
			memStep(opcode, ir);
			break;
		case OP_B:
			bStep(opcode, ir);
			break;
		case OP_J:
		case OP_JAL:
			jStep(opcode, ir);
			break;
		case OP_RR:
			rrStep(opcode, ir);
			break;
	}
}

void Processor::aluStep(uint opcode, uint ir) {
	uint f = (ir&FUNCT_RRRI8_MASK) >> FUNCT_RRRI8_SHIFT;
	uint d = (ir&DEST_RRRI8_MASK) >> DEST_RRRI8_SHIFT;
	uint a = (ir&A_RRRI8_MASK) >> A_RRRI8_SHIFT;
	uint b = (ir&B_RRRI8_MASK) >> B_RRRI8_SHIFT;
	unsigned char uimm = (unsigned char) ((ir&IMM_RRRI8_MASK) >> IMM_RRRI8_SHIFT);
	char imm = (char) ((ir&IMM_RRRI8_MASK) >> IMM_RRRI8_SHIFT);
	if(opcode == OP_ARITH) {
		switch(f) {
			case ARITH_ADD:
				r[d] = r[a] + (r[b] + imm);
				break;
			case ARITH_SUB:
				r[d] = r[a] - (r[b] + imm);
				break;
			case ARITH_MUL:{
									long int res = ((long int) r[a]) * ((long int) (r[b] + imm)); //TODO higher bits of result into o register
									cout << res << endl;
									r[d] = res & 0xffffffff;
									o = (res & 0xffffffff00000000) >> 32;
									break;
			}
			case ARITH_DIV:
				r[d] = r[a] / (r[b] + imm);
				o = r[a] % r[b];
				break;
			case ARITH_MULU:
			case ARITH_DIVU:
				break; //TODO unsigned arithmetic
		}
	} else {
		switch(f) {
			case LOGIC_SHLL:
				r[d] = r[a] << (r[b] + imm);
				break;
			case LOGIC_SHRL:
				r[d] = ((ureg) r[a]) >> (r[b] + imm);
				break;
			case LOGIC_SHRA:
				r[d] = r[a] >> (r[b] + imm);
				break;
			case LOGIC_OR:
				r[d] = r[a] | (r[b] + imm);
				break;
			case LOGIC_AND:
				r[d] = r[a] & (r[b] + imm);
				break;
			case LOGIC_XOR:
				r[d] = r[a] ^ (r[b] + imm);
				break;
			case LOGIC_NOR:
				r[d] = ~(r[a] | (r[b] + imm));
				break;
			case LOGIC_NAND:
				r[d] = ~(r[a] & (r[b] + imm));
				break;
			case LOGIC_XNOR:
				r[d] = ~(r[a] ^ (r[b] + imm));
				break;
		}
	}
}

void Processor::memStep(uint opcode, uint ir) {
	bool pcr = (ir&IPR_MEM_MASK) != 0;
	int d = (ir&DEST_MEM_MASK) >> DEST_MEM_SHIFT;
	int a = (ir&A_MEM_MASK) >> A_MEM_SHIFT;
	short imm = (ir&IMM_MEM_MASK) >> IMM_MEM_SHIFT;
	unsigned short uimm = imm;
	int addr = r[a] + imm + (pcr ? pc : 0);
	switch(opcode) {
		case OP_LB:
			r[d] = mem.byte[addr];
			break;
		case OP_LH:
			r[d] = mem.half[addr];
			break;
		case OP_LW:
			r[d] = mem.word[addr];
			break;
		case OP_SB:
			mem.byte[addr] = r[d];
			break;
		case OP_SH:
			mem.half[addr] = r[d];
			break;
		case OP_SW:
			mem.word[addr] = r[d];
			break;
	}
}

void Processor::bStep(uint opcode, uint ir) {
	int f = (ir&F_B_MASK) >> F_B_SHIFT;
	int a = (ir&A_B_MASK) >> A_B_SHIFT;
	int b = (ir&B_B_MASK) >> B_B_SHIFT;
	short imm = (ir&IMM_B_MASK) >> IMM_B_SHIFT;
	if((imm & 0xf000) == 0x1000)
		imm |= 0xf000;
	switch(f) {
		case B_EQ:
			if(r[a] == r[b])
				pc += imm;
			break;
		case B_NE:
			if(r[a] != r[b])
				pc += imm;
			break;
		case B_LT:
			if(r[a] < r[b])
				pc += imm;
			break;
		case B_LE:
			if(r[a] <= r[b])
				pc += imm;
			break;
	}
}

void Processor::jStep(uint opcode, uint ir) {
	if(opcode == OP_JAL) {
		r[31] = pc;
	}
	uint addr = (ir & ADDR_J_MASK) >> ADDR_J_SHIFT;
	addr <<= 2;
	pc &= ~0x1fffffff;
	pc |= addr;
}

void Processor::rrStep(uint opcode, uint ir) {
	int f = (ir & FUNCT_RR_MASK) >> FUNCT_RR_SHIFT;
	int aux = (ir & AUX_RR_MASK) >> AUX_RR_SHIFT;
	int a = (ir & A_RR_MASK) >> A_RR_SHIFT;
	int b = (ir & B_RR_MASK) >> B_RR_SHIFT;
	switch(f) {
		case RR_JALR:
			r[b] = pc;
			pc = r[a];
			break;
	}
}