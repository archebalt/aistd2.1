#include "pch.h"
#include "CppUnitTest.h"
#include "..\lab1_aistd\RBtree.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(INSERT)
		{
			RBtree<int, char> t;
			t.insert(32, 'm');
			t.insert(15, 'v');
			t.insert(17, 'k');
			t.insert(64, 't');
			t.insert(20, 'p');
			t.insert(13, 'q');
			int* mas = t.getKeys();
			int mas2[] = { 17, 15, 32, 13, 20, 64 };
			for (int i = 0; i < t.Size(); i++)
			{
				Assert::AreEqual(mas[i], mas2[i]);
			}
		}
		TEST_METHOD(REMOVE)
		{
			RBtree<int, char> t;
			t.insert(32, 'm');
			t.insert(15, 'v');
			t.insert(17, 'k');
			t.insert(64, 't');
			t.insert(20, 'p');
			t.insert(13, 'q');
			t.remove(15);
			int* mas = t.getKeys();
			int mas2[] = { 17, 13, 32, 20, 64 };
			for (int i = 0; i < t.Size(); i++)
			{
				Assert::AreEqual(mas[i], mas2[i]);
			}
		}	
		TEST_METHOD(CLEAR)
		{
			RBtree<int, char> t;
			t.insert(32, 'm');
			t.insert(15, 'v');
			t.insert(17, 'k');
			t.clear();
			int k = 0;
			Assert::AreEqual(t.Size(), k);
		}
		TEST_METHOD(GET_VALUES)
		{
			RBtree<int, char> t;
			t.insert(32, 'm');
			t.insert(15, 'v');
			t.insert(17, 'k');
			t.insert(64, 't');
			t.insert(20, 'p');
			t.insert(13, 'q');
			char* mas = t.getValues();
			char mas2[] = { 'k','v','m','q','p','t' };
			for (int i = 0; i < t.Size(); i++)
			{
				Assert::AreEqual(mas[i], mas2[i]);
			}
		}
		TEST_METHOD(FIND)
		{
			RBtree<int, char> t;
			t.insert(32, 'm');
			t.insert(15, 'v');
			t.insert(17, 'k');
			t.insert(64, 't');
			t.insert(20, 'p');
			t.insert(13, 'q');
			bool a = t.find(17);
			Assert::IsTrue(a == true);
			a = t.find(1000);
			Assert::IsTrue(a == false);
		}
	};
}
