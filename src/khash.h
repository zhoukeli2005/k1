//
//  khash.hpp
//  klib
//
//  Created by qiaokeli on 15/12/31.
//  Copyright © 2015年 qiaokeli. All rights reserved.
//

#ifndef k_hash_h_
#define k_hash_h_

#include "kobject.h"
#include "kvalue.h"

namespace klib {
	
	class khash : public kobject
	{
	// constructor & destructor
	public:
		khash();
		~khash();
		
	// Api
	public:
		/*
		 * return g_kvalue_none if not found
		 */
		kvalue & find(const kvalue & key);
		
		/*
		 * insert
		 */
		void insert(const kvalue & key, const kvalue & val);
		
		/*
		 * remove
		 */
		void remove(const kvalue & key);
		
	// operators
	public:
		kvalue & operator [] (const kvalue & key);
		
	// private functions
	private:
		void resize();
		int find_empty_pos();
		
	private:
		struct _elem_t {
			kvalue key;
			kvalue val;
			
			int next;
			
			_elem_t() : next(-1) {}
		};
		_elem_t * pdata_;
		int capacity_;
		int last_free_index_;
	};
	
	khash * khash_create();
}

#endif /* khash_hpp */
