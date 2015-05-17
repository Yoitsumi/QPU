#include <iostream>
#include <fstream>

#include "RegexpMachine.h"
#include "NumberRegexp.h"
#include "RegisterRegexp.h"
#include "NameRegexp.h"
#include "WhiteSpaceRegexp.h"

#include "TokenList.h"
#include "ParsingBuffer.h"
#include "ParsingExceptions.h"

using namespace std;
using namespace casm;

int main() {
	//string tested = "$0 8 0xacd 0b1001 123h";
	ifstream in;
	in.open("test.asm");
	in.seekg(0, ios::end);
	int size = in.tellg();	
	ParsingBuffer input(size);
	in.seekg(0);
	in.read(&input.data[0], size);
	in.close();	

	//cout << &input.data[0] << endl;

	vector<shared_ptr<RegexpMachine>> regexpsTemplate;
	regexpsTemplate.push_back(shared_ptr<RegexpMachine>(new DecimalNumberRegexp()));
	regexpsTemplate.push_back(shared_ptr<RegexpMachine>(new BinaryNumberRegexp()));
	regexpsTemplate.push_back(shared_ptr<RegexpMachine>(new HexadecimalNumberRegexp()));
	regexpsTemplate.push_back(shared_ptr<RegexpMachine>(new RegisterRegexp()));
	regexpsTemplate.push_back(shared_ptr<RegexpMachine>(new NameRegexp()));
	regexpsTemplate.push_back(shared_ptr<RegexpMachine>(new WhiteSpaceRegexp()));
	regexpsTemplate.push_back(shared_ptr<RegexpMachine>(new NewlineRegexp()));

	//Keywords:
	regexpsTemplate.push_back(shared_ptr<RegexpMachine>(new KeywordRegexp(",", COMA, 0)));
	regexpsTemplate.push_back(shared_ptr<RegexpMachine>(new KeywordRegexp(":", COLON, 0)));

	//Mnemmonics
	regexpsTemplate.push_back(shared_ptr<RegexpMachine>(new KeywordRegexp("add", MNEMONIC, 0)));


	TokenList tokens;
	Token matched = { NONE, "", 0xffffffff };
	//for(unsigned int i = 0; i < tested.size(); i++) {
	vector<shared_ptr<RegexpMachine>> regexps(regexpsTemplate);
	bool afterEOF = false;
	while(!afterEOF) {
		char c = input.getChar();
		afterEOF = input.eof();

		for(unsigned int r = 0; r < regexps.size(); r++) {
			RMStatus res = regexps[r]->update(c, regexps);
			if(res == BROKEN) {
				regexps.erase(regexps.begin()+r);
				r--;
			} else if(res == FINISHED) {				
				Token current = regexps[r]->createToken(input.getCurrentString());
				//int cmp = matched.compareTo(current);
				if(current > matched) {
					matched = current;
				}
				regexps.erase(regexps.begin() + r);
				r--;
			}
		}
		if(regexps.size() == 0) {
			if(matched.type == NONE) {
				clog << "Error while parsing file: couldn't match token!" << endl;
				goto exit;
			} else {
				if(matched.type != SKIP)
					tokens << matched;
				input.advance(matched.image.size());
				matched = { NONE, "", 0xffffffff };
				for(int i = 0; i < regexpsTemplate.size(); i++) {
					regexpsTemplate[i]->reset();
				}
				regexps = vector<shared_ptr<RegexpMachine>>(regexpsTemplate);
			}
		}
	}
	exit:
	cout << "Matched tokens: " << endl;
	for(int i = 0; i < tokens.size(); i++) {
		cout << "[" << TOKEN_TYPE_NAMES.at(tokens[i].type) << ":" << tokens[i].image << "] ";
	}
	cin.sync();
	cin.ignore();
}

namespace casm {
	
	namespace ast {

		struct registerOperand {
		public:
			unsigned int reg;
		};

		struct numberOperand {
			int val;
		};

		struct operand {
			enum { REGISTER, NUMBER } type;
			union {
				registerOperand reg;
				numberOperand num;
			} op;
		};

		struct instruction {
		public:
			string op;
			vector<operand> operands;
			unsigned int pc;
		};
	}

	class Parse {

	public:
		TokenList tokens;
		vector<ast::instruction> instructions;
		map<string, ast::instruction*> labels;
		vector<string> pendingLabels;


		/* FILE := LINE+ END
		*/
		void file() {
			line();
			while(true) {
				Token& tok = tokens.lookahead(0);
				if(tok.type == END) {
					return;
				} else {
					line();
				}
			}
		}

		/* LINE := MNEMONIC [OPERAND ( COMA OPERAND)*] NEWLINE
		/          NAME COLON
		/          NEWLINE
		*/
		void line() {
			Token& tok = tokens.lookahead(0);
			switch(tok.type) {
				case MNEMONIC: {
					Token& mnem = tokens.next();
					ast::instruction instr;
					instr.op = mnem.image;
					if(operand_lookahead()) {
						ast::operand op = operand();
						while(true) {
							tok = tokens.next();
							if(tok.type == COMA) {
								operand();
							} else if(tok.type == NEWLINE) {
								return;
							} else {
								throw UnexpectedToken(tok.type);
							}
						}
					}
					break;
				}
				case NAME:
					tokens.next();
					tok = tokens.next();
					if(tok.type != COLON) {
						throw UnexpectedToken(COLON, tok.type);
					}
					break;

				case NEWLINE:
					tokens.next();
					break;

				default:
					throw UnexpectedToken(tok.type);
			}
		}

		/* OPERAND := DEC_NUMBER
		/             HEX_NUMBER
		/             BIN_NUMBER
		/             NAME
		/             REGISTER
		*/
		ast::operand operand() {
			Token& tok = tokens.next();
			switch(tok.type) {
				case DEC_NUMBER:
					return ast::operand{ ast::operand::NUMBER, {} };
				case HEX_NUMBER:
				case BIN_NUMBER:
				case NAME:
				case REGISTER:

					//return;
				default:
					throw UnexpectedToken(tok.type);
			}
		}

		bool operand_lookahead() {
			Token& tok = tokens.lookahead(0);
			switch(tok.type) {
				case DEC_NUMBER:
				case HEX_NUMBER:
				case BIN_NUMBER:
				case NAME:
				case REGISTER:
					return true;
				default:
					return false;
			}
		}

	};
}