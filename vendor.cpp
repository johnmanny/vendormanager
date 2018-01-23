/*
	Author: John Nemeth
	Sources: Class Material
	Description: Vendor data class implementation file
*/
#include "vendor.h"
#include <cstring>
#include <iomanip>

//constructors/destructor//////////////////////////////////////////////////
//constructor
vendor::vendor()
{
	name = NULL;
	products = NULL;
	eventList = NULL;
	phone = NULL;
}

//constructor for passed vendor data
vendor::vendor(const vendor& aVendor)
{
	name = NULL;
	products = NULL;
	eventList = NULL;
	phone = NULL;
	setName(aVendor.name);
	setPhone(aVendor.phone);
	setProductTypes(aVendor.products);
	setEvents(aVendor.eventList);
}

//destructor
vendor::~vendor()
{
	if (name)
		delete[] name;
	if (products)
		delete[] products;
	if (eventList)
		delete[] eventList;
	if (phone)
		delete[] phone;
}

//mutators////////////////////////////////////////////////////////////////
void vendor::setName(char * aName)
{
	if (this->name)
		delete[] this->name;
	this->name = new char[strlen(aName) + 1];
	strcpy(this->name, aName);
}

void vendor::setProductTypes(productTypes aProductType)
{
	if (this->products)
		delete[] this->products;
	this->products = new char[strlen(aProductType) + 1];
	strcpy(this->products, aProductType);
}

void vendor::setEvents(events aEvents)
{
	if (this->eventList)
		delete[] this->eventList;
	this->eventList = new char[strlen(aEvents) + 1];
	strcpy(this->eventList, aEvents);
}

void vendor::setPhone(char * aPhone)
{
	if (this->phone)
		delete[] this->phone;
	this->phone = new char[strlen(aPhone) + 1];
	strcpy(this->phone, aPhone);
}

//accessors///////////////////////////////////////////////////////////////
void vendor::getName(char * aName)const
{
	strcpy(aName, this->name);
}

void vendor::getProductTypes(productTypes aProductType)const
{
	strcpy(aProductType, this->products);
}

void vendor::getEvents(events aEvents)const
{
	strcpy(aEvents, this->eventList);
}

void vendor::getPhone(char * aPhone)const
{
	strcpy(aPhone, this->phone);
}

//utility functions///////////////////////////////////////////////////////
void vendor::dataHeader()const
{
	cout << left << setw(20) << "---Name---" << setw(20) << "---Product Type---" << setw(35) << "---Events---" << setw(15) << "---Phone---" << endl;

}

//operator functions/////////////////////////////////////////////////////
//assignment overloader for vendor data
const vendor& vendor::operator=(const vendor& aVendor)
{
	if (this == &aVendor)
		return *this;
	else
	{
		setName(aVendor.name);
		setProductTypes(aVendor.products);
		setEvents(aVendor.eventList);
		setPhone(aVendor.phone);
		return *this;
	}
}

//assignment overloader for vendor data pointer
const vendor& vendor::operator=(const vendor* aVendor)
{
		setName(aVendor->name);
		setProductTypes(aVendor->products);
		setEvents(aVendor->eventList);
		setPhone(aVendor->phone);
		return *this;
}

//output overloader for vendor data pointer
ostream& operator<<(ostream& out, vendor* aVendor)
{
	char curName[MAX], curPhone[MAX], curProducts[MAX], curEvents[MAX];
	aVendor->getName(curName);
	aVendor->getPhone(curPhone);
	aVendor->getProductTypes(curProducts);
	aVendor->getEvents(curEvents);

	out << left << setw(20) << curName << setw(20) << curProducts << setw(35) << curEvents << setw(15) << curPhone << endl;
}

//output overloader for vendor data
ostream& operator<<(ostream& out, vendor& aVendor)
{
	char curName[MAX], curPhone[MAX], curProducts[MAX], curEvents[MAX];
	aVendor.getName(curName);
	aVendor.getPhone(curPhone);
	aVendor.getProductTypes(curProducts);
	aVendor.getEvents(curEvents);

	out << left << setw(20) << curName << setw(20) << curProducts << setw(35) << curEvents << setw(15) << curPhone << endl;
}
