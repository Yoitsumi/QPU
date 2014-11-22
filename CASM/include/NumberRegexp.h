#pragma once
#include "RegexpMachine.h"

namespace casm {

	bool isHexDigit(char);

	/*-?[0-9]+*/
	class DecimalNumberRegexp : public RegexpMachine {
	public:
		DecimalNumberRegexp();
		~DecimalNumberRegexp();

	protected:
		/* -?[0-9]+ 
		   ^^
		*/
		RMStatus state0(char, std::vector<std::shared_ptr<RegexpMachine>>&);
		/* -?[0-9]+
		     ^^^^^
		*/
		RMStatus state1(char, std::vector<std::shared_ptr<RegexpMachine>>&);
		/* -?[0-9]+
				    ^
		*/
		RMStatus state2(char, std::vector<std::shared_ptr<RegexpMachine>>&);
	};

	/*(0x[0-a-fA-F]+)|([0-9a-fA-F]+h)*/
	class HexadecimalNumberRegexp : public RegexpMachine {

	public:
		HexadecimalNumberRegexp();
		HexadecimalNumberRegexp(const HexadecimalNumberRegexp&);
		virtual ~HexadecimalNumberRegexp();

	protected:
		/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
			^^             ^
		*/
		RMStatus state0(char, std::vector<std::shared_ptr<RegexpMachine>>&);

		/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
		     ^
		*/
		RMStatus state1(char, std::vector<std::shared_ptr<RegexpMachine>>&);

		/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
		      ^^^^^^^^^^
		*/
		RMStatus state2(char, std::vector<std::shared_ptr<RegexpMachine>>&);

		/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
		                ^^
		*/
		RMStatus state3(char, std::vector<std::shared_ptr<RegexpMachine>>&);

		/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
		                   ^^^^^^^^^^^^
		*/
		RMStatus state4(char, std::vector<std::shared_ptr<RegexpMachine>>&);

		/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
		                               ^^
		*/
		RMStatus state5(char, std::vector<std::shared_ptr<RegexpMachine>>&);

		/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
		                                 ^
		*/
		RMStatus state6(char, std::vector<std::shared_ptr<RegexpMachine>>&);

	};

}