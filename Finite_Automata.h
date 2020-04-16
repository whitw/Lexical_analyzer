//TODO include
#include <unordered_map>
using namespace std;

class Finite_Automata {
private:
public:
};

class Node {
private:
	bool termination;
	std::unordered_map<char, Node*> next;
public:
};

