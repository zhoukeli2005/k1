//
//  kvalue.h
//  klib
//
//  Created by qiaokeli on 15/12/31.
//  Copyright © 2015年 qiaokeli. All rights reserved.
//

#ifndef k_value_h_
#define k_value_h_

#include "kobject.h"

namespace klib {

	class kstring;
	class karray;
	class khash;
	
	class kvalue
	{
		
	// constructor
	public:
		kvalue() : type_(kobject_type::E_NONE) {}
		
		kvalue(int i);
		kvalue(double d);
		kvalue(const char * str);
		kvalue(const kvalue & r);
		
	// destructor
	public:
		~kvalue();
		
	// creator
	public:
		void create_string(const char * format, ...);
		void create_array();
		void create_hash();
		
	// interface
	public:
		bool is_none();
		const char * cstr();
		unsigned int hash();
		
	// type casts
	public:
		operator int();
		operator double();
		operator kstring& ();
		operator karray& ();
	//	operator khash& ();
		
		karray& as_array() { return (karray &)(*this); }
		kstring& as_string() { return (kstring &)(*this); }
	//	khash& as_hash() { return (khash &)(*this); }
		
	// assignments
	public:
		kvalue & operator = (int i);
		kvalue & operator = (double d);
		kvalue & operator = (const char * str);
		kvalue & operator = (const kvalue & r);
		
	// operators
	public:
		bool operator == (const kvalue & r);
		bool operator != (const kvalue & r);
	
		
	// internal functions
	private:
		void clear();
		
	// internal data
	private:
		union _data_type {
			int i;
			double d;
			kobject * p;
		} data_;
		
		kobject_type type_;
	};
}


#endif /* kvalue_h */
