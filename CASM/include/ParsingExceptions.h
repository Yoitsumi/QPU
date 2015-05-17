#pragma once

#include <exception>

#include "Token.h"

using namespace std;

namespace casm {

	class UnexpectedToken : public exception {

	private:
		const TokenType expected, encountered;

	public:
		UnexpectedToken(TokenType ex, TokenType en) : expected(ex), encountered(en) {}
		UnexpectedToken(TokenType en) : expected(NONE), encountered(en) {}

		virtual const char* what() const{
			if(expected != NONE)
				return ("Unexpected token encountered: " + TOKEN_TYPE_NAMES.at(encountered) + ", expected " + TOKEN_TYPE_NAMES.at(expected)).c_str();
			else 
				return ("Unexpected token encountered: " + TOKEN_TYPE_NAMES.at(encountered)).c_str();
		}

	};

}