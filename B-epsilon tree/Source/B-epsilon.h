#include<iostream> 
#include <map> 
using namespace std;


/**
 * Considering max pivots per node = 3 and max buffer size = 3 messages for 
 * this implementation
 */

struct msg
{
	int value;
	int opcode;
};

struct node
{
	map<int, msg> buffer;

	map<int, node*> pivotmap;
};

node* insert(node* root, int key, int value, int opcode);
int searchKey(node* root, int key);
void show(node* root);



