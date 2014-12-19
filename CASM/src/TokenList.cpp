#include "..\include\TokenList.h"

namespace casm {

	TokenList::TokenList() : position(0){
	}


	TokenList::~TokenList() {
	}
	
	void TokenList::push_back(Token t) {
		tokens.push_back(t);
	}

	unsigned TokenList::size() {
		return tokens.size();
	}

	TokenList& TokenList::operator <<(Token t) {
		tokens.push_back(t);
		return *this;
	}

	Token& TokenList::operator [](unsigned i) {
		return tokens[i];
	}
	Token& TokenList::lookahead(unsigned i) {
		return tokens[position + i];
	}
	Token& TokenList::next() {
		if(position >= tokens.size())
			return Token{END, "", 0};
		else 
			return tokens[position++];
	}

}