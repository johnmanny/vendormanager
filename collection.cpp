/*
	Author: John Nemeth
	Sources: Class Material
	Description: implementation file for collection class
*/
#include "collection.h"
#include <fstream>
#include <iomanip>
#include <cstring>
#include <iostream>

//constructors/destructors/////////////////////////////////////////////////////////////////
//constructor
collection::collection()
{
	root = NULL;
	head = NULL;
	size = 0;
}

//copy constructor for passed filename to load from file
collection::collection(char * fileName)
{
	root = NULL;
	head = NULL;
	size = 0;
	ifstream in;
	vendor aVendor;
	char name[MAX], products[MAX], events[MAX], aPhone[MAX];
	in.open(fileName);
	in.get(name, MAX, ';');
	while(!in.eof())
	{
		in.ignore(MAX, ';');
		in.get(aPhone, MAX, ';');
		in.ignore(MAX, ';');
		in.get(products, MAX, ';');
		in.ignore(MAX, ';');
		in.get(events, MAX, '\n');
		in.ignore(MAX, '\n');
		aVendor.setName(name);
		aVendor.setProductTypes(products);
		aVendor.setEvents(events);
		aVendor.setPhone(aPhone);
		add(aVendor);
		
		in.get(name, MAX, ';');
	}
	in.close();
}

//copy constructor for passed collection class
collection::collection(const collection& theCollection)
{
	root = NULL;
	head = NULL;
	size = theCollection.size;

	*this = theCollection;	
}

//destructor
collection::~collection()
{
	destroyTree(root);
	destroyList(head);
}

//utility mutator functions for data structures///////////////////////////////////////////////////////////////
//destroy tree recursively
void collection::destroyTree(treeNode *& tempNode)
{
	if (tempNode)
	{
		destroyTree(tempNode->left);
		destroyTree(tempNode->right);
		delete tempNode;
	}
}

//destroy list recursively
void collection::destroyList(linkedListNode *& node)
{
	if (node)
	{
		destroyList(node->next);
		delete node->entry;
		delete node;
	}
}

//recursive copy tree function for assignment func
void collection::copyTree(treeNode *& rootNew, treeNode * node)
{
	if (node)
	{
		rootNew = new treeNode;
		rootNew->entry = node->entry;
		copyTree(rootNew->left, node->left);
		copyTree(rootNew->right, node->right);
	}
	else
		rootNew = NULL;
}

//recursive copy list function for assignment func
void collection::copyList(linkedListNode *& headNew, linkedListNode * node)
{
	if (node)
	{
		headNew = new linkedListNode;
		headNew->entry = node->entry;
		copyList(headNew->next, node->next);
	}
	else
		headNew = NULL;
}

//mutators///////////////////////////////////////////////////////////////////////////////////////////
//initial add function
void collection::add(const vendor& aVendor)
{
	char entryName[MAX], tempName[MAX];
	vendor * ptrVendor = new vendor;
	*ptrVendor = aVendor;
	ptrVendor->getName(entryName);
	addToList(ptrVendor);
	addToTree(root, entryName, tempName, ptrVendor);
	size++;
}

//recursive add to tree function
void collection::addToTree(treeNode *& tree, char * entName, char * treeName, vendor * entryPtr)
{
	 if (tree)
	 	tree->entry->getName(treeName);
	 if(!tree)
	 {
	 	tree = new treeNode;
		tree->entry = entryPtr;
		tree->left = NULL;
		tree->right = NULL;
	}
	else if (strcmp(entName, treeName) < 0)
	{
		addToTree(tree->left, entName, treeName, entryPtr);
	}
	else
	{
		addToTree(tree->right, entName, treeName, entryPtr);
	}
}

//iterative add to linked list function
void collection::addToList(vendor * entryPtr)
{
	linkedListNode * newNode = new linkedListNode;
	newNode->entry = entryPtr;
	newNode->next = NULL;
	if (!head)
		head = newNode;
	else
	{
		linkedListNode * cur = head;
		char tempProducts[MAX], entryProducts[MAX];
		entryPtr->getProductTypes(entryProducts);
		linkedListNode * prev = NULL;
		while (cur)
		{
			cur->entry->getProductTypes(tempProducts);	
			if (strcmp(entryProducts, tempProducts) < 0)
			{
				if (!prev)
				{
					newNode->next = cur;
					head = newNode;
				}
				else
				{
					prev->next = newNode;
					newNode->next = cur;
				}
				break;
			}
			if (!cur->next)
			{
				cur->next = newNode;
				break;
			}
			
			prev = cur;
			cur = cur->next;
		}
	}
	return;
}

//initial remove function
bool collection::remove(char * vendorName)
{
	char testName[MAX];
	return (removeFromTree(root, vendorName, testName) && removeFromList(vendorName));
}

