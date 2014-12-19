#pragma once

#include <vector>

#include "Token.h"

namespace casm {

	class TokenList {
	private:
		std::vector<Token> tokens;
		int position;
	public:
		TokenList();
		~TokenList();

		void push_back(Token t);
		TokenList& operator <<(Token);

		unsigned size();

		Token& operator [](unsigned);
		Token& lookahead(unsigned);
		Token& next();
	};

}
