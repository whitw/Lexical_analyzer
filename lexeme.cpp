#include "lexeme.h"
#include <iomanip>

ostream& operator<<(ostream& out, const lexeme& lex)
{
	out << setw(10) << lex.getTokenName() << "|" << lex.getString() << endl;
	return out;
}

