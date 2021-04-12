#pragma once

#include <iostream>
enum Colors { red, black };
template <typename KeyNode, typename ValueNode>


class RBnode
{
public:

	RBnode *parent;
	RBnode *leftChild;
	RBnode* rightChild;
	KeyNode KeyTree;
	ValueNode ValueTree;
	Colors ColorNode;
};

template <typename KeyNode, typename ValueNode>
class nodeQueue
{
public:
	nodeQueue* next;
	RBnode<KeyNode, ValueNode>* data;
	nodeQueue()
	{
		next = nullptr;
		data = nullptr;
	}
};

