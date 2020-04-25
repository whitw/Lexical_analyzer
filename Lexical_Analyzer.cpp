#include "Lexical_Analyzer.h"
#include <cassert>
#include "lexeme.h"
#include "Node.h"

Lexical_Analyzer::Lexical_Analyzer(Finite_Automata& fa)
{
	start = fa.start();
}
void Lexical_Analyzer::readStr(string input)
{
	str = input;
	readStr();
}
void Lexical_Analyzer::appendStr(string input) {
	str.append(input);
}
void Lexical_Analyzer::readStr() {
	//read string and place all lexemes into this->lexQueue
	string::iterator i = str.begin();
	string::iterator readTill = str.begin();
	Node* cur = start;
	Node* testNode = start;
	//scan substring[readTill, i)

	string::iterator lastSuccess = str.begin(); //str[readTill,lastSuccess] is one lexeme
	Node* lastSuccessNode = nullptr;
	//if scanning [readTill, i) failed,
	//put substring [readTill, lastSuccess+1). and rescan from lastSuccess+1
	//if readTill == lastSuccess, report error and put substring [readTill, readTill+1) == [readTill], 
	//and rescan from readTill+1.
	while (true) {
		//test for i-th character, i-th node is cur->next(*i);
		assert(lastSuccessNode != start);
		assert(readTill <= lastSuccess);
		assert(lastSuccess <= i);
		if (i != str.end()) {
			//check for cur->next(*i);
			//state after reading i characters == testNode
			testNode = cur->next(*i);
			if (testNode != nullptr) {
				//not terminated yet. continue.
				if (testNode->isTerminal()) {
					lastSuccess = i;
					lastSuccessNode = testNode;
				}
				i++;
				cur = testNode;
			}
			else {
				if (cur->isTerminal()) {
					//[readTill, i) is valid lexeme.
					lexQueue.push(lexeme(cur->getTokenNum(), string(readTill, i)));
					lastSuccess = readTill = i;
					cur = start;
				}
				else {
					//[readTill, i) is NOT valid lexeme.
					//return to the last successful state.
					//if none of them were successful, report ONE character as an error and try again.
					if (lastSuccess != readTill) {
						lexQueue.push(lexeme(0, string(readTill, lastSuccess + 1)));
						lastSuccess = i = readTill = lastSuccess + 1;
					}
					else {
						lexQueue.push(lexeme(0, string(readTill, readTill + 1)));
						lastSuccess = i = readTill = readTill + 1;
					}
					cur = start;
				}
			}
		}
		else {
			//string ended. check for [readTill, str.end())
			if (cur->isTerminal()) {
				//[readTill, i) is valid lexeme.
				lexQueue.push(lexeme(cur->getTokenNum(), string(readTill, i)));
				lastSuccess = readTill = i;
				return;
			}
			else {
				//[readTill, i) is NOT valid lexeme.
				//return to the last successful state.
				//if none of them were successful, report ONE character as an error and try again.
				if (lastSuccessNode != nullptr) {
					if (readTill != str.end()) {
						lexQueue.push(lexeme(0, string(readTill, lastSuccess + 1)));
						lastSuccess = i = readTill = lastSuccess + 1;
					}
					else return;
				}
				else {
					if (readTill != str.end()) {
						lexQueue.push(lexeme(0, string(readTill, readTill + 1)));
						lastSuccess = i = readTill = readTill + 1;
					}
					else return;
				}
			}
		}
	}
}
lexeme Lexical_Analyzer::next()
{
	assert(!lexQueue.empty());
	lexeme ret = lexQueue.front();
	lexQueue.pop();
	return ret;
}
