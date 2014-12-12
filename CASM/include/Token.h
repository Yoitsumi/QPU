#pragma once

#include <string>

namespace casm {

	enum TokenType {
		NONE, SKIP,
		HEX_NUMBER, DEC_NUMBER, BIN_NUMBER,
		MNEMONIC, REGISTER, NAME
	};


	struct Token {

		TokenType type;
		std::string image;
		unsigned int priority;

		int compareTo(const Token&) const;

		bool operator <(const Token&) const;
		bool operator >(const Token&) const;
		bool operator >=(const Token&) const;
		bool operator <=(const Token&) const;

	};

}