#ifndef __LEXEME_H__
#define __LEXEME_H__
#include <string>
#include <map>

using namespace std;

//contains the type of tokens that lexical analyzer can return.
using tokennum = int;

class TOKEN_NAME {
private:
	static std::map<int, string> tokens;
public:
	static string getString(int tokenNum);
};

#endif