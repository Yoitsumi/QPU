#include "..\include\Token.h"

namespace casm {

	int Token::compareTo(const Token& t) const{
		if(image.size() != t.image.size()) {
			return image.size() - t.image.size();
		} else {
			return t.priority - priority;
		}
	}

}