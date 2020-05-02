#include "lexeme.h"
#include <iomanip>

ostream& operator<<(ostream& out, const lexeme& lex)
{
	out << setw(10) << lex.getTokenName() << "|" << lex.getString() << endl;
	return out;
}

string lexeme::getString() const
{
	if (str == "\r") return "CR";
	else if (str == "\n") return "LF";
	else if (str == "	") return "TB";
	else if (str == " ") return "SP";
	return str;
}
