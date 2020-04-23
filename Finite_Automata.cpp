#include "Finite_Automata.h"
#include <fstream>
#include <cassert>
#include <tuple>
#include <iostream>
#include <iomanip>

Finite_Automata::Finite_Automata()
{
	nodeCnt = 0;
	nodelist = nullptr;
	startPt = nullptr;
}

Finite_Automata::Finite_Automata(string filename)
{
	nodeCnt = 0;
	nodelist = nullptr;
	startPt = nullptr;
	loadFromFile(filename);
}

Finite_Automata::~Finite_Automata()
{
	if (startPt) {
		clearNodes();
		//TODO: delete all Nodes with DFS (or BFS maybe?)
	}
}

void Finite_Automata::loadFromFile(string filename)
{
	if (startPt) {
		clearNodes();
	}
	nodelist = nullptr;
	ifstream inf;
	inf.open(filename, ios_base::in);
	if (inf.is_open()) {
		//Get node data
		inf >> nodeCnt;
		nodelist = new Node* [nodeCnt];
		for (int i = 0; i < nodeCnt; i++) {
			int nodeToken;
			inf >> nodeToken;
			if (nodeToken != 0)
				nodelist[i] = new Node(true, nodeToken);
			else nodelist[i] = new Node(false, 0);
		}
		//Get edges
		for (int i = 0; i < nodeCnt; i++) {
			int edgeCnt;
			char c;
			int dest;
			inf >> edgeCnt;
			for (int j = 0; j < edgeCnt; j++) {
				inf >> c >> dest;
				nodelist[i]->addEdge(c, nodelist[dest]);
			}
		}
		startPt = nodelist[0];
		inf.close();
	}
	else {
		std::cout << "file open failed";
	}
}

void Finite_Automata::clearNodes() {
	for (int i = 0; i < nodeCnt; i++) {
		delete  nodelist[i];
	}
	delete nodelist;
	nodeCnt = 0;
	nodelist = nullptr;
	startPt = nullptr;
}

ostream& operator<<(ostream& out, const lexeme& lex)
{
	out << setw(10) <<lex.getTokenName() << "|" << lex.getString() << endl;
	return out;
}

Lexical_Analyzer::Lexical_Analyzer(Finite_Automata& fa)
{
	start = fa.start();
	cur = start;
}

void Lexical_Analyzer::readStr(string string)
{
	//read string and place all lexemes into this->lexQueue
}

lexeme Lexical_Analyzer::next()
{
	assert(!lexQueue.empty());
	lexeme ret = lexQueue.front();
	lexQueue.pop();
	return ret;
}

Node::Node(bool terminal, tokennum tok)
{
	this->terminal = terminal;
	this->tok = tok;
	
}

void Node::addEdge(char c, Node* ptr)
{
	nextNode.insert(std::make_pair(c, ptr));
}

Node* Node::next(char t)
{
	std::unordered_map<char, Node*>::iterator it = nextNode.find(t);
	if (it == nextNode.end())
		return nullptr;
	else return it->second;
}
