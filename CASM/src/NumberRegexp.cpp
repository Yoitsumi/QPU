#include "..\include\NumberRegexp.h"

namespace casm {

	using namespace std;

	DecimalNumberRegexp::DecimalNumberRegexp() : RegexpMachine({
		static_cast<stateFunc>(&DecimalNumberRegexp::state0),
		static_cast<stateFunc>(&DecimalNumberRegexp::state1),
		static_cast<stateFunc>(&DecimalNumberRegexp::state2)
	},
	DEC_NUMBER, 10) {		
	}

	DecimalNumberRegexp::DecimalNumberRegexp(const DecimalNumberRegexp& other) : RegexpMachine(other) {}

	DecimalNumberRegexp::~DecimalNumberRegexp() {
	}

	RMStatus DecimalNumberRegexp::stateDef(0) {
		if(c == '-') {
			state = 1;
			return MATCHING;
		} else {
			state = 1;
			return state1(c, branch);
		}
	}

	RMStatus DecimalNumberRegexp::stateDef(1) {
		if(c >= '0' && c <= '9') {
			state = 2;
			return MATCHING;
		} else {
			return BROKEN;
		}
	}

	RMStatus DecimalNumberRegexp::stateDef(2) {
		if(c >= '0' && c <= '9') {
			return MATCHING;
		} else {
			return FINISHED;
		}
	}


	HexadecimalNumberRegexp::HexadecimalNumberRegexp() : RegexpMachine({
		static_cast<stateFunc>(&HexadecimalNumberRegexp::state0),
		static_cast<stateFunc>(&HexadecimalNumberRegexp::state1),
		static_cast<stateFunc>(&HexadecimalNumberRegexp::state2),
		static_cast<stateFunc>(&HexadecimalNumberRegexp::state3),
		static_cast<stateFunc>(&HexadecimalNumberRegexp::state4),
		static_cast<stateFunc>(&HexadecimalNumberRegexp::state5),
		static_cast<stateFunc>(&HexadecimalNumberRegexp::state6),
	},
	HEX_NUMBER, 10) {
	}

	HexadecimalNumberRegexp::~HexadecimalNumberRegexp() {
	}

	HexadecimalNumberRegexp::HexadecimalNumberRegexp(const HexadecimalNumberRegexp& other) : RegexpMachine(other) {
	}

	/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
	   ^^             ^
	*/
	RMStatus HexadecimalNumberRegexp::stateDef(0) {
		shared_ptr<HexadecimalNumberRegexp> copy(new HexadecimalNumberRegexp(*this));
		copy->state = 4;
		branch.push_back(copy);
		if(c == '0') {
			state = 1;
			return MATCHING;
		} else {
			return BROKEN;
		}
	}

	/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
	     ^
	*/
	RMStatus HexadecimalNumberRegexp::stateDef(1) {
		if(c == 'x') {
			state = 2;
			return MATCHING;
		} else {
			return BROKEN;
		}
	}

	/* (0x[0-9a-fA-F]+)|([0-9a-fA-F]+h)
	      ^^^^^^^^^^
	*/
	RMStatus HexadecimalNumberRegexp::stateDef(2) {
		if(isHexDigit(c)) {
			state = 3;
			return MATCHING;
		} else {
			return BROKEN;
		}
	}

	/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
	                ^^
	*/
	RMStatus HexadecimalNumberRegexp::stateDef(3) {
		if(isHexDigit(c)) {
			return MATCHING;
		} else {
			return FINISHED;
		}
	}

	/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
	                   ^^^^^^^^^^^^
	*/
	RMStatus HexadecimalNumberRegexp::stateDef(4) {
		if(isHexDigit(c)) {
			state = 5;
			return MATCHING;
		} else {
			return BROKEN;
		}
	}

	/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
	                               ^^
	*/
	RMStatus HexadecimalNumberRegexp::stateDef(5) {
		if(isHexDigit(c)) {
			return MATCHING;
		} else if(c == 'h' || c == 'H') {
			state = 6;
			return MATCHING;
		} else {
			return BROKEN;
		}
	}

	/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
	                                 ^
	*/
	RMStatus HexadecimalNumberRegexp::stateDef(6) {
		return FINISHED;
	}


	BinaryNumberRegexp::BinaryNumberRegexp() : RegexpMachine({		
		static_cast<stateFunc>(&BinaryNumberRegexp::state0),
		static_cast<stateFunc>(&BinaryNumberRegexp::state1),
		static_cast<stateFunc>(&BinaryNumberRegexp::state2),
		static_cast<stateFunc>(&BinaryNumberRegexp::state3),
	},
	BIN_NUMBER, 10) {
	}
	BinaryNumberRegexp::BinaryNumberRegexp(const BinaryNumberRegexp& other) : RegexpMachine(other) {};
	BinaryNumberRegexp::~BinaryNumberRegexp() {};

	/* 0b[01]+
	   ^
	*/
	RMStatus BinaryNumberRegexp::stateDef(0) {
		if(c == '0') {
			state = 1;
			return MATCHING;
		} else return BROKEN;
	}
	/* 0b[01]+
	    ^
	*/
	RMStatus BinaryNumberRegexp::stateDef(1) {
		if(c == 'b' || c == 'B') {
			state = 2;
			return MATCHING;
		} else return BROKEN;
	}
	/* 0b[01]+
	     ^^^^
	*/
	RMStatus BinaryNumberRegexp::stateDef(2) {
		if(c == '0' || c == '1') {
			state = 3;
			return MATCHING;
		} else return BROKEN;
	}
	/* 0b[01]+
	         ^
	*/
	RMStatus BinaryNumberRegexp::stateDef(3) {
		if(c == '0' || c == '1') return MATCHING;
		else return FINISHED;
	}
}