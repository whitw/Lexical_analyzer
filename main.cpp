#include <iostream>
#include <fstream>
#include "Lexical_Analyzer.h"
#include "lexeme.h"
using namespace std;

int main(int argc, char* argv[]) {
	ifstream ifile;
	ofstream ofile;
	string ofname;
	string dfaname;
	string tokenname;
	ifile.open("whichDFA.txt"); //contains a filename for dfa, and tokens.
	ifile >> dfaname >> tokenname;
	ifile.close();
	TOKEN_NAME::readFromFile(tokenname); //init token
	Finite_Automata fi(dfaname); //init dfa
	Lexical_Analyzer lex(fi); //init lex

	//by arguments:
	//	./Lexical_Analyzer  --> input:stdin, output:stdout
	//	./Lexical_Analyzer file.xxx --> input:file.xxx, output:file.out
	//	./Lexical_Analyzer file.xxx file2.yyy --> input:file.xxx output:file2.yyy
	if (argc == 1) {
		string input;
		cout << "entering console mode: you can type any line you want to test." << endl;
		while (!cin.eof()) {
			cout << ">>";
			getline(cin, input);
			lex.readStr(input);
			while (!lex.isEnd()) {
				cout << lex.next();
			}
		}
		return 0;
	}	
	if(argc > 4) {
		cout << "usage:\n"
		     << "lexical_analyzer [opt:<input_file_name>] [opt:<output_file_name>]\n";
		return 0;
	}
	if(argc >= 2) {
		ifile.open(argv[1]);
		if (!ifile.is_open()) {
			cout << "Cannot open the file " << argv[1] << endl;
			return 0;
		}
	}
	if(argc == 2){
		string ifname = argv[1];
		if(ifname.find(".") == string::npos){
				ofname = ifname + ".out";
		}
		else{
			ofname = ifname.substr(0,ifname.find_last_of('.')) + ".out";
			if(ifname == ofname){
				ofname = ifname + ".out";
			}
		}
	}
	if(argc == 3){
		ofname = argv[2];
	}
	ofile.open(ofname);
	if(!ofile.is_open()){
		cout << "Cannot create the file" << ofname << endl;
		return 0;
	}
	//main algorithm of the program.
	//read a file and send to the lexical analyzer
	char input[1024];
	lexeme l;
	while(!ifile.eof()){
		ifile.read(input, 1024);
		lex.appendStr(string(input).substr(0, ifile.gcount()));
	}
	lex.readStr();
	string lexStr;
	//You can read lex with this format.
	while(!lex.isEnd()){
		l =  lex.next();
		ofile << l.getTokenNum() << " ";
		lexStr = l.getString();
		if(lexStr == "\n") ofile << "LF" << endl;
		else if(lexStr == "	") ofile << "TB" << endl;
		else if(lexStr == " ") ofile << "SP" << endl;
		else ofile << lexStr << endl;
	}
	cout << "Complete" << endl;
	
	fi.clearNodes();
	ifile.close();
	ofile.close();
	return 0;
}
