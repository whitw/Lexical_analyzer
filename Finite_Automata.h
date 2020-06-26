#ifndef __FINITE_AUTOMATA_H__
#define __FINITE_AUTOMATA_H__

#include <queue>
#include "node.h"
#include "token.h"
using namespace std;

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

#endif
