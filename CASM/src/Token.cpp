#include "..\include\Token.h"

namespace casm {

	int Token::compareTo(const Token& t) const{
		if(image.size() != t.image.size()) {
			return image.size() - t.image.size();
		} else {
			return t.priority - priority;
		}
	}

	bool Token::operator <(const Token& t) const {
		return compareTo(t) < 0;
	}
	bool Token::operator >(const Token& t) const {
		return compareTo(t) > 0;
	}
	bool Token::operator >=(const Token& t) const {
		return compareTo(t) >= 0;
	}
	bool Token::operator <=(const Token& t) const {
		return compareTo(t) <= 0;
	}


}