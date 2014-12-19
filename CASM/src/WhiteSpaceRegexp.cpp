#include "..\include\WhiteSpaceRegexp.h"

namespace casm {

	WhiteSpaceRegexp::WhiteSpaceRegexp() : RegexpMachine({
		static_cast<stateFunc>(&WhiteSpaceRegexp::state0),
		static_cast<stateFunc>(&WhiteSpaceRegexp::state1),
	},
	SKIP, 10) {
	}

		WhiteSpaceRegexp::WhiteSpaceRegexp(WhiteSpaceRegexp& other) : RegexpMachine(other) {}


	WhiteSpaceRegexp::~WhiteSpaceRegexp() {
	}

	RMStatus WhiteSpaceRegexp::stateDef(0) {
		if(isWhiteSpace(c)) {
			state = 1;
			return MATCHING;
		} else {
			return BROKEN;
		}
	}

	RMStatus WhiteSpaceRegexp::stateDef(1) {
		if(isWhiteSpace(c))
			return MATCHING;
		else
			return FINISHED;
	}



	NewlineRegexp::NewlineRegexp() : RegexpMachine({
		static_cast<stateFunc>(&NewlineRegexp::state0),
		static_cast<stateFunc>(&NewlineRegexp::state1),
		static_cast<stateFunc>(&NewlineRegexp::state2),
		static_cast<stateFunc>(&NewlineRegexp::state3),
	}, NEWLINE, 5) {}

	NewlineRegexp::NewlineRegexp(NewlineRegexp& other) : RegexpMachine(other) {}
	NewlineRegexp::~NewlineRegexp() {};

	/*	(\r\n?) || (\n\r?)
	/   ^^     ^^  ^^     */
	RMStatus NewlineRegexp::stateDef(0) {
		if(c == '\r') {
			state = 1;
			return MATCHING;
		} else if(c == '\n') {
			state = 2;
			return MATCHING;
		} else return BROKEN;
	}
	/*	(\r\n?) || (\n\r?)
	/     ^^^             */
	RMStatus NewlineRegexp::stateDef(1) {
		if(c == '\n') {
			state = 3;
			return MATCHING;
		} else return FINISHED;
	}
	/*	(\r\n?) || (\n\r?)
	/                ^^^  */
	RMStatus NewlineRegexp::stateDef(2) {
		if(c == '\r') {
			state = 3;
			return MATCHING;
		} else return FINISHED;
	}
	/*	(\r\n?) || (\n\r?)
	/                    ^*/
	RMStatus NewlineRegexp::stateDef(3) {
		return FINISHED;
	}

}