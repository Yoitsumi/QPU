#pragma once

#include <vector>
#include <memory>
#include <string>

namespace casm {

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

		RegexpMachine(std::vector<stateFunc>);
		RegexpMachine(const RegexpMachine&);

		void copyFrom(RegexpMachine&);

	public:
		virtual ~RegexpMachine();

		virtual RMStatus update(char c, std::vector<std::shared_ptr<RegexpMachine>>& branch);

	};

	class KeywordRegexp : public RegexpMachine {
	protected:
		const std::string keyword;

	public:
		KeywordRegexp(std::string);
		virtual ~KeywordRegexp();
		virtual RMStatus update(char c, std::vector<std::shared_ptr<RegexpMachine>>& branch);
	};

}