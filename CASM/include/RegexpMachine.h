#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Token.h"

#define stateDecl(i) RMStatus state##i(char, std::vector<std::shared_ptr<RegexpMachine >>&)
#define stateDef(i) state##i(char c, std::vector<std::shared_ptr<RegexpMachine >>& branch)

namespace casm {

	bool isHexDigit(char);

	bool isDigit(char);

	bool isNameStart(char);

	bool isNameConstituent(char);

	bool isWhiteSpace(char);

	/*codes for status of regexp state machines*/
	enum RMStatus {
		/*matching - returned, when string may match until now*/
		MATCHING,
		/*broken   - when string cannot match this regexp branch*/
		BROKEN,
		/*finished - after FIRST character, that cannot fit into this branch, but it still matches*/
		FINISHED
	};

	class RegexpMachine {
	protected:
		typedef RMStatus(RegexpMachine::*stateFunc)(char, std::vector<std::shared_ptr<RegexpMachine >>&);
		unsigned int state;
		std::vector<stateFunc> states;

		const TokenType tokenType;
		const unsigned int priority;

		RegexpMachine(std::vector<stateFunc>, TokenType, unsigned int priority);
		RegexpMachine(const RegexpMachine&);

		//void copyFrom(RegexpMachine&);

	public:
		virtual ~RegexpMachine();

		virtual RMStatus update(char c, std::vector<std::shared_ptr<RegexpMachine>>& branch);
		Token createToken(std::string);

		virtual void reset() {
			state = 0;
		}

	};

	class KeywordRegexp : public RegexpMachine {
	protected:
		const std::string keyword;

	public:
		KeywordRegexp(std::string, TokenType, unsigned int priority);
		KeywordRegexp(const KeywordRegexp&);
		virtual ~KeywordRegexp();
		virtual RMStatus update(char c, std::vector<std::shared_ptr<RegexpMachine>>& branch);
	};

}