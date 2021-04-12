#pragma once
#include <iostream>
#include "RBnode.h"

template <typename KeyNode, typename ValueNode>

class queue
{

private:
	nodeQueue<KeyNode, ValueNode> *head;
	nodeQueue<KeyNode, ValueNode> *tail;
	int size;
public:
	
	queue()
	{

		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	void push(RBnode<KeyNode, ValueNode>* data)
	{
		nodeQueue<KeyNode, ValueNode>* add = new nodeQueue<KeyNode, ValueNode>;
		add->data = data;
		if (head == nullptr)
		{
			tail = head = add;
			head->next = nullptr;
		}
		else
		{
			add->next = tail;
			tail = add;
		}
		size++;
	}
	void pop()
	{
		if (size > 0)
		{
			if (size == 1)
			{
				delete head;
				head = nullptr;
				tail = nullptr;
			}
			else
			{
				nodeQueue<KeyNode, ValueNode>* beforeHead = nullptr;
				for (nodeQueue<KeyNode, ValueNode> *curr = tail; curr != head ;curr = curr->next)
				{
					if (curr != head)
					{
						beforeHead = curr;
					}
				}
				delete head;
				head = beforeHead;
				head->next = nullptr;
			}
			size--;
		}
	}
	void clear()
	{
		while (size != 0)
		{
			pop();
		}
	}
	RBnode<KeyNode,ValueNode>* peek()
	{
		if (size != 0)
		{
			return head->data;
		}
	}

	bool empty()
	{
		if (size == 0)
		{
			return true;
		}
		return false;
	}
	int Size()
	{
		return size;
	}

};
