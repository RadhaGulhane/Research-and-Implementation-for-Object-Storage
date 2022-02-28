#include<iostream>
#include <iterator> 
#include<queue>
using namespace std;
#include "btree.h"

/**
 * @brief Provides the visualization for btree stucture.
 * 
 * This function uses breadth-first approach and prints keys and values present
 * in each node. 
 * 
 * @param root root node of btree
 */
void display(node* root)
{
	queue<node*> g;
	g.push(root);
	while (!g.empty()) 
	{
		node* n = g.front();
		g.pop();
		cout << "KEY-VALUE :";
		map<int, int> ::iterator itr2;
		for (itr2 = n->key_value.begin(); itr2 != n->key_value.end(); itr2++) {
			//cout<<itr2->first<<"  "<<itr2->second<<"      ";
			cout << itr2->first << "  ";
		}

		cout << "PIVOTS :";
		map<int, node*> ::iterator itr;
		for (itr = n->pivotmap.begin(); itr != n->pivotmap.end(); itr++) {
			cout << itr->first << "  ";
			g.push(itr->second);
		}

		cout << endl;
	}
	cout << '\n';
}

/**
 * @brief Split the node
 * Creates two new node and distribute the records present in @root into left
 * and right child equallly.
 * 
 * @param root node which we want to split
 * @return parent node
 */
node* split_node(node* root) //split root into two nodes
{

	int max_key_count = root->key_value.size();
	node* node1 = new node;
	map<int, int> ::iterator itr = root->key_value.begin();
	int firstpiv = itr->first;


	for (int i = 0; i < max_key_count / 2; i++)
	{
		node1->key_value[itr->first] = itr->second;

		itr++;

	}

	int tempkey = itr->first;
	int tempvalue = itr->second;
	itr++;
	node* node2 = new node;


	int secondpiv = itr->first;
	while (itr != root->key_value.end())
	{
		node2->key_value[itr->first] = itr->second;
		itr++;

	}
	root->key_value.clear();
	root->key_value[tempkey] = tempvalue;

	if (root->pivotmap.size() != 0)
	{
		map<int, node*> ::iterator itr2 = root->pivotmap.begin();

		for (int i = 0; i <= max_key_count / 2; i++)
		{
			node1->pivotmap[itr2->first] = itr2->second;
			itr2++;

		}

		while (itr2 != root->pivotmap.end())
		{
			node2->pivotmap[itr2->first] = itr2->second;
			itr2++;

		}

	}
	root->pivotmap.clear();

	root->pivotmap[firstpiv] = node1;
	root->pivotmap[secondpiv] = node2;

	return root;
}

/**
 * @brief Searches for given key and provides value for it.
 * 
 * @param root root node of btree
 * @param key key which need to be searched in btree
 * @return int return error code, KEY_NOT_FOUND if key not present else returns 
 * 			value
 */
int searchkey(node* root, int key)
{
	if (root == NULL)
	{
		cout << "key is not present. rc = "<< KEY_NOT_FOUND << endl;
		return KEY_NOT_FOUND;
	}
	auto itr = root->key_value.find(key);
	if (itr != root->key_value.end())
	{
		//cout << "Value of given key : " << itr->second << endl;

		return itr->second;
	}
	else //find appropriate child to find key
	{
		if (root->pivotmap.size() != 0)
		{
			auto itr2 = root->pivotmap.begin();
			for (auto itr = root->key_value.begin(); itr != root->key_value.end(); itr++)
			{
				if (itr->first > key)
				{
					break;
				}
				itr2++;
			}

			return searchkey(itr2->second, key);
		}
		else
		{
			cout << "key is not present. rc = "<< KEY_NOT_FOUND << endl;
			return KEY_NOT_FOUND;
		}
	}
}

/**
 * @brief Deletes the record with given key from btree
 * 
 * @param root root node of btree
 * @param key key to get record
 * @return node* returns root node of btree
 */
