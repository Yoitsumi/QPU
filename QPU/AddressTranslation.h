//Methods for translating virtual adress to physical
//includes:
// - Control of privilaged modes (kernel, user) //TODO
// - TLB translation							//TODO

#pragma once

class Processor;

namespace memory {
	

	long translate(Processor&, int);
}