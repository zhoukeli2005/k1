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

#include <iostream>

void kapp::init()
{
	klib::kvalue kstr;
	kstr.create_string("XXX, Test:%s, %d", "keli", 42);
	
	klib::kvalue ka;
	ka.create_array();
	
	ka.as_array().push(kstr);
	
	std::cout << ka.as_array()[-1].as_string().cstr() << std::endl;
	
	return;
}