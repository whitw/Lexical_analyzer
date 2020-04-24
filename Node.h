#ifndef __NODE_H__
#define __NODE_H__
#include <unordered_map>
#include "token.h"

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
#endif