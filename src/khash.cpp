//
//  khash.cpp
//  klib
//
//  Created by qiaokeli on 15/12/31.
//  Copyright © 2015年 qiaokeli. All rights reserved.
//

#include "khash.h"

namespace klib {
	
#define DEFAULT_HASH_SIZE 64
	
	khash::khash()
	: pdata_(nullptr)
	, last_free_index_(0)
	, capacity_(0)
	{
		capacity_ = DEFAULT_HASH_SIZE;
		pdata_ = new _elem_t[capacity_];
	}
	
	khash::~khash()
	{
		if(pdata_) {
			delete [] pdata_;
		}
		pdata_ = nullptr;
		capacity_ = 0;
	}
	
	// when find_empty_pos fail, resize
	void khash::resize()
	{
		int count = 0;
		for(int i = 0; i < capacity_; ++i) {
			if(!pdata_[i].val.is_none()) {
				count++;
			}
		}
		_elem_t * old_data = pdata_;
		int old_capacity = capacity_;
		
		capacity_ = std::max(count * 2, DEFAULT_HASH_SIZE);
		pdata_ = new _elem_t[capacity_];
		last_free_index_ = 0;
		
		for(int i = 0; i < old_capacity; ++i) {
			if(!old_data[i].val.is_none()) {
				insert(old_data[i].key, old_data[i].val);
			}
		}
		
		delete [] old_data;
	}
	
	int khash::find_empty_pos()
	{
		for(int i = 0; i < capacity_; ++i) {
			last_free_index_ = (last_free_index_ + i) % capacity_;
			if(pdata_[last_free_index_].key.is_none()) {
				return last_free_index_;
			}
		}
		return -1;
	}
	
	kvalue & khash::find(const kvalue &key)
	{
		unsigned int hash = key.hash();
		int mpos = hash % capacity_;
		_elem_t * elem = &pdata_[mpos];

		// 1. find elem
		while (!elem->key.is_none()) {
			if(elem->key == key) {
				return elem->val;
			}
			if(elem->next < 0) {
				break;
			}
			elem = &pdata_[elem->next];
		}
		
		// 2. find empty pos
		int empty_pos = find_empty_pos();
		if(empty_pos < 0) {
			resize();
			empty_pos = find_empty_pos();
		}
		
		mpos = hash % capacity_;
		elem = &pdata_[mpos];
		
		_elem_t * empty_elem = &pdata_[empty_pos];
		
		// 3. if mpos is empty
		if(elem->key.is_none()) {
			elem->key = key;
			return elem->val;
		}
		
		// 4. if mpos is at its main-pos
		unsigned int other_hash = elem->key.hash();
		int other_mpos = other_hash % capacity_;
		if(other_mpos == mpos) {
			empty_elem->key = key;
			empty_elem->next = elem->next;
			elem->next = empty_pos;
			return empty_elem->val;
		}
		
		// 5. move to its main-pos
		_elem_t * other_melem = &pdata_[other_mpos];
		while(other_melem->next != mpos) {
			other_melem = &pdata_[other_melem->next];
		}
		memcpy(empty_elem, elem, sizeof(*empty_elem));
		other_melem->next = empty_pos;
		
		// 6. now, main-pos is empty
		elem->key = key;
		elem->val.clear();
		elem->next = -1;
		
		return elem->val;
	}
	
	void khash::insert(const kvalue & key, const kvalue & val)
	{
		kvalue & v = this->find(key);
		v = val;
	}
	
	kvalue & khash::operator [] (const kvalue & key)
	{
		return find(key);
	}
	
	khash * khash_create()
	{
		return new khash();
	}
}
