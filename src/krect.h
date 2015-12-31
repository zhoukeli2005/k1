#ifndef _kRect_h_
#define _kRect_h_

#include "core/kConfig.h"

k_namespace_begin
math_namespace_begin

struct kRect
{
	float x, y, w, h;
	
	kRect() : x(0), y(0), w(0), h(0) {}
	
	kRect(float x_, float y_, float w_, float h_)
	: x(x_)
	, y(y_)
	, w(w_)
	, h(h_)
	{
		
	}
	
	kRect(const kRect & r)
	{
		x = r.x;
		y = r.y;
		w = r.w;
		h = r.h;
	}
	
	kRect & operator = (const kRect & r)
	{
		x = r.x;
		y = r.y;
		w = r.w;
		h = r.h;
		
		return *this;
	}
};

math_namespace_end
k_namespace_end

#endif
