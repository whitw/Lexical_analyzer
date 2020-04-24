#ifndef __LEXICAL_ANALYZER_H__
#define __LEXICAL_ANALYZER_H__

#include "Finite_Automata.h"
#include "Node.h"
#include <queue>
#include "token.h"
#include "lexeme.h"

class Lexical_Analyzer {
	/*
	usage:
	lex.readStr("int a = 3; if(a = 7){return a;}");
	while(!lex.isEnd()){
		std::cout << lex.next();
	}
	*/
private:
	Node* start;
	std::queue<lexeme> lexQueue;
public:
	Lexical_Analyzer(Finite_Automata& fi);
	void readStr(string string);
	lexeme next(); //get the lexeme from token Queue.
	bool isEnd() { return lexQueue.empty(); }
};
#endif