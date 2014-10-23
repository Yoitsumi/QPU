#include "main.h"

#include "AddressTranslation.h"

#include "Processor.h"

static inline bool bitSet(int mask, int val){
	return (mask&val) != 0;
}

static inline bool bitClear(int mask, int val) {
	return (mask&val) == 0;
}

void* memory::prepare(Processor& p,int mode, int addr) {
	char* ram = p.ram.get();
	char* rom = p.rom.get();
	char* dev = p.dev.get();
	if(bitClear(PROTECTION_MODE_MASK, addr)) {
		//USER MAPPED
		//TODO: TLB translation
		return &ram[addr];
	} else {
		//KERNEL
		//TODO: check current privilages
		if(bitSet(KERNEL_MAPPING_MASK, addr)) {
			//KERNEL MAPPED
			//TODO: TLB translation
			return &ram[addr & KERNEL_MAPPING_MASK];
		} else {
			//KERNEL UNMAPPED
			switch(addr & KERNEL_UNMAPPED_SEG) {
				case KERNEL_SEG_ROM:
					//TODO: check if ROM is active
					if(mode == READ || mode == EXEC)
						return &rom[addr & KERNEL_PHYS_MASK];
					else
						return &ram[addr & KERNEL_PHYS_MASK];
				case KERNEL_SEG_K1:
					//TODO: check access mode for k1
					return &ram[addr & KERNEL_PHYS_MASK + KERNEL_SEG_K1];
				case KERNEL_SEG_K2:
					//TODO: check access mode for k2
					return &ram[addr & KERNEL_PHYS_MASK + KERNEL_SEG_K2];
				case KERNEL_SEG_DEV:
					return &dev[addr & KERNEL_PHYS_MASK];
				default:
					//Not supposed to happen, as the switch covers all possibilities
					return 0;
			}
		}
	}
}