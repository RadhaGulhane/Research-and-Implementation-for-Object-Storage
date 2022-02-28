#include<iostream>
using namespace std;
#include "unit_tests.h"

int main()
{
	
	cout << "Started ut-test_sequential_CRUD_operations..." << endl;
	test_sequential_CRUD_operations();
	cout << "Successfully completed ut-test_sequential_CRUD_operations." << endl << endl;

	cout << "Started ut-test_user_operation..." << endl;
	test_user_operations();
	cout << "Successfully completed ut-test_user_operations()." << endl << endl;

	return 0;
}