#ifndef __LEXICAL_ANALYZER_H__
#define __LEXICAL_ANALYZER_H__

#include "finite_automata.h"
#include "node.h"
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
	Node* start; //start state of the dfa structure
	std::deque<lexeme> lexQueue; //output lexemes
	std::queue<pair<int, int>> errQueue;  //error positions
	string str; //input string
public:
	Lexical_Analyzer(Finite_Automata& fi);
	void readStr(string string);
	void appendStr(string string);
	void readStr(); //use after appendStr(someString);
	lexeme next(); //get the lexeme from token Queue.
	std::pair<int, int> nextErr();
	bool isEnd() { return lexQueue.empty(); }
};
#endif
