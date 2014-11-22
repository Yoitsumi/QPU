#include "..\include\NumberRegexp.h"

namespace casm {

	using namespace std;

	DecimalNumberRegexp::DecimalNumberRegexp() : RegexpMachine(vector<stateFunc>({
		static_cast<stateFunc>(&DecimalNumberRegexp::state0),
		static_cast<stateFunc>(&DecimalNumberRegexp::state1),
		static_cast<stateFunc>(&DecimalNumberRegexp::state2)
	})) {		
	}


	DecimalNumberRegexp::~DecimalNumberRegexp() {
	}

	RMStatus DecimalNumberRegexp::state0(char c, std::vector<std::shared_ptr<RegexpMachine>>& branch) {
		if(c == '-') {
			state = 1;
			return MATCHING;
		} else {
			state = 1;
			return state1(c, branch);
		}
	}

	RMStatus DecimalNumberRegexp::state1(char c, std::vector<std::shared_ptr<RegexpMachine>>& branch) {
		if(c >= '0' && c <= '9') {
			return MATCHING;
		} else {
			return BROKEN;
		}
	}

	RMStatus DecimalNumberRegexp::state2(char c, std::vector<std::shared_ptr<RegexpMachine>>& branch) {
		if(c >= '0' && c <= '9') {
			return MATCHING;
		} else {
			return FINISHED;
		}
	}

	bool isHexDigit(char c) {
		return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
	}

	HexadecimalNumberRegexp::HexadecimalNumberRegexp() : RegexpMachine({
		static_cast<stateFunc>(&HexadecimalNumberRegexp::state0),
		static_cast<stateFunc>(&HexadecimalNumberRegexp::state1),
		static_cast<stateFunc>(&HexadecimalNumberRegexp::state2),
		static_cast<stateFunc>(&HexadecimalNumberRegexp::state3),
		static_cast<stateFunc>(&HexadecimalNumberRegexp::state4),
		static_cast<stateFunc>(&HexadecimalNumberRegexp::state5),
		static_cast<stateFunc>(&HexadecimalNumberRegexp::state6),
	}) {
	}

	HexadecimalNumberRegexp::~HexadecimalNumberRegexp() {
	}

	HexadecimalNumberRegexp::HexadecimalNumberRegexp(const HexadecimalNumberRegexp& other) : RegexpMachine(other) {
	}

	/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
	   ^^             ^
	*/
	RMStatus HexadecimalNumberRegexp::state0(char c, std::vector<std::shared_ptr<RegexpMachine>>& branch) {
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
	RMStatus HexadecimalNumberRegexp::state1(char c, std::vector<std::shared_ptr<RegexpMachine>>&) {
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
	RMStatus HexadecimalNumberRegexp::state2(char c, std::vector<std::shared_ptr<RegexpMachine>>&) {
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
	RMStatus HexadecimalNumberRegexp::state3(char c, std::vector<std::shared_ptr<RegexpMachine>>&) {
		if(isHexDigit(c)) {
			return MATCHING;
		} else {
			return FINISHED;
		}
	}

	/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
	                   ^^^^^^^^^^^^
	*/
	RMStatus HexadecimalNumberRegexp::state4(char c, std::vector<std::shared_ptr<RegexpMachine>>&) {
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
	RMStatus HexadecimalNumberRegexp::state5(char c, std::vector<std::shared_ptr<RegexpMachine>>&) {
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
	RMStatus HexadecimalNumberRegexp::state6(char, std::vector<std::shared_ptr<RegexpMachine>>&) {
		return FINISHED;
	}

}