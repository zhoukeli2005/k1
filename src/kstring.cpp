//
//  kstring.cpp
//  klib
//
//  Created by qiaokeli on 15/12/31.
//  Copyright © 2015年 qiaokeli. All rights reserved.
//

#include "kstring.h"

#include <memory>
#include <stdio.h>

namespace klib {
	
	struct kstring_imp {
		kstring kstr;
		unsigned int hash;
		int len;
		struct kstring_imp * next;
		char p[1];
	};
	
	struct kstring_cache {
		kstring_imp ** cache_;
		int size_;
		int capacity_;
		
		kstring_cache()
		: cache_(nullptr)
		, size_(0)
		, capacity_(0)
		{
			
		}
		
		void resize()
		{
			if(size_ * 1.7 >= capacity_) {
				kstring_imp ** old_cache = cache_;
				int old_size = size_;
				capacity_ = (capacity_ + 1) * 2;
				cache_ = new kstring_imp* [capacity_];
				size_ = 0;
				
				// C++ new will zero-initialize POD(plain old data) array??
				memset(cache_, 0, sizeof(kstring_imp *) * capacity_);
				
				for(int i = 0; i < old_size; ++i) {
					if(old_cache[i]) {
						kstring_imp * tmp = old_cache[i];
						while(tmp) {
							insert(tmp);
							tmp = tmp->next;
						}
					}
				}
			}
		}
		
		kstring_imp * find(const char * str, int len, unsigned int hash)
		{
			resize();
			int pos = hash % capacity_;
			kstring_imp * kstr = cache_[pos];
			while(kstr) {
				if(kstr->hash == hash && kstr->len == len && strcmp(kstr->p, str) == 0) {
					return kstr;
				}
				kstr = kstr->next;
			}
			return nullptr;
		}
		
		void insert(kstring_imp * s)
		{
			resize();
			int pos = s->hash % capacity_;
			s->next = cache_[pos];
			cache_[pos] = s;
			
			size_++;
		}
	};
	
	static kstring_cache s_cache;
	
	
	kstring * kstring_format(const char * format, ...)
	{
		va_list ap;
		va_start(ap, format);
		
		return kstring_format_va(format, ap);
	}
	
	kstring * kstring_format_va(const char * format, va_list ap)
	{
		static char buff[1024];
		memset(buff, 0, sizeof(buff));
		
		vsnprintf(buff, sizeof(buff) - 1, format, ap);
		
		return kstring_create(buff);
	}
	
	kstring * kstring_create(const char * pstr)
	{
		int len = strlen(pstr);
		unsigned int hash = len;
		int step = (len >> 5) + 1;
		for(int l = len - 1; l >= step; l -= step) {
			hash ^= ((hash << 5) + (hash >> 2)) + pstr[l];
		}
		
		// 1. if find in cache
		kstring_imp * kstr_imp = s_cache.find(pstr, len, hash);
		if(kstr_imp) {
			kstr_imp->kstr.grab();
			return &kstr_imp->kstr;
		}
		
		// 2. create new one
		int mem_size = sizeof(kstring_imp) + len;
		kstr_imp = (kstring_imp *)new char[mem_size];
		memcpy(kstr_imp->p, pstr, len + 1);
		kstr_imp->len = len;
		kstr_imp->hash = hash;
		
		// 3. call kstring's constructor to init 'ref_count'
		kstring * kstr = &kstr_imp->kstr;
		new (kstr) kstring();
		
		// 4. insert in cache
		kstr->grab();
		s_cache.insert(kstr_imp);
		
		return kstr;
	}
	
	int kstring::size()
	{
		kstring_imp * kstr_imp = (kstring_imp *)this;
		return kstr_imp->len;
	}
	
	unsigned int kstring::hash()
	{
		kstring_imp * kstr_imp = (kstring_imp *)this;
		return kstr_imp->hash;
	}
	
	const char * kstring::cstr()
	{
		kstring_imp * kstr_imp = (kstring_imp *)this;
		return kstr_imp->p;
	}
	
	void kstring::_destruct_this()
	{
		assert(false);
	}
}
