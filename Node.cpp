#include "node.h"
#include <unordered_map>


Node::Node(bool terminal, tokennum tok)
{
	this->terminal = terminal;
	this->tok = tok;

}

void Node::addEdge(char c, Node* ptr)
{
	nextNode.insert(std::make_pair(c, ptr));
}

Node* Node::next(char t)
{
	std::unordered_map<char, Node*>::iterator it = nextNode.find(t);
	if (nextNode.count(t)) {
		return it->second;
	}
	else return nullptr;
}
