#include<iostream>
using namespace std;

#include "unit_tests.h"

const int MAX_REC_COUNT = 100;

void test_sequential_CRUD_operations()
{
	node* root = NULL;
	for (int i = 0; i < MAX_REC_COUNT; i++)
	{
		int key = i;
		int val = i + 1;
		root = insert(root, key, val);
	}

	for (int i = 0; i < MAX_REC_COUNT; i++)
	{
		int key = i;
		int val = searchkey(root, key);
		assert(val == key + 1);
	}

	for (int i = 0; i < MAX_REC_COUNT; i++)
	{
		int key = i;
		root = delete_key(root, key);
	}

}

void test_user_operations()
{
	int user_op;
	node* root = NULL;
	do
	{
		cout << " Select Operations : " << endl;
		cout << "1. Insert or Update\n2. Search \n3. Delete \n4. Display \n5. Exit" << endl;
		cin >> user_op;
		switch (user_op) 
		{
			case 1 :
			{
				int key, val;
				cout << "Enter key and value : ";
				cin >> key >> val;
				root = insert(root, key, val);
				break;
			}
			case 2 :
			{
				int key, val;
				cout << "Enter key to search : ";
				cin >> key;
				val = searchkey(root, key);		
				break;
			}
			case 3 :
			{
				int key;
				cout << "Enter key to delete : ";
				cin >> key;
				root = delete_key(root, key);
				break;
			}
			case 4 :
			{
				display(root);
				break;
			}
			case 5 :
				break;
			default :
				cout << " Enter valid operation " << endl;
				break;
		}

	} while (user_op != 5);

}
