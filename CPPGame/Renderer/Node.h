#ifndef SRC_COMMON_LIST_H
#define SRC_COMMON_LIST_H

#include <list>

template <typename Object>
class Node
{
public:
	Object data;
	
	Node* parent;
	
	std::list<Node*> children;

	Node(Object obj, Node* p = NULL)
		:data(obj), parent(p) { }

	void addChild(Node* child){
		children.push_back(child);
	}

	void deleteChild(Node* child){
		children.remove(child);
	}

};
#endif