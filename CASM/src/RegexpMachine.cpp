#include "..\include\RegexpMachine.h"

using namespace std;

namespace casm {
	
	bool isHexDigit(char c) {
		return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
	}

	bool isDigit(char c) {
		return c >= '0' && c <= '9';
	}

	bool isNameStart(char c) {
		return (c >= 'a' && c <= 'z') ||
			    (c >= 'A' && c <= 'Z') ||
				  c == '_' || c == '.';
	}

	bool isNameConstituent(char c) {
		return (c >= 'a' && c <= 'z') ||
			    (c >= 'A' && c <= 'Z') ||
				 (c >= '0' && c <= '9') ||
			     c == '_' || c == '.';
	}

	bool isWhiteSpace(char c) {
		return (c == ' ' || c == '\n' || c == '\t' || c == '\r' );
	}

	RegexpMachine::RegexpMachine(std::vector<stateFunc> sts, TokenType tt, unsigned int p) :
		states(sts), state(0), tokenType(tt), priority(p) {
	}

	RegexpMachine::RegexpMachine(const RegexpMachine& other) : 
		states(other.states), state(other.state), tokenType(other.tokenType), priority(other.priority) {

	}


	RegexpMachine::~RegexpMachine() {
	}

	RMStatus RegexpMachine::update(char c, vector<shared_ptr<RegexpMachine>>& branch) {
		return (this->*states[state])(c, branch);
	}

	Token RegexpMachine::createToken(string image) {
		return {tokenType, image, priority};
	}

	/*
	void RegexpMachine::copyFrom(RegexpMachine& from) {
		states = from.states;
	}
	*/



	KeywordRegexp::KeywordRegexp(string k, TokenType type, unsigned int p) : RegexpMachine({}, type, p), keyword(k) {}

	KeywordRegexp::KeywordRegexp(const KeywordRegexp& other) : RegexpMachine(other), keyword(other.keyword) {}

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