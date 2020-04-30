#include "token.h"
#include <tuple>
#include <iostream>
#include <fstream>
using namespace std;
string TOKEN_NAME::getString(const int tokenNum) {
	auto i = tokens.find(tokenNum);
	if (i == tokens.end())
		return "ERROR";
	else return i->second;
}

void TOKEN_NAME::readFromFile(string filename) {
	ifstream ifile;
	ifile.open(filename);
	int token;
	string tokenName;
	if(!ifile.is_open()){
		std::cout << "Cannot open token file " << filename;
		return;
	}
	tokens.clear();
	while(!ifile.eof()){
		ifile >> token >> tokenName;
		tokens.insert(std::make_pair(token, tokenName));
	}
	ifile.close();
}
std::map<tokennum, string> TOKEN_NAME::tokens = {};
