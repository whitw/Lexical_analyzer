#include "finite_automata.h"
#include <fstream>
#include <iostream>
#include <cassert>

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
			string c;
			int dest;
			inf >> c >> edgeCnt;
			for (int j = 0; j < edgeCnt; j++) {
				inf >> c >> dest;
				if (c.length() == 2) {
					if (c == "TB") {
						nodelist[i]->addEdge('\t', nodelist[dest]);
					}
					if (c == "LF") {
						nodelist[i]->addEdge('\n', nodelist[dest]);
					}
					if (c == "SP") {
						nodelist[i]->addEdge(' ', nodelist[dest]);
					}
					if (c == "CR") {
						nodelist[i]->addEdge('\r', nodelist[dest]);
					}
				}
				else if (c.length() == 3) {
					if (c[1] != '-') { std::cout << "file read failed:: at node " << dest << ":" << c
						                         << "," << "NOT d-d format" << endl; return; }
					else
						if (c[0] > c[2]) { std::cout << "file read failed:: at node " << dest << ":" << c
							                     << "," << c[0] <<"-" << c[1] << ":left one is bigger" << endl; return; }
						else {
							for (char k = c[0]; k <= c[2]; k++) {
								nodelist[i]->addEdge(k, nodelist[dest]);
							}
						}
				}
				else {
					if (c.length() != 1) { std::cout << "file read failed:: at node " << dest << ":" << c
						                             << "incorrect edge format: length is " << c.length() << endl; return; }
					nodelist[i]->addEdge(c[0], nodelist[dest]);
				}
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
