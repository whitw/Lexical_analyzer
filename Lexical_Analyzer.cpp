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

bool readable(string str) {
	return true;
}

void Lexical_Analyzer::readStr() {
	string::iterator cur = str.begin(); //LA had read till cur.
	string::iterator lastSuccess = str.begin();//last Success. for the string "43.t", lastSuccess is at str[1](detect INTVAL)
	string::iterator readFrom = str.begin();//
	Node* curN = start;
	Node* lastSuccessN = nullptr;
	
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
			//occurs when L={boooooooooooool} and S=booooooooooo
			//occurs when the input string is ["int], [@] or [43.t]  -->detect error!
			if (readFrom == lastSuccess) {
				//None of the prefixes of the string [lastSuccess, cur] were the lexeme. ["int], [@]
				//detect a single character as an error, and continue.
				if (!lexQueue.empty() && lexQueue.back().getTokenNum() == 0) {
					//merge lexeme with invalid tokens(== errors)
					lexeme lex = lexQueue.back();
					lexQueue.pop_back();
					lexQueue.push_back(lexeme(0, lex.getString() + string(readFrom, readFrom + 1)));
				}
				else lexQueue.push_back(lexeme(0, string(readFrom, readFrom + 1)));
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
