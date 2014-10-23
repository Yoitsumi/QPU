//Methods for translating virtual adress to physical
//includes:
// - Control of privilaged modes (kernel, user) //TODO
// - TLB translation							//TODO

#pragma once

class Processor;

typedef unsigned int uint;

namespace memory {

	const uint PROTECTION_MODE_MASK = 1<<31;
	const uint KERNEL_MAPPING_MASK  = 1<<30;
	const uint KERNEL_MAPPED_MASK   = (1<<30)-1;
	const uint KERNEL_UNMAPPED_SEG  = 3<<28;
	const uint KERNEL_SEG_ROM       = 0<<28;
	const uint KERNEL_SEG_K0        = 0<<28;
	const uint KERNEL_SEG_K1        = 1<<28;
	const uint KERNEL_SEG_K2        = 2<<28;
	const uint KERNEL_SEG_DEV       = 3<<28;
	const uint KERNEL_PHYS_MASK     = (1<<28)-1;

	const int WRITE = 0;
	const int READ = 1;
	const int EXEC = 2;
	void* prepare(Processor&,int access, int address);
}