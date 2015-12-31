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
		static kvalue create_string(const char * format, ...);
		static kvalue create_array();
		static kvalue create_hash();
		
	// interface
	public:
		bool is_none();
		
	// type casts
	public:
		operator int();
		operator double();
		operator kstring * ();
		operator karray * ();
		operator khash * ();
		
	// assignments
	public:
		kvalue & operator = (int i);
		kvalue & operator = (double d);
		kvalue & operator = (const char * str);
		kvalue & operator = (const kvalue & r);
		
	// internal functions
	private:
		void clear();
		
	// internal data
	private:
		union _data_type {
			int i;
			double d;
			void * p;
		} data_;
		
		kobject_type type_;
	};
}


#endif /* kvalue_h */
