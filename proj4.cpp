/*
	Author: John Nemeth
	Sources: class material
	Description: driver file for vendor database program
*/

#include "tools.h"
#include "vendor.h"
#include "collection.h"
#include <iomanip>

//function prototypes for interface////////////////////////////
void displayMenu();
char getCmd();
void execCmd(char & cmd, collection& vendorList);
void getVendorInfo(vendor & curVendor, collection & vendorList);

//main program////////////////////////////////////////////////
int main()
{
	char command;
	char fileName[] = "data.dat";
	collection vendors(fileName);

	displayMenu();
	command = getCmd();
	while(command != 'q')
	{
		execCmd(command, vendors);
		cin.clear();
		displayMenu();
		command = getCmd();
	}

	vendors.writeOut(fileName);
	cout << "\nSee you next time!" << endl << endl;
	return 0;
}

//interface functions///////////////////////////////////////////
//display menu for main program
void displayMenu()
{
	cout << endl << "\tJohn's Vendor Manager V1" << endl;
	cout << "\ta) add vendor" << endl;
	cout << "\tr) remove vendor" << endl;
	cout << "\tp) search vendors who sell a specific product" << endl;
	cout << "\ts) search vendor by name" << endl;
	cout << "\td) display vendors by name" << endl;
	cout << "\tt) display vendors by type of product" << endl;
	cout << "\tq) quit!" << endl << endl;
}

//get command
char getCmd()
{
	char cmd;
	cout << "Choose an option(a, r, p, s, d, t, or q): ";
	cin >> cmd;
	cout << endl;
	cin.ignore(100, '\n');
	return tolower(cmd);
}

//execute command
void execCmd(char & cmd, collection& vendorList)
{
	vendor aVendor;	
	vendor * vendors[50] = {NULL};
	char key[MAX];
	int index;

	switch(cmd)
	{
	case 'a':
		getVendorInfo(aVendor, vendorList);			
		vendorList.add(aVendor);
		cout << "Vendor has been added to database!" << endl;
		break;
	case 'r':
		cout << "Enter name of vendor to remove: ";
		cin.get(key, MAX, '\n');
		cin.ignore(MAX, '\n');
		if (vendorList.remove(key))
			cout << endl << "Success! " << key << " has been found and removed!" << endl;
		else
			cout << "No vendor with name " << key << " found. Nothing has been removed." << endl;
		break;
	case 'p':
			cout << "Enter product type to get list of vendors(max of 50 vendors returned): " << endl;
			cin.get(key, MAX, '\n');
			cin.ignore(MAX, '\n');
			if (vendorList.retrieve(key, vendors))
			{
				index = 0;
				cout << endl << "Success!" << endl << "List of vendors who sell product: " << endl;
				aVendor.dataHeader();
				while (vendors[index] != NULL)
				{	
					cout << vendors[index];
					index++;
				}
			}
			else
				cout << "No vendors with " << key << " products found!" << endl;
		break;
	case 's':
		cout << "Enter name of vendor to retrieve: ";
		cin.get(key, MAX, '\n');
		cin.ignore(MAX, '\n');
		if (vendorList.retrieve(key, aVendor))
		{
			cout << endl << "Success!" << endl;
			aVendor.dataHeader();
			cout << aVendor;
		}
		else
			cout << "No vendor with name " << key << " found!" << endl;
		break;
	case 'd':
		cout << "-----Vendors sorted alphabetically by name:" << endl;
		vendorList.displayByName();
		break;
	case 't':
		cout << "-----Vendors sorted by product type:" << endl;
		vendorList.displayByType();
		break;
	default:
		cout << "Command not recognized!" << endl;
		break;
	}
}

//function to get vendor info
void getVendorInfo(vendor & curVendor, collection & vendorList)
{
	char aName[MAX], aPhone[MAX], aProduct[MAX], aEvents[MAX];

	cout << "\tEnter Name: ";
	cin.get(aName, MAX, '\n');
	cin.ignore(MAX, '\n');
	cout << "\tEnter Product type: ";
	cin.get(aProduct, MAX, '\n');
	cin.ignore(MAX, '\n');
	cout << "\tEnter Events: ";
	cin.get(aEvents, MAX, '\n');
	cin.ignore(MAX, '\n');
	cout << "\tEnter Phone Number: ";
	cin.get(aPhone, MAX, '\n');
	cin.ignore(MAX, '\n');
	curVendor.setName(aName);
	curVendor.setPhone(aPhone);
	curVendor.setEvents(aEvents);
	curVendor.setProductTypes(aProduct);
}
