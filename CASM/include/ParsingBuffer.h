#pragma once

#include <memory>
#include <string>

using namespace std;

class ParsingBuffer {
	
public:
	ParsingBuffer();
	~ParsingBuffer();

	string getCurrentString();
	void advance(int);

private:
	const unique_ptr<char> data;
	unsigned int length;
	unsigned int mark;
	unsigned int position;

};

