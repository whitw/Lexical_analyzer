#include <string>
using namespace std;

enum TOKEN_NAME {
	INT,    CHAR,    BOOL,    FLOAT,
	INTVAL, CHARVAL, BOOLVAL, FLOATVAL, //CHARVAL: "~"
	IDENTIFIER,
	
	IF, ELSE, WHILE, FOR,
	RETURN,

	ARI_PLUS, ARI_MINUS,
	ARI_MUL, ARI_DIV,

	BIT_SHL, BIT_SHR,
	BIT_AND, BIT_OR,
	
	ASSIGN,
	
	CMP_LT,  CMP_GT,
	CMP_EQ,  CMP_NE,
	CMP_LTE, CMP_GTE,
	
	SEMICOLON, //;
	LBRACKET, RBRACKET, //{}
	LPAREN, RPAREN, // ()
	COMMA,
	
	TAB, LF, SPACE
};

class Lexeme {
private:
	TOKEN_NAME token;
	string     lexeme;
public:

};