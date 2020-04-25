#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <string>
#include <map>

using namespace std;

//Definition of Token types
using tokennum = int;

class TOKEN_NAME {
private:
	static std::map<int, string> tokens;
public:
	static void readFromFile(string filename);
	static string getString(const int tokenNum);
};

#endif
