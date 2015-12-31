//
//  kobject.h
//  klib
//
//  Created by qiaokeli on 15/12/31.
//  Copyright © 2015年 qiaokeli. All rights reserved.
//

#ifndef k_object_h_
#define k_object_h_

#include <cassert>

namespace klib {
	enum class kobject_type {
		E_NONE,
		
		// simple-types
		E_INT,
		E_DOUBLE,
		
		// objects
		E_ARRAY,
		E_STRING,
		E_HASH,
		
		E_TYPE_MAX
	};
	
	class kobject
	{
	public:
		kobject() : ref_count_(1) {}
		
		virtual ~kobject() {}
		
	public:
		void grab()
		{
			assert(ref_count_ > 0);
			ref_count_++;
		}
		
		void drop()
		{
			assert(ref_count_ > 0);
			ref_count_--;
			if(ref_count_ == 0) {
				delete this;
			}
		}
		
	private:
		int ref_count_;
	};
}


#endif /* kobject_h */
