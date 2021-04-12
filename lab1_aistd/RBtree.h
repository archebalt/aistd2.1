#pragma once

#include <iostream>
#include <string>
#include "Queue.h"


using namespace std;
template <typename KeyNode, typename ValueNode>
class RBtree
{
private:
	int size;
	RBnode<KeyNode, ValueNode>* root;
	RBnode<KeyNode, ValueNode>* nil;
public:
	RBtree()
	{
		root = nullptr;
		nil = nullptr;
		size = 0;
	}
	void leftTurn(RBnode<KeyNode, ValueNode>* x)
	{
		RBnode<KeyNode, ValueNode>* y = x->rightChild; 
		x->rightChild = y->leftChild;
		if (y->leftChild != nil) 
			y->leftChild->parent = x;
		y->parent = x->parent;
		if (x->parent == nil)
		{
			root = y;
		}
		else
		{
			if (x == x->parent->leftChild)
				x->parent->leftChild = y;
			else
				x->parent->rightChild = y;
		}
		y->leftChild = x;
		x->parent = y;
	}
	void rightTurn(RBnode<KeyNode, ValueNode>* x)
	{
		RBnode<KeyNode, ValueNode>* y = x->leftChild;
		x->leftChild = y->rightChild;
		if (y->rightChild != nil)
			y->rightChild->parent = x;
		y->parent = x->parent;
		if (x->parent == nil)
		{
			root = y;
		}
		else
		{
			if (x == x->parent->leftChild)
				x->parent->leftChild = y;
			else
				x->parent->rightChild = y;
		}
		y->rightChild = x;
		x->parent = y;
	}
	void insert(KeyNode key, ValueNode value)
	{
		RBnode<KeyNode, ValueNode>* z = new RBnode<KeyNode, ValueNode>; 
		z->KeyTree = key;
		z->ValueTree = value;
		if (size == 0)
		{
			nil = new RBnode<KeyNode, ValueNode>;
			nil->ColorNode = black;
			z->parent = nil;
			z->leftChild = nil;
			z->rightChild = nil;
			z->ColorNode = red;
			root = z;
			size++;
			insertCorrection(z);
		}
		else
		{
			try
			{
				
				RBnode<KeyNode, ValueNode>* x = root;
				RBnode<KeyNode, ValueNode>* y = x;
				while (x != nil)
				{
					y = x;
					if (z->KeyTree < x->KeyTree)
						x = x->leftChild;
					else if (z->KeyTree > x->KeyTree)
						x = x->rightChild;
					else
					{
						delete z;
						throw domain_error("already on the tree");
					}
				}
				z->parent = y;
				if (z->KeyTree < y->KeyTree)
					y->leftChild = z;
				else
					y->rightChild = z;
				z->leftChild = nil;
				z->rightChild = nil;
				z->ColorNode = Colors::red;
				size++; 
				insertCorrection(z);
			}
			catch (std::exception const& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}
	void insertCorrection(RBnode<KeyNode, ValueNode>* z)
	{
		while (z->parent->ColorNode == red)
		{
			if (z->parent == z->parent->parent->leftChild)
			{
				if ( z->parent->parent->rightChild->ColorNode == red)
				{
					z->parent->parent->rightChild->ColorNode = black;
					z->parent->parent->ColorNode = red;
					z->parent->ColorNode = black;
					z = z->parent->parent;
				}
				else if (z == z->parent->rightChild)
				{
					z = z->parent;
					leftTurn(z);
				}
				else if ( z == z->parent->leftChild)
				{
					z->parent->ColorNode = black;
					z->parent->parent->ColorNode = red;
					rightTurn(z->parent->parent);
				}
			}
			else 
			{
				if ( z->parent->parent->leftChild->ColorNode == red)
				{
					z->parent->parent->leftChild->ColorNode = black;
					z->parent->parent->ColorNode = red;
					z->parent->ColorNode = black;
					z = z->parent->parent;
				}
				else if ( z == z->parent->leftChild)
				{
					z = z->parent;
					rightTurn(z);
				}
				else if ( z == z->parent->rightChild)
				{
					z->parent->ColorNode = black;
					z->parent->parent->ColorNode = red;
					leftTurn(z->parent->parent);
				}
			}
		}
		root->ColorNode = black;
	}
	void remove(KeyNode key)
	{
		try
		{
			if (root == nullptr) return;
			if (root->rightChild == nil && root->leftChild == nil && root->KeyTree == key)
			{
				delete root;
				delete nil;
				nil = nullptr;
				root = nullptr;
				size--;
				return;
			}
			RBnode<KeyNode, ValueNode>* cur = root;
			while (cur != nil && cur->KeyTree != key)
			{
				if (key < cur->KeyTree)
					cur = cur->leftChild;
				else
					cur = cur->rightChild;
			}


			if (cur == nil)	
				throw std::domain_error("not on the tree");
			RBnode<KeyNode, ValueNode>* x;
			Colors deleteCur;
			if (cur->leftChild != nil && cur->rightChild != nil)
			{
				RBnode<KeyNode, ValueNode>* min = cur->rightChild;
				while (min->leftChild != nil)
				{
					min = min->leftChild;
				}
				KeyNode sup = cur->KeyTree;
				cur->KeyTree = min->KeyTree;
				min->KeyTree = sup;
				ValueNode sup2 = cur->ValueTree;
				cur->ValueTree = min->ValueTree;
				min->ValueTree = sup2;
				x = min->rightChild;
				x->parent = min->parent;
				if (min->parent->leftChild == min)
				{
					min->parent->leftChild = x;
				}
				else
				{
					min->parent->rightChild = x;
				}
				deleteCur = min->ColorNode;
				size--;
				delete min;
			}
			else if (cur->leftChild != nil)
			{
				x = cur->leftChild;
				x->parent = cur->parent;
				if (cur != root)
				{
					if (cur->parent->leftChild == cur) cur->parent->leftChild = x;
					else cur->parent->rightChild = x;
				}
				else
				{
					root = x;
				}
				deleteCur = cur->ColorNode;
				size--;
				delete cur;
			}
			else if (cur->rightChild != nil)
			{
				x = cur->rightChild;
				x->parent = cur->parent;
				if (cur != root)
				{
					if (cur->parent->leftChild == cur) cur->parent->leftChild = x;
					else cur->parent->rightChild = x;
				}
				else
				{
					root = x;
				}
				deleteCur = cur->ColorNode;
				size--;
				delete cur;
			}
			else
			{
				x = nil;
				x->parent = cur->parent;
				if (cur->parent->leftChild == cur) cur->parent->leftChild = x;
				else cur->parent->rightChild = x;
				size--;
				deleteCur = cur->ColorNode;
				delete cur;
			}
			if (deleteCur == Colors::black)
			{
				removeCorrection(x);
			}

		}
		catch (std::exception const& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	void removeCorrection(RBnode<KeyNode, ValueNode>* x)
	{
		RBnode<KeyNode, ValueNode>* w;
		while (x != root && x->ColorNode == black)
		{
			if (x->parent->leftChild == x)
			{
				w = x->parent->rightChild;
				if (w->ColorNode == Colors::red) 
				{
					w->ColorNode = Colors::black;
					x->parent->ColorNode = Colors::red;
					leftTurn(x->parent);
					w = x->parent->rightChild;
				}
				if (w != nil)
				{
					if (w->leftChild->ColorNode == Colors::black && w->rightChild->ColorNode == Colors::black)
					{
						w->ColorNode = Colors::red;
						x = x->parent;
					}
					else if (w->rightChild->ColorNode == Colors::black && w->leftChild->ColorNode == Colors::red) 
					{
						w->leftChild->ColorNode = Colors::black;
						w->ColorNode = Colors::red;
						rightTurn(w);
						w = x->parent->rightChild;
					}
					else if(w->rightChild->ColorNode == Colors::red)
					{
						w->ColorNode = x->parent->ColorNode;
						x->parent->ColorNode = Colors::black;
						w->rightChild->ColorNode = Colors::black;
						leftTurn(x->parent);
						x = root;
					}
				}
			}
			else
			{
				w = x->parent->leftChild;
				if (w->ColorNode == Colors::red)
				{
					w->ColorNode = Colors::black;
					x->parent->ColorNode = Colors::red;
					rightTurn(x->parent);
					w = x->parent->leftChild;
				}
				if (w != nil)
				{
					if (w->leftChild->ColorNode == Colors::black && w->rightChild->ColorNode == Colors::black)
					{
						w->ColorNode = Colors::red;
						x = x->parent;
					}
					else if (w->rightChild->ColorNode == Colors::red && w->leftChild->ColorNode == Colors::black)
					{
						w->rightChild->ColorNode = Colors::black;
						w->ColorNode = Colors::red;
						leftTurn(w);
						w = x->parent->leftChild;
					}
					else if (w->leftChild->ColorNode == Colors::red)
					{
						w->ColorNode = x->parent->ColorNode;
						x->parent->ColorNode = Colors::black;
						w->leftChild->ColorNode = Colors::black;
						rightTurn(x->parent);
						x = root;
					}
				}	
			}
		}
		x->ColorNode = Colors::black;
	}
	
	int* getKeys()
	{
		queue<KeyNode, ValueNode> q;
		q.push(root);
		int k = 0;
		int* mas = new int[size];

		RBnode<KeyNode, ValueNode>* v;
		while (!q.empty())
		{
			v = q.peek();
			q.pop();
			mas[k] = v->KeyTree;
			k++;

			if (v->leftChild != nil)
				q.push(v->leftChild);
			if (v->rightChild != nil)
				q.push(v->rightChild);
		}
		return mas;
	}
	ValueNode *getValues()
	{
		queue<KeyNode, ValueNode> q;
		q.push(root);

		int k = 0;
		ValueNode* mas = new ValueNode[size];

		RBnode<KeyNode, ValueNode>* v;
		while (!q.empty())
		{
			v = q.peek();
			q.pop();
			mas[k] = v->ValueTree;
			k++;

			if (v->leftChild != nil)
				q.push(v->leftChild);
			if (v->rightChild != nil)
				q.push(v->rightChild);
		}

		return mas;
	}
	void print()
	{
		queue<KeyNode, ValueNode> q;
		q.push(root);

			RBnode<KeyNode, ValueNode>* v;
		while (!q.empty())
		{
			v = q.peek();
			q.pop();
			cout << v->KeyTree << " ";

			if (v->leftChild != nil)
				q.push(v->leftChild);
			if (v->rightChild != nil)
				q.push(v->rightChild);
		}
	}
	bool find(KeyNode key)
	{
		RBnode<KeyNode, ValueNode>* cur = root;
		while (cur != nil)
		{
			if (key < cur->KeyTree)
				cur = cur->leftChild;
			else if (key > cur->KeyTree)
				cur = cur->rightChild;
			else
				return true;
		}
		return false;
	}
	void clear()
	{
		queue<KeyNode, ValueNode> q;
		q.push(root);

		RBnode<KeyNode, ValueNode>* v;
		while (!q.empty())
		{
			v = q.peek();
			q.pop();

			if (v->leftChild != nil)
				q.push(v->leftChild);
			if (v->rightChild != nil)
				q.push(v->rightChild);
			delete v;
		}
		root = nullptr;
		nil = nullptr;
		size = 0;
	}
	bool empty()
	{
		if (size == 0)
			return true;
		else
			return false;
	}
	~RBtree()
	{
		if (!empty())
			clear();
	}
	int Size()
	{
		return size;
	}
};