node* delete_key(node* root, int key)
{
	if (root == NULL)
	{
		cout << "key is not present. rc = "<< KEY_NOT_FOUND << endl;
		return NULL;
	}
	auto itr = root->key_value.find(key);
	if (itr != root->key_value.end())
	{
		/* If we found the key and 
			if we are at leaf node, simply delete the key-value and retun root.
			else delete the key-value and adjust the pivot node.
		*/
		if (root->pivotmap.size() == 0)
		{
			/* if we are at leaf node */
			root->key_value.erase(key);
		}
		else
		{
			/* we are at internal node. */
			root->key_value.erase(key);

			auto itr2 = root->pivotmap.begin(); //change this to itr of buffer
			while (itr2->second->key_value.begin()->first < key)
			{
				itr2++;

			}
			auto right = itr2;
			auto left = --itr2;
			int key_, value_;
			if (right->second->key_value.size() - 1 >= MAX_SIZE / 2)
			{
				auto minfromright = right->second->key_value.begin();
				key_ = minfromright->first;
				value_ = minfromright->second;
				root->key_value[key_] = value_;
				right->second = delete_key(right->second, key_);
			}
			else
			{
				auto maxfromleft = left->second->key_value.rbegin();
				key_ = maxfromleft->first;
				value_ = maxfromleft->second;
				root->key_value[key_] = value_;
				left->second = delete_key(left->second, key_);
			}

			/* If underflow occures at left child, merge left, root, right nodes. */
			if (left->second->key_value.size() < MAX_SIZE / 2)
			{
				left->second->key_value.insert(right->second->key_value.begin(), right->second->key_value.end());
				left->second->pivotmap.insert(right->second->pivotmap.begin(), right->second->pivotmap.end());
				left->second->key_value[key_] = value_;
				root->key_value.erase(key_);
				root->pivotmap.erase(right->first);
			}

			/* Handle the case where root contains only one child pointer. */
			if (root->key_value.size() == 0)
			{
				delete root;
				root = NULL;
				return left->second;
			}
			return root;

		}

		return root;
	}
	else
	{
		if (root->pivotmap.size() == 0)
		{
			cout << "key is not present. rc = "<< KEY_NOT_FOUND << endl;
			return root;
		}

		/* find appropriate child to find key. */
		auto itr2 = root->pivotmap.begin();
		auto itr = root->key_value.begin();
		for (; itr != root->key_value.end(); itr++)
		{
			if (itr->first > key)
			{
				break;
			}
			itr2++;
		}
		itr2->second = delete_key(itr2->second, key);


		if (itr2->second->pivotmap.size() == 0)//if leaf node
		{
			if (itr2->second->key_value.size() < MAX_SIZE / 2)
			{
				int flag = 0;
				auto curr = itr2;

				if (itr2 != root->pivotmap.begin())
				{
					auto prev_sibling = --curr;
					if (prev_sibling->second->key_value.size() - 1 >= MAX_SIZE / 2)
					{

						itr--;
						itr2->second->key_value[itr->first] = itr->second;
						root->key_value.erase(itr->first);
						/* assign last key of perv_sibling's key value */
						auto temp = prev_sibling->second->key_value.rbegin();
						root->key_value[temp->first] = temp->second;
						prev_sibling->second->key_value.erase(temp->first);
						flag = 1;

					}
				}
				if (flag == 0)
				{

					auto curr = itr2;
					auto next_sibling = ++curr;
					if (next_sibling != root->pivotmap.end())
					{

						if (next_sibling->second->key_value.size() - 1 >= MAX_SIZE / 2)
						{

							itr2->second->key_value[itr->first] = itr->second;
							root->key_value.erase(itr->first);
							auto temp = next_sibling->second->key_value.begin();
							root->key_value[temp->first] = temp->second;
							next_sibling->second->key_value.erase(temp->first);
							flag = 1;
						}
					}
				}
				if (flag == 0)
				{

					auto curr = itr2;
					auto sibling = ++curr;
					int key_, value_;
					if (sibling != root->pivotmap.end())
					{
						key_ = itr->first;
						value_ = itr->second;


					}
					else
					{
						auto curr = itr2;
						sibling = --curr;
						auto temp = itr;
						temp--;
						key_ = temp->first;
						value_ = temp->second;

					}
					//merging

					itr2->second->key_value.insert(sibling->second->key_value.begin(), sibling->second->key_value.end());

					itr2->second->key_value[key_] = value_;
					root->pivotmap.erase(sibling->first);

					root->key_value.erase(key_);
					if (root->key_value.size() == 0)
					{
						return itr2->second;
					}

				}

				return root;

			}
		}
		else
		{

			if (itr2->second->key_value.size() < MAX_SIZE / 2)
			{
				//merge and return
				//merge root, and two sibling
				//after merging if overflow occur at child split and add one key to root

				//1.find sibling and appropriate key from root
				int piv_sibling, key_, value_;
				if (itr != root->key_value.end())
				{
					auto curr = itr2;
					curr++;
					piv_sibling = curr->first;
					key_ = itr->first;
					value_ = itr->second;
				}
				else
				{
					auto curr = itr2;
					curr--;
					piv_sibling = curr->first;
					auto temp = itr;
					temp--;

					key_ = temp->first;
					value_ = temp->second;

				}
				node* sibling = root->pivotmap[piv_sibling];
				//2.merge 
				itr2->second->key_value.insert(sibling->key_value.begin(), sibling->key_value.end());
				itr2->second->pivotmap.insert(sibling->pivotmap.begin(), sibling->pivotmap.end());
				itr2->second->key_value[key_] = value_;
				root->key_value.erase(key_);
				root->pivotmap.erase(piv_sibling);
				//if overflow occur then split 
				if (itr2->second->key_value.size() >= MAX_SIZE)
				{
					node* temp = split_node(itr2->second);
					root->pivotmap.erase(itr2->first); //can delete or free space itr->second
					root->key_value.insert(temp->key_value.begin(), temp->key_value.end());
					root->pivotmap.insert(temp->pivotmap.begin(), temp->pivotmap.end());
				}
				//ifkeybalue at root ==0... return itr2->second
				if (root->key_value.size() == 0)
				{
					root = NULL;
					//delete root;
					return itr2->second;
				}
				return root;
			}

		}
		return root;
	}
}

