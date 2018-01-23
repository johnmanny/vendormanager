/*
	Author: John Nemeth
	Sources: Class material
	Description: collection class to model data structures for vendor data class header file
*/
#ifndef	COLLECTION_H
#define COLLECTION_H
#include "vendor.h"
#include "tools.h"

//data structure structs///////////////////////////////////////////////////////////
struct treeNode
{
	vendor * entry;
	treeNode *left, *right;
};

struct linkedListNode
{
	vendor * entry;
	linkedListNode * next;
};

//collection class for data structures to hold vendor data//////////////////////////
class collection
{
	public:
		//constructors/destructor
		collection();
		collection(char * fileName);
		collection(const collection& theCollection);
		~collection();
		
		//assignment operator
		const collection& operator=(const collection&);
	
		//public mutators
		void add(const vendor& aVendor);
		bool remove(char * vendorName);

		//public accessors
		bool retrieve(char * vendorName, vendor & aVendor)const;
		bool retrieve(productTypes aProductType, vendor * vendors[])const;
		void displayByType()const;
		void displayByName()const;
		void displayByName(treeNode * node)const;
		void writeOut(char * fileName)const;

	private:
		//pointers to ADT structs
		treeNode * root;
		linkedListNode * head;
		
		//private mutators
		void destroyTree(treeNode *& tempNode);	
		void destroyList(linkedListNode *& node);
		void copyTree(treeNode *&, treeNode *);
		void copyList(linkedListNode *&, linkedListNode *);
		void addToTree(treeNode *& tree, char * entName, char * treeName, vendor * entryPtr);
		void addToList(vendor * entryPtr);
		bool removeFromTree(treeNode *& node, char * aName, char * curName);
		bool removeFromList(char * aName);
	
		//number of vendors 
		int size;
};
#endif
