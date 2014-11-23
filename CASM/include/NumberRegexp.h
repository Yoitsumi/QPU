#pragma once
#include "RegexpMachine.h"

namespace casm {
	
	/*-?[0-9]+*/
	class DecimalNumberRegexp : public RegexpMachine {
	public:
		DecimalNumberRegexp();
		DecimalNumberRegexp(const DecimalNumberRegexp&);
		~DecimalNumberRegexp();

	protected:
		/* -?[0-9]+ 
		   ^^
		*/
		stateDecl(0);
		/* -?[0-9]+
		     ^^^^^
		*/
		stateDecl(1);
		/* -?[0-9]+
				    ^
		*/
		stateDecl(2);
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
		stateDecl(0);

		/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
		     ^
		*/
		stateDecl(1);

		/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
		      ^^^^^^^^^^
		*/
		stateDecl(2);

		/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
		                ^^
		*/
		stateDecl(3);

		/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
		                   ^^^^^^^^^^^^
		*/
		stateDecl(4);

		/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
		                               ^^
		*/
		stateDecl(5);

		/* (0x[0-a-fA-F]+)|([0-9a-fA-F]+h)
		                                 ^
		*/
		stateDecl(6);

	};

	/* 0b[01]+ */
	class BinaryNumberRegexp : public RegexpMachine {

	public:
		BinaryNumberRegexp();
		BinaryNumberRegexp(const BinaryNumberRegexp&);
		virtual ~BinaryNumberRegexp();

	protected:
		/* 0b[01]+ 
		   ^
		*/
		stateDecl(0);		
		/* 0b[01]+
		    ^
		*/
		stateDecl(1);
		/* 0b[01]+
		     ^^^^
		*/
		stateDecl(2);
		/* 0b[01]+
		         ^
		*/
		stateDecl(3);

	};

}