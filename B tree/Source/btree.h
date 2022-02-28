#include <map> 

const int MAX_SIZE = 5; /* MAX_SIZE = order of btree */
enum RETURN_CODE
{
	SUCCESS            = 0,
	KEY_NOT_FOUND      = -2,
	KEY_ALREADY_EXISTS = -3,

};

struct node
{
	map<int, int> key_value;
	map<int, node*>pivotmap;
};

/* Displays whole b-tree visualization. */
void display(node* root);

/**
Inserts or Updates key. If key is already present this function will update the key with provided value.
If key is not already present in the b-tree, it will insert new key with provided value.
*/
node* insert(node* root, int key, int value);

/*
Searches for required value using provided key. If key is not oresent, 
it will return KEY_NOT_FOUND else it willl return value associated with key
*/
int searchkey(node* root, int key);

/* Deletes the key-value from b-tree. */
node* delete_key(node* root, int key);