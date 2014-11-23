#pragma once
#include "RegexpMachine.h"

namespace casm {

	/* $([0-9][0-9]?)|([a-zA-Z_.][a-zA-Z0-9_.]*) */
	class RegisterRegexp : public RegexpMachine {
	public:

		RegisterRegexp();
		RegisterRegexp(RegisterRegexp&);
		~RegisterRegexp();

	protected:
		/* $([0-9][0-9]?)|([a-zA-Z_.][a-zA-Z0-9_.]*)
		   ^                                         */
		stateDecl(0);
		/* $([0-9][0-9]?)|([a-zA-Z_.][a-zA-Z0-9_.]*)
		     ^^^^^       ^ ^^^^^^^^^^                */
		stateDecl(1);
		/* $([0-9][0-9]?)|([a-zA-Z_.][a-zA-Z0-9_.]*)
		          ^^^^^^                             */
		stateDecl(2);
		/* $([0-9][0-9]?)|([a-zA-Z_.][a-zA-Z0-9_.]*)
		                ^                            */
		stateDecl(3);
		/* $([0-9][0-9]?)|([a-zA-Z_.][a-zA-Z0-9_.]*)
		                             ^^^^^^^^^^^^^^^ */
		stateDecl(4);
	};

}