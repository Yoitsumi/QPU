#include "..\include\RegexpMachine.h"

using namespace std;

namespace casm {

	RegexpMachine::RegexpMachine(std::vector<stateFunc> sts) : states(sts), state(0) {
	}

	RegexpMachine::RegexpMachine(const RegexpMachine& other) : states(other.states), state(other.state) {

	}


	RegexpMachine::~RegexpMachine() {
	}

	RMStatus RegexpMachine::update(char c, vector<shared_ptr<RegexpMachine>>& branch) {
		return (this->*states[state])(c, branch);
	}

	void RegexpMachine::copyFrom(RegexpMachine& from) {
		states = from.states;
	}



	KeywordRegexp::KeywordRegexp(string k) : RegexpMachine({}), keyword(k) {}

	KeywordRegexp::~KeywordRegexp() {}

	RMStatus KeywordRegexp::update(char c, std::vector<std::shared_ptr<RegexpMachine>>& branch) {
		if(state >= keyword.size()) {
			return FINISHED;
		}
		if(keyword[state++] != c) {
			return BROKEN;
		} else {
			return MATCHING;
		}
	}

}