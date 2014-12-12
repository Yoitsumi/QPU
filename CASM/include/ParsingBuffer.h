#pragma once

#include <memory>
#include <string>

#include "Array.h"

namespace casm {

	class ParsingBuffer {

	public:
		const Array<char> data;

		ParsingBuffer(unsigned length);
		~ParsingBuffer();

		std::string getCurrentString();
		void advance(int);
		bool eof();
		char getChar();

	private:
		unsigned int mark;
		unsigned int position;

	};

}