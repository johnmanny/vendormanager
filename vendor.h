/*
	Author: John Nemeth
	Sources: Class material
	Description: vendor data class header file
*/
#ifndef VENDOR_H
#define VENDOR_H
#include "tools.h"

//type definitions
//using productTypes = char *;
//using events = char *;
typedef char (*productTypes);
typedef char (*events);

//vendor class to model data///////////////////////////////////////////////////// 
class vendor
{
	public:
		//constructors/destructor
		vendor();
		vendor(const vendor& aVendor);
		~vendor();
		
		//public mutators
		void setName(char * aName);
		void setProductTypes(productTypes aProductType);
		void setEvents(events aEvents);
		void setPhone(char * aPhone);
		
		//assignment operator overloader functions(of type vendor data and vender data pointer)
		const vendor& operator=(const vendor& aVendor);
		const vendor& operator=(const vendor* aVendor);
		friend ostream& operator<<(ostream& out, vendor* aVendor);
		friend ostream& operator<<(ostream& out, vendor& aVendor);	
		
		//public accessors
		void getName(char * aName)const;
		void getProductTypes(productTypes aProductType)const;
		void getEvents(events aEvents)const;
		void getPhone(char * aPhone)const;
		
		//public utility function
		void dataHeader()const;

	private:
		//data types
		char * name;
		char * phone;
		productTypes products;
		events eventList;
};
#endif
