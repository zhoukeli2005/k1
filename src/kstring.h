//
//  kstring.h
//  klib
//
//  Created by qiaokeli on 15/12/31.
//  Copyright © 2015年 qiaokeli. All rights reserved.
//

#ifndef k_string_h_
#define k_string_h_

#include "kobject.h"

namespace klib {
	
	class kstring : public kobject
	{
	public:
		int size();
		unsigned int hash();
		
		const char * cstr();
		
	protected:
		virtual void _destruct_this();
	};
	
	kstring * kstring_create(const char * p);
	kstring * kstring_format(const char * format, ...);
	kstring * kstring_format_va(const char * format, va_list ap);
}

#endif /* kstring_h */
