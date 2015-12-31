#ifndef _kVec3_h_
#define _kVec3_h_

#include "core/kConfig.h"
#include "debug/kStat.h"

#include <math.h>

k_namespace_begin
math_namespace_begin

struct kVec3
{
	float x, y, z;
	
	// constructor
	kVec3(): x{0}, y{0}, z{0} { init(); }
	kVec3(float x_, float y_, float z_): x{x_}, y{y_}, z{z_} { init(); }
	kVec3(const kVec3 & o): x{o.x}, y{o.y}, z{o.z} { init(); }
	kVec3(kVec3 && o): x{o.x}, y{o.y}, z{o.z} { init(); }
	
	void init()
	{
		debug::kStat::instance().kVec3_count++;
	}
	
	~kVec3()
	{
		debug::kStat::instance().kVec3_count--;
	}
	
	// copy
	kVec3 & operator = (const kVec3 & o)
	{
		x = o.x;
		y = o.y;
		z = o.z;
		return *this;
	}
	
	kVec3 & operator = (kVec3 && o)
	{
		x = o.x;
		y = o.y;
		z = o.z;
		return *this;
	}
	
	// operator
	kVec3 & operator += (const kVec3 & o)
	{
		x += o.x;
		y += o.y;
		z += o.z;
		return *this;
	}
	
	kVec3 & operator -= (const kVec3 & o)
	{
		x -= o.x;
		y -= o.y;
		z -= o.z;
		return * this;
	}
	
	kVec3 & operator *= (float f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}
	
	kVec3 & operator /= (float f)
	{
		if(f != 0) {
			x /= f;
			y /= f;
			z /= f;
		}
		return *this;
	}
	
	// api
	float distance()
	{
		return sqrtf(x * x + y * y + z * z);
	}
	
	float distance_double()
	{
		return x * x + y * y + z * z;
	}
	
	void normalize()
	{
		float d = distance();
		x /= d;
		y /= d;
		z /= d;
	}
	
	kVec3 cross(const kVec3 & o)
	{
		kVec3 tmp(*this);
		tmp.crossInPlace(o);
		return tmp;
	}
	
	kVec3 & crossInPlace(const kVec3 & o)
	{
		float x_ = x;
		float y_ = y;
		float z_ = z;
		
		this->x = y_ * o.z - z_ * o.y;
		this->y = z_ * o.x - x_ * o.z;
		this->z = x_ * o.y - y_ * o.x;
		return *this;
	}
};
inline kVec3 operator + (const kVec3 & a, const kVec3 b)
{
	kVec3 tmp = a;
	tmp += b;
	return  tmp;
}

inline kVec3 operator - (const kVec3 & a, const kVec3 & b)
{
	kVec3 tmp = a;
	tmp -= b;
	return tmp;
}

inline kVec3 operator * (const kVec3 & a, float f)
{
	kVec3 tmp = a;
	tmp *= f;
	return tmp;
}

inline kVec3 operator * (float f, const kVec3 & a)
{
	return a * f;
}

inline kVec3 operator / (const kVec3 & a, float f)
{
	kVec3 tmp = a;
	tmp /= f;
	return tmp;
}

inline float operator * (const kVec3 & a, const kVec3 & b)
{
	float f = a.x * b.x + a.y * b.y + a.z * b.z;
	return f;
}

math_namespace_end
k_namespace_end

#endif

