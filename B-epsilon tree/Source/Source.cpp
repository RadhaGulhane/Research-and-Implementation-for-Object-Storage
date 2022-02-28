#include<iostream>
using namespace std;
#include<assert.h>
#include "B-epsilon.h"

const int MAX_SAMPLES = 2000;

/* Perform sequential insert and search operation */
void user_test_1()
{
	node* root = NULL;

	for (int i = 0; i < MAX_SAMPLES; i++)
	{
		int key = i, value = i;
		root = insert(root, key, value, 0);
	}

	for (int i = 0; i < 2000; i++)
	{
		int val = searchKey(root, i);
		assert(val == i);
		if (val != i)
		{
			cout << "key : " << i << " val : " << val << endl;
		}
	}
	cout<<"Completed user_test_1 successfully."<<endl;
}

/* Perfrom operation by taking inputs from user.*/
void user_test_2()
{
	int user_op;
	node* root = NULL;
	do
	{
		cout << " Select Operations : " << endl;
		cout << "1. Insert \n2. Search \n3. Display \n4. Exit" << endl;
		cin >> user_op;
		switch (user_op) 
		{
			case 1 :
			{
				int key, val;
				cout << "Enter key and value : ";
				cin >> key >> val;
				root = root = insert(root, key, val, 0);
				break;
			}
			case 2 :
			{
				int key, val;
				cout << "Enter key to search : ";
				cin >> key;
				val = searchKey(root, key);	
				break;
			}
			case 3 :
			{
				show(root);
				break;
			}
			case 4 :
				break;
			default :
				cout << " Enter valid operation " << endl;
				break;
		}

	} while (user_op != 4);
}

int main()
{
	user_test_1();
	user_test_2();

}