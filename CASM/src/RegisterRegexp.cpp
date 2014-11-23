#include "..\include\RegisterRegexp.h"

namespace casm {

	RegisterRegexp::RegisterRegexp() : RegexpMachine({
		static_cast<stateFunc>(&RegisterRegexp::state0),
		static_cast<stateFunc>(&RegisterRegexp::state1),
		static_cast<stateFunc>(&RegisterRegexp::state2),
		static_cast<stateFunc>(&RegisterRegexp::state3),
		static_cast<stateFunc>(&RegisterRegexp::state4)
	},
	REGISTER, 10) {
	}


	RegisterRegexp::~RegisterRegexp() {
	}

	/* $([0-9][0-9]?)|([a-zA-Z_.][a-zA-Z0-9_.]*)
	   ^                                         */
	RMStatus RegisterRegexp::stateDef(0) {
		if(c == '$') {
			state = 1;
			return MATCHING;
		} else return BROKEN;
	}
	/* $([0-9][0-9]?)|([a-zA-Z_.][a-zA-Z0-9_.]*)
	     ^^^^^       ^ ^^^^^^^^^^                */
	RMStatus RegisterRegexp::stateDef(1) {
		if(isDigit(c)) {
			state = 2;
			return MATCHING;
		} else if(isNameStart(c)) {
			state = 4;
			return MATCHING;
		} else return BROKEN;
	}
	/* $([0-9][0-9]?)|([a-zA-Z_.][a-zA-Z0-9_.]*)
	          ^^^^^^                             */
	RMStatus RegisterRegexp::stateDef(2) {
		if(isDigit(c)) {
			state = 3;
			return MATCHING;
		} else return FINISHED;
	}
	/* $([0-9][0-9]?)|([a-zA-Z_.][a-zA-Z0-9_.]*)
	                ^                            */
	RMStatus RegisterRegexp::stateDef(3) {
		return FINISHED;
	}
	/* $([0-9][0-9]?)|([a-zA-Z_.][a-zA-Z0-9_.]*)
	                             ^^^^^^^^^^^^^^^ */
	RMStatus RegisterRegexp::stateDef(4) {
		if(isNameConstituent(c)) {
			return MATCHING;
		} else return FINISHED;
	}
}