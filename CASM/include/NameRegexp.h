#pragma once
#include "RegexpMachine.h"

namespace casm {

	/* [a-zA-z_.][a-zA-Z0-9_.]* */
	class NameRegexp : public RegexpMachine {

	public:
		NameRegexp();
		NameRegexp(NameRegexp&);
		~NameRegexp();

	protected:
		/* [a-zA-z_.][a-zA-Z0-9_.]*
		*  ^^^^^^^^^^               */
		stateDecl(0);

		/* [a-zA-z_.][a-zA-Z0-9_.]*
		*            ^^^^^^^^^^^^^^ */
		stateDecl(1);

	};

}