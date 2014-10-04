#include "main.h"

#include "AddressTranslation.h"

static inline bool bitSet(int mask, int val){
	return (mask&val) != 0;
}

long memory::translate(Processor& p, int addr){
	return 0l;
}

