//
//  kvalue.cpp
//  klib
//
//  Created by qiaokeli on 15/12/31.
//  Copyright © 2015年 qiaokeli. All rights reserved.
//

#include "kvalue.h"
#include "karray.h"
#include "kstring.h"
#include "khash.h"

namespace klib {
	
	// global none kvalue
	kvalue g_kvalue_none;
	
	// ---- constructor ----
	
	kvalue::kvalue(int i)
	: type_(kobject_type::E_NONE)
	{
		this->operator = (i);
	}
	
	kvalue::kvalue(double d)
	: type_(kobject_type::E_NONE)
	{
		this->operator = (d);
	}
	
	kvalue::kvalue(const char * str)
	: type_(kobject_type::E_NONE)
	{
		this->operator = (str);
	}
	
	kvalue::kvalue(const kvalue & r)
	: type_(kobject_type::E_NONE)
	{
		this->operator = (r);
	}
	
	// ---- destructor ----
	kvalue::~kvalue()
	{
		this->clear();
	}
	
	// ---- static creator ----
	void kvalue::create_array()
	{
		clear();
		data_.p = karray_create();
		type_ = kobject_type::E_ARRAY;
	}
	
	void kvalue::create_string(const char *format, ...)
	{
		clear();
		va_list ap;
		va_start(ap, format);
		
		kstring * kstr = kstring_format_va(format, ap);
		
		data_.p = kstr;
		type_ = kobject_type::E_STRING;
	}
	
	void kvalue::create_hash()
	{
		clear();
		data_.p = khash_create();
		type_ = kobject_type::E_HASH;
	}
	
	// ---- interface ----
	bool kvalue::is_none() const
	{
		if(this == &g_kvalue_none) {
			return true;
		}
		return type_ == kobject_type::E_NONE;
	}
	
	const char * kvalue::cstr() const
	{
		// TODO...
		return "";
	}
	
	unsigned int kvalue::hash() const
	{
		switch(type_) {
			case kobject_type::E_NONE:
				return 0;
				
			case kobject_type::E_INT:
				return data_.i;
				
			case kobject_type::E_DOUBLE:
			{
				unsigned int h = 0;
				unsigned int * pint = (unsigned int *)(&data_.d);
				h = *pint + *(pint + 1);
				return h;
			}
				
			case kobject_type::E_STRING:
				return this->as_string().hash();
				
			default:
				return (unsigned int )(data_.p);
		}
	}
	
	// ---- type casts ----
	kvalue::operator int() const
	{
		assert(type_ == kobject_type::E_INT);
		return data_.i;
	}
	
	kvalue::operator double() const
	{
		assert(type_ == kobject_type::E_DOUBLE);
		return data_.d;
	}
	
	kvalue::operator kstring & () const
	{
		assert(type_ == kobject_type::E_STRING);
		return dynamic_cast<kstring &>(*data_.p);
	}
	
	kvalue::operator karray & () const
	{
		assert(type_ == kobject_type::E_ARRAY);
		return dynamic_cast<karray &>(*data_.p);
	}
	
	kvalue::operator khash & () const
	{
		assert(type_ == kobject_type::E_HASH);
		return dynamic_cast<khash &>(*data_.p);
	}
	
	// ---- assignments ----
	kvalue & kvalue::operator = (int i)
	{
		clear();
		data_.i = i;
		type_ = kobject_type::E_INT;
		return *this;
	}
	
	kvalue & kvalue::operator = (double d)
	{
		if((int)d == d) {
			return this->operator = ((int)d);
		}
		clear();
		data_.d = d;
		type_ = kobject_type::E_DOUBLE;
		return *this;
	}
	
	kvalue & kvalue::operator = (const char * str)
	{
		clear();
		
		data_.p = kstring_create(str);
		type_ = kobject_type::E_STRING;
		
		return *this;
	}
	
	kvalue & kvalue::operator = (const kvalue & r)
	{
		clear();
		type_ = r.type_;
		
		switch (type_) {
			case kobject_type::E_NONE:
				break;
				
			case kobject_type::E_INT:
				data_.i = r.data_.i;
				break;
				
			case kobject_type::E_DOUBLE:
				data_.d = r.data_.d;
				break;
				
			default:
				data_.p = r.data_.p;
				data_.p->grab();
				break;
		}
		
		return *this;
	}
	
	// ---- compare operators ----
	bool kvalue::operator == (const kvalue & r)
	{
		// 1. None ( both is None --> true, otherwise --> false )
		if(type_ == kobject_type::E_NONE || r.type_ == kobject_type::E_NONE) {
			if(type_ == r.type_) {
				return true;
			}
			return false;
		}
		
		// 2. both Number
		if(type_ <= kobject_type::E_DOUBLE && r.type_ <= kobject_type::E_DOUBLE) {
			double a = (type_ == kobject_type::E_INT) ? data_.i : data_.d;
			double b = (r.type_ == kobject_type::E_INT) ? r.data_.i : r.data_.d;
			return a == b;
		}
		
		// 3. both kobject
		if(type_ >= kobject_type::E_ARRAY || r.type_ >= kobject_type::E_ARRAY) {
			if(type_ != r.type_) {
				return false;
			}
			return data_.p == r.data_.p;
		}
		
		// 4. other, don't care for now
		return false;
	}
	
	bool kvalue::operator != (const kvalue & r)
	{
		return !this->operator == (r);
	}
	
	void kvalue::clear()
	{
		if(type_ >= kobject_type::E_ARRAY) {
			data_.p->drop();
		}
		type_ = kobject_type::E_NONE;
	}
}
