//
//  karray.cpp
//  klib
//
//  Created by qiaokeli on 15/12/31.
//  Copyright © 2015年 qiaokeli. All rights reserved.
//

#include "karray.h"

namespace klib {
	
	karray::karray()
	: parray_(nullptr)
	, size_(0)
	, capacity_(0)
	{
		
	}
	
	karray::~karray()
	{
		if(parray_) {
			delete [] parray_;
		}
		parray_ = nullptr;
		size_ = 0;
		capacity_ = 0;
	}
	
	int karray::resize(int size)
	{
		kvalue * old_array = parray_;
		int old_size = size_;
		capacity_ = size;
		size_ = 0;
		
		parray_ = new kvalue[capacity_];
		
		for(int i = 0; i < old_size; ++i) {
			push(old_array[i]);
		}
		
		if(old_array) {
			delete [] old_array;
		}
		
		return capacity_;
	}
	
	void karray::push(const kvalue & v)
	{
		if(size_ >= capacity_) {
			resize((size_ + 1) * 2);
		}
		parray_[size_++] = v;
	}
	
	kvalue karray::pop()
	{
		if(size_ > 0) {
			return parray_[size_--];
		}
		return kvalue();
	}
	
	kvalue & karray::peek(int index)
	{
		if(index < 0) {
			index += size_;
		}
		
		assert(index >= 0 && index < size_);
		return parray_[index];
	}
	
	kvalue & karray::operator[](int index)
	{
		return this->peek(index);
	}
	
	karray * karray_create()
	{
		return new karray();
	}
}
