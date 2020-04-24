#ifndef __LEXEME_H__
#define __LEXEME_H__

#include <string>
#include "token.h"

//definition of the lexeme that Lexical_Analyzer returns.
using namespace std;
class lexeme {
private:
	tokennum token;
	string str;
public:
	lexeme() { this->token = 0; this->str = ""; }
	lexeme(tokennum token, string str) { this->token = token; this->str = str; }
	tokennum getTokenNum() const { return token; }
	string   getTokenName() const { return TOKEN_NAME::getString(token); }
	string   getString() const { return str; }
	friend ostream& operator<<(ostream& out, const lexeme& lex);
};
#endif