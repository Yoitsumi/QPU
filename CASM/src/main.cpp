#include <iostream>

#include "RegexpMachine.h"
#include "NumberRegexp.h"
#include "RegisterRegexp.h"

using namespace std;
using namespace casm;

int main() {
	string tested = "$zero ";
	vector<shared_ptr<RegexpMachine>> regexps;
	regexps.push_back(shared_ptr<RegexpMachine>(new DecimalNumberRegexp()));
	regexps.push_back(shared_ptr<RegexpMachine>(new BinaryNumberRegexp()));
	regexps.push_back(shared_ptr<RegexpMachine>(new HexadecimalNumberRegexp()));
	regexps.push_back(shared_ptr<RegexpMachine>(new RegisterRegexp()));
	Token matched = { NONE, "", 0xffffffff };
	for(unsigned int i = 0; i < tested.size(); i++) {
		for(unsigned int r = 0; r < regexps.size(); r++) {
			RMStatus res = regexps[r]->update(tested[i], regexps);
			if(res == BROKEN) {
				regexps.erase(regexps.begin()+r);
				r--;
				if(regexps.size() == 0) {					
					goto exit;
				}
			} else if(res == FINISHED) {				
				Token current = regexps[r]->createToken(tested.substr(0, i));
				int cmp = matched.compareTo(current);
				if(cmp < 0) {
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