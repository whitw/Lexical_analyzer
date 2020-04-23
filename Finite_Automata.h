#ifndef __FINITE_AUTOMATA_H__
#define __FINITE_AUTOMATA_H__
#include <unordered_map>
#include "lexeme.h"
#include <queue>
using namespace std;


class Node {
private:
	bool terminal;
	tokennum tok;
	std::unordered_map<char, Node*> nextNode;
public:
	Node(bool terminal, tokennum tok);
	void addEdge(char, Node*);

	bool isTerminal() { return terminal; }
	tokennum getTokenNum() { return tok; }
	string getTokenName() { return TOKEN_NAME::getString(tok); }
	Node* next(char t);
};

class Finite_Automata {
	/*
	class Finite_Automata
	create graph consist of Node-s
	user only can initiate it with some proper file.
	TODO: maybe writeToFile(string filename)?
	*/
private:
	int nodeCnt;
	Node** nodelist;
	Node* startPt; //Start Node of the FA
public:
	Finite_Automata();
	Finite_Automata(string filename);
	void clearNodes();
	~Finite_Automata();
	Node* start() { return startPt; }; //return the starting Node.
	void loadFromFile(string filename);
};

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
	Node* cur;
	queue<lexeme> lexQueue;
	void resetCursor() { cur = start; }
public:
	Lexical_Analyzer(Finite_Automata& fi);
	void readStr(string string);
	lexeme next(); //get the lexeme from token Queue.
	bool isEnd() { return lexQueue.empty(); }
};
#endif