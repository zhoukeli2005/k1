//
//  kapp.cpp
//  klib
//
//  Created by qiaokeli on 15/12/31.
//  Copyright © 2015年 qiaokeli. All rights reserved.
//

#include "kapp.h"
#include "kvalue.h"
#include "karray.h"
#include "kstring.h"
#include "khash.h"

#include <iostream>

void kapp::init()
{
	klib::kvalue kstr;
	kstr.create_string("XXX, Test:%s, %d", "keli", 42);
	
	klib::kvalue ka;
	ka.create_array();
	
	klib::karray & a = (klib::karray &) ka;
	klib::karray & b = ka.as_array();
	
	ka.as_array().push(kstr);
	ka.as_array().push(1);
	ka.as_array().push("hahaha");
	
	klib::kvalue kh;
	kh.create_hash();
	
	kh.as_hash()["xx"] = ka;
	kh.as_hash()[5] = 7;
	kh.as_hash()[5.0] = 8;
	kh.as_hash()["yy"] = kstr;
	
	std::cout << ka.as_array()[-1].as_string().cstr() << std::endl;
	std::cout << (int)ka.as_array()[-2] << std::endl;
	std::cout << (int)kh.as_hash()[5] << "," << kh.as_hash()["yy"].as_string().cstr() << "," << (kh.as_hash()["xx"] == ka) << std::endl;
	
	
	return;
}