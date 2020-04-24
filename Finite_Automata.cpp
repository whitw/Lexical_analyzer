#include "Finite_Automata.h"
#include <fstream>
#include <iostream>

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
