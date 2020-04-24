#include <iostream>
#include <fstream>
#include "Lexical_Analyzer.h"
#include "lexeme.h"
using namespace std;

int main(int argc, char* argv[]) {
	string line;
	ifstream ifile;
	string dfaname;
	ifile.open("whichDFA.txt");
	ifile >> dfaname;
	ifile.close();
	Finite_Automata fi(dfaname);
	Lexical_Analyzer lex(fi);
	
	if (argc == 1) {
		string input;
		while (!cin.eof()) {
			getline(cin, input);
			lex.readStr(input);
			while (!lex.isEnd()) {
				cout << lex.next();
			}
		}
	}
	if(argc == 2) {
		ifile.open(argv[1]);
		if (!ifile.is_open()) {
			cout << "Cannot open the file " << argv[1] << endl;
			return 0;
		}
	}
	else {
		cout << "usage:\n"
		     << "lexical_analyzer <input_file_name>\n"
			 << "output:\n"
			 << "<input_file_name.out>]\n";
		return 0;
	}
	//TODO: Test Code here

	ifile.close();
	return 0;
}