//recursive remove from tree function
bool collection::removeFromTree(treeNode *& node, char * aName, char * curName)
{
	if (!node)
		return false;
	node->entry->getName(curName);
	if (strcmp(aName, curName) == 0)
	{
		treeNode * temp;
		if (!node->left && !node->right)		//node is a leaf
		{
			delete node;
			node = NULL;
		}
		else if (!node->left)				//node has no left child
		{
			temp = node;
			node = node->right;
			temp->right = NULL;
			delete temp;
		}
		else if (!node->right)				//node has no right child
		{
			temp = node;
			node = node->left;
			temp->left = NULL;
			delete temp;
		}
		else								//final case, has two children
		{
			treeNode * prev = NULL;		
			treeNode * cur = node->right;
			while (cur->left)				//find successor
			{
				prev = cur;
				cur = cur->left;
			}
			node->entry = cur->entry;		
			if (!prev)						//remove successor
				node->right = cur->right;
			else							//could have right child
				prev->left = cur->right;
			cur->right = NULL;
			delete cur;
		}
		return true;
	}
	else if (strcmp(aName, curName) < 0)
		return removeFromTree(node->left, aName, curName);
	else
		return removeFromTree(node->right, aName, curName);
}

//iterative remove from linkedlist function
bool collection::removeFromList(char * aName)
{
	char curName[MAX];
	linkedListNode * cur = head;
	linkedListNode * prev = NULL;
	while (cur)
	{
		cur->entry->getName(curName);
		if (strcmp(curName, aName) == 0)
		{
			if (!prev)
				head = cur->next;
			else
				prev->next = cur->next;
			delete cur->entry;		//delete pointer to vendor data at end of remove entry process
			delete cur;
			cur = NULL;
			size--;
			return true;
		}	
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
	return false;
}

//accessor functions///////////////////////////////////////////////////////////////////////////////
//retrieve vendor name from linked list structure iteratively
bool collection::retrieve(char * vendorName, vendor& aVendor)const
{
	char curName[MAX];
	linkedListNode * cur = head;
	while (cur)
	{
		cur->entry->getName(curName);
		if (strcmp(vendorName, curName) == 0)
		{
			aVendor = cur->entry;
			return true;
		}
		cur = cur->next;
	}
	return false;
}

//retrieve vendor product type from linked list structure iteratively
bool collection::retrieve(productTypes aProductType, vendor * vendors[])const
{
	char curProduct[MAX];
	int index = 0;
	linkedListNode * cur = head;
	bool found = false;
	while (cur)
	{
		cur->entry->getProductTypes(curProduct);
		if (strcmp(aProductType, curProduct) == 0)
		{
			vendors[index] = cur->entry;
			index++;
			found = true;
		}
		cur = cur->next;
	}
	if (found)
		return true;
	else
		return false;
}

//initial display by name function
void collection::displayByName()const
{
	if (!root)
	{
		cout << "No Vendors!" << endl;
		return;
	}
	root->entry->dataHeader();
	displayByName(root);
	cout << "Total Vendors: " << size << endl;
}

//display by name in tree structure recursively
void collection::displayByName(treeNode * node)const
{
	if (node)
	{
		displayByName(node->left);
		cout << node->entry;
		displayByName(node->right);
	}
}

//display by product type iteratively using linked list structure
void collection::displayByType()const
{
	if (!head)
	{
		cout << "No Vendors!" << endl;
		return;
	}
	linkedListNode * cur = head;
	cur->entry->dataHeader();
	while (cur)
	{
		cout << cur->entry;
		cur = cur->next;
	}
	cout << "Total Vendors: " << size << endl;
}

void collection::writeOut(char * fileName)const
{
	ofstream out;
	char curName[MAX], curPhone[MAX], curEvents[MAX], curProducts[MAX];
	linkedListNode * cur = head;

	out.open(fileName);
	if (!out)
	{
		cout << "Failed to open output file!" << endl;
		return;
	}

	while (cur)
	{
		cur->entry->getName(curName);
		cur->entry->getPhone(curPhone);
		cur->entry->getEvents(curEvents);
		cur->entry->getProductTypes(curProducts);

		out << curName << ";" << curPhone << ";" << curProducts << ";" << curEvents << endl;

		cur = cur->next;
	}
	out.close();
}
//assignment functions////////////////////////////////////////////////////////////////////////////////
//assignment operator function
const collection& collection::operator=(const collection& theCollection)
{
	if(this == &theCollection)
		return *this;
	else
	{
		destroyTree(root);
		destroyList(head);

		copyTree(root, theCollection.root);
		copyList(head, theCollection.head);
		return *this;
	}
}