/**
 * @brief Inserts the new record on bttree
 * 
 * @param root root node of btree
 * @param key key of record
 * @param value value of record
 * @return node* root node of btree
 */
node* insert(node* root, int key, int value)
{
	if (root == NULL)
	{
		root = new node;
		root->key_value[key] = value;
		return root;
	}
	else {
		if (root->pivotmap.size() == 0)//if leaf node
		{
			root->key_value[key] = value;
			if (root->key_value.size() > MAX_SIZE - 1)
			{
				/* If we overflowed, split the node. */
				root = split_node(root);
			}
			return root;
		}
		else {

			/* find approriate child to insert */
			int count = 0;
			auto itr2 = root->pivotmap.begin();
			for (auto itr = root->key_value.begin(); itr != root->key_value.end(); itr++)
			{
				if (itr->first > key)
				{
					break;
				}
				count++;
				itr2++;
			}
			//cout<<"piv"<<itr2->first<<"  ";
			node* temp = insert(itr2->second, key, value);

			int min_key = (MAX_SIZE % 2) ? MAX_SIZE / 2 : MAX_SIZE / 2 - 1;

			/* Handle node splitting */
			if (temp->key_value.size() < min_key) //merging with root.. balancing
			{
				/* add keyvalue to new key_value and pivot to root */
				
				root->pivotmap.erase(itr2->first);
				root->key_value.insert(temp->key_value.begin(), temp->key_value.end());
				root->pivotmap.insert(temp->pivotmap.begin(), temp->pivotmap.end());
				temp = NULL;
				delete temp;

				/* If overflow at internal node, split and return root */
				if (root->key_value.size() >= MAX_SIZE)
				{
					root = split_node(root);
				}
				return root;

			}
			else
			{
				itr2->second = temp;
				return root;

			}

		}
	}
}

