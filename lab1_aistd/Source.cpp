#include<iostream>
#include "Queue.h"
#include"RBnode.h"
#include"RBtree.h"

#include<string>
using namespace std;

int main()
{
	RBtree<int, char> t;
	cout << "insert nodes :" << endl;
	int mas[] = {32,15,17,64,20,13};
	for (int i = 0; i < 6; i++)
	{
		cout << mas[i] << ' ';
	}
	t.insert(32, 'm');
	t.insert(15, 'v');
	t.insert(17, 'k');
	t.insert(64, 't');
	t.insert(20, 'p');
	t.insert(13, 'q');
	cout << endl;
	cout << "what we got :" << endl;
	t.print();
	cout << endl;
	return 0;
}