#include <iostream>

#include "RegexpMachine.h"
#include "NumberRegexp.h"

using namespace std;
using namespace casm;

int main() {
	string tested = "0x58ABDh ";
	vector<shared_ptr<RegexpMachine>> regexps;
	regexps.push_back(shared_ptr<RegexpMachine>(new HexadecimalNumberRegexp()));
	for(unsigned int i = 0; i < tested.size(); i++) {
		for(unsigned int r = 0; r < regexps.size(); r++) {
			RMStatus res = regexps[r]->update(tested[i], regexps);
			if(res == BROKEN) {
				regexps.erase(regexps.begin()+r);
				r--;
				if(regexps.size() == 0) {
					cout << "NOT MATCHED" << endl;
					break;
				}
			} else if(res == FINISHED) {
				cout << "Matched: " << tested.substr(0, i) << endl;
				goto exit;
			}
		}
	}
	exit:
	cin.sync();
	cin.ignore();
}