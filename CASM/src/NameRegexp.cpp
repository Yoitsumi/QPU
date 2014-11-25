#include "..\include\NameRegexp.h"

namespace casm {

	NameRegexp::NameRegexp() : RegexpMachine({
		static_cast<stateFunc>(&NameRegexp::state0),
		static_cast<stateFunc>(&NameRegexp::state1),
	},
	NAME, 10) {
	}

	NameRegexp::NameRegexp(NameRegexp& other) : RegexpMachine(other) {}


	NameRegexp::~NameRegexp() {
	}

	RMStatus NameRegexp::stateDef(0) {
		if(isNameStart(c)) {
			state = 1;
			return MATCHING;
		} else return BROKEN;
	}

	RMStatus NameRegexp::stateDef(1) {
		if(isNameConstituent(c)) {
			return MATCHING;
		} else return FINISHED;
	}

}