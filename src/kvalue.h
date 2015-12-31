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
		bool is_none() const;
		void clear();	// set_none()
		const char * cstr() const;
		unsigned int hash() const;
		
	// type casts
	public:
		operator int() const;
		operator double() const;
		operator kstring& () const;
		operator karray& () const;
		operator khash& () const;
		
		karray& as_array() const { return this->operator karray & (); }
		kstring& as_string() const { return this->operator kstring & (); }
		khash& as_hash() const { return this->operator khash& (); }
		
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
		
	// internal data
	private:
		union _data_type {
			int i;
			double d;
			kobject * p;
		} data_;
		
		kobject_type type_;
	};
	
	extern kvalue g_kvalue_none;
}


#endif /* kvalue_h */
