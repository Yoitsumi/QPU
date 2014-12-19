#pragma once

#include <string>
#include <map>

namespace casm {

	enum TokenType {
		NONE, SKIP, END, NEWLINE,
		HEX_NUMBER, DEC_NUMBER, BIN_NUMBER,
		MNEMONIC, REGISTER, NAME,
		COMA, COLON
	};

	const std::map<TokenType, std::string> TOKEN_TYPE_NAMES = {
		{ NONE, "NONE" },
		{ SKIP, "SKIP" },
		{ END, "END" },
		{ NEWLINE, "NEWLINE" },
		{ HEX_NUMBER, "HEX_NUMBER" },
		{ DEC_NUMBER, "DEC_NUMBER" },
		{ BIN_NUMBER, "BIN_NUMBER" },
		{ MNEMONIC, "MNEMONIC" },
		{ REGISTER, "REGISTER" },
		{ NAME, "NAME" },
		{ COMA, "COMA" },
		{ COLON, "COLON" }
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