#include "lexical_analyzer.h"
#include <cassert>
#include <vector>
#include "lexeme.h"
#include "node.h"
using namespace std;

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
	vector<string::iterator> lnStart; //list of starting pointer(iterator) of the line.
	string::iterator cur = str.begin(); //LA had read till cur.
	string::iterator lastSuccess = str.begin();//last Success. for the string "43.t", lastSuccess is at str[1](detect INTVAL)
	string::iterator readFrom = str.begin();//processed [str.begin(), readFrom). Find lexeme at [readFrom, cur]
	Node* curN = start;
	Node* lastSuccessN = nullptr;
	
	/*initiate lnStart*/
	lnStart.push_back(str.begin());
	for (string::iterator i = str.begin(); i != str.end() && i + 1 != str.end(); i++) {
		if (i != str.begin() && *(i - 1) == '\r' && *i == '\n') {
			lnStart.push_back(i + 1);
		} //Windows \r\n
		else if (i != str.begin() && *(i - 1) != '\r' && *i == '\n') {
			lnStart.push_back(i + 1);
		} //Linux \n
		else if (i != str.end() && *i == '\r' && *(i+1) != '\n') {
			lnStart.push_back(i + 1);
		} //Mac \r
	}

	bool strEnded, readableNext;

	assert(curN != nullptr);              //failed to open dfa file. The program must have been terminated.
	assert(start->isTerminal() == false); //All lexical analyzer MUST not accept an empty string; infinite loop can occur.
	if (str.length() == 0) return;
	while (true) {
		assert(readFrom <= lastSuccess);
		assert(lastSuccess <= cur);       //find token at [readFrom, cur].
		assert(lastSuccessN != start);    //lastSuccessN == start if start->isTerminal() == false

		strEnded = (cur == str.end());
		if (!strEnded)
			readableNext = (curN->next(*cur) != nullptr);
		else readableNext = false;

		if (!strEnded && readableNext) {
			//can read one character.
			curN = curN->next(*cur);
			cur++;
			if (curN->isTerminal()) {
				lastSuccessN = curN;
				lastSuccess = cur;
			}
			continue;
		}
		//cannot read anymore. string ended, or cannot proceed a cursor from graph anymore.
		else if (curN->isTerminal()) {
			//detected lexeme successfully.
			lexQueue.push_back(lexeme(curN->getTokenNum(), string(readFrom, cur)));
			lastSuccess = readFrom = cur;
			curN = start;
			lastSuccessN = nullptr;
		}
		else {
			//occurs when L={boooooooooooool} and w=booooooooooo
			//occurs when the input string is ["int], [@] or [43.t]  -->detect error!
			if (readFrom == lastSuccess) {
				//None of the prefixes of the string [lastSuccess, cur] were the lexeme. ["int], [@]
				//detect a single character as an error, and continue.
				if (!lexQueue.empty() && lexQueue.back().getTokenNum() == 0) {
					//merge continuous lexemes with invalid tokens(== errors)
					lexeme lex = lexQueue.back();
					lexQueue.pop_back();
					lexQueue.push_back(lexeme(0, lex.getString() + string(readFrom, readFrom + 1)));
				}
				else {
					int line = 1, col = readFrom - str.begin() + 1;
					for (unsigned int i = 0; i < lnStart.size(); i++) {
						if (readFrom < lnStart[i]) {
							line = i;
							col = readFrom - lnStart[i - 1] + 1;
							break;
						}
					}
					lexQueue.push_back(lexeme(0, string(readFrom, readFrom + 1)));
					errQueue.push(make_pair(line, col));
				}
				lastSuccess = cur = readFrom = readFrom + 1;
				curN = start;
				lastSuccessN = nullptr;
			}
			else {
				// Start -> ... -> TerminalState -> ... nonTerminalState(cur). [43.t]
				// detect [Start ... LastTerminalState] an lexeme, and continue from the next character.
				lexQueue.push_back(lexeme(lastSuccessN->getTokenNum(), string(readFrom, lastSuccess)));
				cur = readFrom = lastSuccess;
				curN = start;
				lastSuccessN = nullptr;
			}
		}
		if (cur == str.end())
			break;
	}
}

lexeme Lexical_Analyzer::next()
{
	assert(!lexQueue.empty());
	lexeme ret = lexQueue.front();
	lexQueue.pop_front();
	return ret;
}

std::pair<int, int> Lexical_Analyzer::nextErr()
{
	assert(!errQueue.empty());
	std::pair<int, int> ret = errQueue.front();
	errQueue.pop();
	return ret;

}
