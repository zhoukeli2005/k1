//
//  karray.h
//  klib
//
//  Created by qiaokeli on 15/12/31.
//  Copyright © 2015年 qiaokeli. All rights reserved.
//

#ifndef k_array_h_
#define k_array_h_

#include "kcommon.h"
#include "kobject.h"
#include "kvalue.h"

namespace klib {
	
	class karray : public kobject
	{
	public:
		karray();
		virtual ~karray();
		
	public:
		void push(const kvalue & v);
		kvalue pop();
		kvalue & peek(int index);
		
		int size();
		
		int resize(int size);
		
	public:
		kvalue & operator [] (int index);
		
	private:
		kvalue * parray_;
		int size_;
		int capacity_;
	};
	
	karray * karray_create();
}

#endif /* karray_h */
