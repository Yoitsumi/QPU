#pragma once
#include "RegexpMachine.h"

namespace casm {

	/*\w+*/
	class WhiteSpaceRegexp : public RegexpMachine {
	public:
		WhiteSpaceRegexp();
		WhiteSpaceRegexp(WhiteSpaceRegexp&);
		~WhiteSpaceRegexp();

	protected:
		/* \w+
		/  ^^  */
		stateDecl(0);

		/* \w+
		/    ^ */
		stateDecl(1);
	};

	/* (\r\n?) || (\n\r?) */
	class NewlineRegexp : public RegexpMachine {
	public:
		NewlineRegexp();
		NewlineRegexp(NewlineRegexp&);
		~NewlineRegexp();

	protected:
		/*	(\r\n?) || (\n\r?)
		/   ^^     ^^  ^^     */
		stateDecl(0);
		/*	(\r\n?) || (\n\r?)
		/     ^^^             */
		stateDecl(1);
		/*	(\r\n?) || (\n\r?)
		/                ^^^  */
		stateDecl(2);
		/*	(\r\n?) || (\n\r?)
		/                    ^*/
		stateDecl(3);
	};

}