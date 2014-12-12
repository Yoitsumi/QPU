#include <iostream>

#include "RegexpMachine.h"
#include "NumberRegexp.h"
#include "RegisterRegexp.h"
#include "NameRegexp.h"

#include "ParsingBuffer.h"

using namespace std;
using namespace casm;

int main() {
	string tested = "$zero// ";
	
	ParsingBuffer input(tested.size()+1);
	for(int i=0; i<tested.size(); i++)
		input.data[i] = tested[i];
	input.data[input.data.length-1] = '\0';

	//cout << &input.data[0] << endl;

	vector<shared_ptr<RegexpMachine>> regexpsTemplate;
	regexpsTemplate.push_back(shared_ptr<RegexpMachine>(new DecimalNumberRegexp()));
	regexpsTemplate.push_back(shared_ptr<RegexpMachine>(new BinaryNumberRegexp()));
	regexpsTemplate.push_back(shared_ptr<RegexpMachine>(new HexadecimalNumberRegexp()));
	regexpsTemplate.push_back(shared_ptr<RegexpMachine>(new RegisterRegexp()));
	regexpsTemplate.push_back(shared_ptr<RegexpMachine>(new NameRegexp()));
	Token matched = { NONE, "", 0xffffffff };
	//for(unsigned int i = 0; i < tested.size(); i++) {
	vector<shared_ptr<RegexpMachine>> regexps(regexpsTemplate);
	while(!input.eof()) {
		char c = input.getChar();		
		for(unsigned int r = 0; r < regexps.size(); r++) {
			RMStatus res = regexps[r]->update(c, regexps);
			if(res == BROKEN) {
				regexps.erase(regexps.begin()+r);
				r--;
				if(regexps.size() == 0) {					
					goto exit;
				}
			} else if(res == FINISHED) {				
				Token current = regexps[r]->createToken(input.getCurrentString());
				//int cmp = matched.compareTo(current);
				if(current > matched) {
					matched = current;
				}
				regexps.erase(regexps.begin() + r);
				r--;
				if(regexps.size() == 0) {
					goto exit;
				}
			}
		}
	}
exit:
	if(matched.image.size()>0)
		cout << "Matched: " << matched.image << endl;
	else
		cout << "Not matched" << endl;
	cin.sync();
	cin.ignore();
}