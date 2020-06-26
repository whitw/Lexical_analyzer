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
	pair<int, int> pos;
public:
	lexeme() { this->token = 0; this->str = ""; this->pos = make_pair(-1, -1); }
	lexeme(tokennum token, string str, pair<int, int> pos) { this->token = token; this->str = str; this->pos = pos; }
	tokennum getTokenNum() const { return token; }
	string   getTokenName() const { return TOKEN_NAME::getString(token); }
	pair<int,int> getPos() const { return pos; }
	string   getString() const;
	friend ostream& operator<<(ostream& out, const lexeme& lex);
};
#endif