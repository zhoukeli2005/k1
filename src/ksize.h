#ifndef _kSize_h_
#define _kSize_h_

#include "core/kConfig.h"

k_namespace_begin
math_namespace_begin

struct kSize
{
	float w, h;
	
	// constructor
	kSize()
	: w{0}
	, h{0}
	{
		
	}
};

math_namespace_end
k_namespace_end

#endif
