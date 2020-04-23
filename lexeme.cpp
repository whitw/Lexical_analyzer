#include "lexeme.h"

string TOKEN_NAME::getString(int tokenNum)
{
	auto i = tokens.find(tokenNum);
	if (i == tokens.end())
		return "ERROR";
	else return i->second;
}

std::map<tokennum, string> TOKEN_NAME::tokens = {
			{0, "INVALID"},
			{1, "INT"},
			{2, "CHAR"},
			{3, "BOOL"},
			{4, "FLOAT"},
			{5, "INTVAL"},
			{6, "CHARVAL"},
			{7, "BOOLVAL"},
			{8, "FLOATVAL"},
			{9, "IDENTIFIER"},
			{10, "IF"},
			{11, "ELSE"},
			{12, "WHILE"},
			{13, "FOR"},
			{14, "RETURN"},
			{15, "ARI_ADD"},
			{16, "ARI_SUB"},
			{17, "ARI_MUL"},
			{18, "ARI_DIV"},
			{19, "BIT_SHL"},
			{20, "BIT_SHR"},
			{21, "BIT_AND"},
			{22, "BIT_OR"},
			{23, "ASSIGN"},
			{24, "CMP_LT"},
			{25, "CMP_GT"},
			{26, "CMP_EQ"},
			{27, "CMP_NE"},
			{28, "CMP_LTE"},
			{29, "CMP_GTE"},
			{30, "SEMICOLON"},
			{31, "LBRACKET"},
			{32, "RBRACKET"},
			{33, "LPAREN"},
			{34, "RPAREN"},
			{35, "COMMA"},
			{36, "TAB"},
			{37, "LF"},
			{38, "SPACE"}
};