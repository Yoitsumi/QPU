#include "..\include\ParsingBuffer.h"

using namespace std;

namespace casm {

	ParsingBuffer::ParsingBuffer(unsigned l) : data(l), position(0), mark(0) {
	}


	ParsingBuffer::~ParsingBuffer() {
	}

	string ParsingBuffer::getCurrentString() {
		/*
		unique_ptr<char[]> buff = unique_ptr<char[]>(new char[position - mark]);
		return string(buff.get());
		*/
		return string(&data[mark], position - mark - 1);
	}

	void ParsingBuffer::advance(int i) {
		mark += i;
		position = mark;
	}

	bool ParsingBuffer::eof() {
		return position == data.length;
	}

	char ParsingBuffer::getChar() {
		return data[position++];
	}

}