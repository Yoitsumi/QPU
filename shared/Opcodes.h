typedef unsigned int uint;

namespace processor{
	const uint OPCODE_MASK       = 0xf8000000;
	const uint OPCODE_SHIFT      = 27;

	/*
	 * RRI8 format:
	 * .       .       .       .        |
	 * |op  |f  |d   |a   |b   |imm8    |  
	 *  5b   4b  5b   5b   5b   B
	 * op i OP_ARITH or OP_LOGIC
	 * f specifies ALU function such as add, sub etc.
	 * operation: $d = $a (f) ($b + simm8)
	 */
	const uint FUNCT_RRRI8_MASK  = 0x07800000;
	const uint FUNCT_RRRI8_SHIFT = 23;
	const uint DEST_RRRI8_MASK   = 0x007c0000;
	const uint DEST_RRRI8_SHIFT  = 18;
	const uint A_RRRI8_MASK      = 0x0003e000;
	const uint A_RRRI8_SHIFT	  = 13;
	const uint B_RRRI8_MASK		  = 0x00001f00;
	const uint B_RRRI8_SHIFT     = 8;
	const uint IMM_RRRI8_MASK    = 0x000000ff;
	const uint IMM_RRRI8_SHIFT   = 0;
	
	/*
	 * MEM format:
	 * .       .       .       .       |
	 * |op  ||d   |a   |imm16          |
	 *  5b  b 5b   5b   H
	 * (second operand is called IPR)
	 * loads or stores value from/to $d into memory address $a+simm16
	 * (if IPR bit is set, pc of next instruction is added to address)
	*/
	const uint IPR_MEM_MASK      = 0x04000000;
	const uint DEST_MEM_MASK     = 0x03e00000;
	const uint DEST_MEM_SHIFT    = 21;
	const uint A_MEM_MASK        = 0x001f0000;
	const uint A_MEM_SHIFT       = 16;
	const uint IMM_MEM_MASK      = 0x0000ffff;
	const uint IMM_MEM_SHIFT     = 0;

	/*
	 * B format:
	 * .       .       .       .       |
	 * |op  |f  |a   |b   |imm13       |
	 *  5b   4b  5b   5b   13b
	 * operation: conditionally branches to pc + simm13
	*/
	const uint F_B_MASK          = 0x07800000;
	const uint F_B_SHIFT         = 23;
	const uint A_B_MASK          = 0x007c0000;
	const uint A_B_SHIFT         = 18;
	const uint B_B_MASK          = 0x0003e000;
	const uint B_B_SHIFT         = 13;
	const uint IMM_B_MASK        = 0x00001fff;
	const uint IMM_B_SHIFT       = 0;

	/*
	 * J format:
	 * .       .       .       .       |
	 * |op  |addr                      |
	 *  5b   27b
	*/
	const uint ADDR_J_MASK       = 0x07ffffff;
	const uint ADDR_J_SHIFT      = 0;

	/*
	 * RR format:
	 * |   .   ,   .   |   .   ,   .   |
	 * |op  |f     |aux      |a   |b   |
	 *  5b   7b     10b       5b   5b
	 * operation: does some special stuff on registers a, b
	*/
	const uint FUNCT_RR_MASK     = 0x07f00000;
	const uint FUNCT_RR_SHIFT    = 20;
	const uint AUX_RR_MASK       = 0x000ffc00;
	const uint AUX_RR_SHIFT      = 10;
	const uint A_RR_MASK         = 0x000003e0;
	const uint A_RR_SHIFT        = 5;
	const uint B_RR_MASK         = 0x0000001f;
	const uint B_RR_SHIFT        = 0;

	/*
	 * RIMM format:
	 * |   .   ,   .   |   .   ,   .   |
	 * |op  |f    |d   |simm16         |
	 *  5b   6b    5b   H
	 * operation: does something on register and signed 16 bit immediate
	 */
	const uint FUNCT_RIMM_MASK  = 0x07e00000;
	const uint FUNCT_RIMM_SHIFT = 21;
	const uint D_RIMM_MASK      = 0x001f0000;
	const uint D_RIMM_SHIFT     = 16;
	const uint IMM_RIMM_MASK    = 0x0000ffff;
	const uint IMM_RIMM_SHIFT   = 0;

	const uint OP_ARITH = 0x00;
	const uint OP_LOGIC = 0x01;
	const uint OP_LB    = 0x02;
	const uint OP_LH    = 0x03;
	const uint OP_LW    = 0x04;//05 reserved for LD
	const uint OP_SB    = 0x06;
	const uint OP_SH    = 0x07;
	const uint OP_SW    = 0x08;//09 reserved for SD
	const uint OP_B     = 0x0a;
	const uint OP_J     = 0x0b;
	const uint OP_JAL   = 0x0c;
	const uint OP_RIMM  = 0x0d;
	const uint OP_RR    = 0x1f;

	const uint ARITH_ADD  = 0x0;
	const uint ARITH_SUB  = 0x1;
	const uint ARITH_MUL  = 0x2;
	const uint ARITH_DIV  = 0x3;
	const uint ARITH_MOD  = 0x5;
	const uint ARITH_MULU = 0x6;
	const uint ARITH_DIVU = 0x7;
	const uint ARITH_MODU = 0x9;

	const uint LOGIC_SHLL = 0x0;
	const uint LOGIC_SHRL = 0x1;
	const uint LOGIC_SHRA = 0x2;
	const uint LOGIC_OR   = 0x4;
	const uint LOGIC_AND  = 0x5;
	const uint LOGIC_XOR  = 0x6;
	const uint LOGIC_NOR  = 0x8;
	const uint LOGIC_NAND = 0x9;
	const uint LOGIC_XNOR = 0xa;

	const uint B_EQ       = 0x0;
	const uint B_NE       = 0x1;
	const uint B_LT       = 0x2;
	const uint B_LE       = 0x3;

	const uint RR_JALR    = 0x01;
	/*
	  Transfers data from register b into a special register specified in aux field
	  If the special register is 64bit, higher bits are set to contents of $a
	  otherwise $a should be set to $0 for compatibility with future versions
	*/
	const uint RR_MTS     = 0x30;
	const uint RR_MFS     = 0x31;

	const uint RIMM_LLH   = 0x10;
	const uint RIMM_LUH   = 0x11;

	const uint SREG_HWIV = 0x000; // HardWare Interrupt Vector 
	const uint SREG_SWIV = 0x001; // SoftWare Interrupt Vector
	const uint SREG_EXIV = 0x002; // EXception Interrupt Vector
	const uint SREG_DBIV = 0x003; // DeBug Interrupt Vector
	const uint SREG_ERPC = 0x004; // Exception Return PC
	const uint SREG_IOCD = 0x005; // Interrupt Origin CoDe

	const uint INTCODE_ORIGIN_MASK  = 0xc0000000;
	const uint INTCODE_ORIGIN_SHIFT = 30;
	const uint INTCODE_ORIGIN_HW = 0;
	const uint INTCODE_ORIGIN_SW = 1;
	const uint INTCODE_ORIGIN_EX = 2;
	const uint INTCODE_ORIGIN_DB = 3;
}