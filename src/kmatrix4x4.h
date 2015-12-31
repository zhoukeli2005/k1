#ifndef _kMatrix_h_
#define _kMatrix_h_

#include "core/kConfig.h"
#include "debug/kStat.h"

#include "math/kVec3.h"
#include "kMathUtil.h"

#include <string.h>

k_namespace_begin
math_namespace_begin

struct kMatrix4x4;
kMatrix4x4 operator * (const kMatrix4x4 &, const kMatrix4x4 &);

struct kMatrix4x4
{
	float m[16];
	
	// constructor
	kMatrix4x4()
	{
		memset(m, 0, sizeof(m));
		m[0] = m[5] = m[10] = m[15] = 1;
		
		debug::kStat::instance().kMatrix4x4_count++;
	}
	
	kMatrix4x4(const kMatrix4x4 & o)
	{
		if(&o == this) {
			return;
		}
		memcpy(m, o.m, sizeof(m));
	}
	
	kMatrix4x4(kMatrix4x4 && o)
	{
		memcpy(m, o.m, sizeof(m));
	}
	
	// destructor
	~kMatrix4x4()
	{
		debug::kStat::instance().kMatrix4x4_count--;
	}
	
	// operator
	kMatrix4x4 & operator = (const kMatrix4x4 & o)
	{
		if(this == &o) {
			return *this;
		}
		memcpy(m, o.m, sizeof(m));
		return *this;
	}
	
	kMatrix4x4 & operator = (kMatrix4x4 && o)
	{
		memcpy(m, o.m, sizeof(m));
		return *this;
	}
	
	kMatrix4x4 & operator *= (const kMatrix4x4 & o)
	{
		float tmp_m[16];
		memcpy(tmp_m, m, sizeof(m));
		for(int row = 0; row < 4; ++row) {
			for(int line = 0; line < 4; ++line) {
				this->m[row + line * 4] = 0;
				for(int i = 0; i < 4; ++i) {
					this->m[row + line * 4] += tmp_m[row + i * 4] * o.m[i + line * 4];
				}
			}
		}
		return *this;
	}
	
	float & operator [] (int idx)
	{
		return m[idx];
	}
	
	// api
	float & get(int row, int line)
	{
		return m[row + line * 4];
	}
	
	const float & get(int row, int line) const
	{
		return m[row + line * 4];
	}
	
	// factory api
	static kMatrix4x4 identity()
	{
		kMatrix4x4 tmp;
		return tmp;
	}
	
	static kMatrix4x4 translate(float x, float y, float z)
	{
		kMatrix4x4 tmp;
		tmp.m[12] = x;
		tmp.m[13] = y;
		tmp.m[14] = z;
		return tmp;
	}
	
	static kMatrix4x4 rotate(float x, float y, float z)
	{
		kMatrix4x4 tmp = rotateZ(z) * rotateX(x) * rotateY(y);
		return tmp;
	}
	
	static kMatrix4x4 rotateX(float radian)
	{
		kMatrix4x4 tmp;
		
		float sinX = math::sin(radian);
		float cosX = math::cos(radian);
		
		tmp.get(1, 1) = cosX;
		tmp.get(1, 2) = -sinX;
		tmp.get(2, 1) = sinX;
		tmp.get(2, 2) = cosX;
		
		return tmp;
	}
	
	static kMatrix4x4 rotateY(float radian)
	{
		kMatrix4x4 tmp;
		
		float sinX = math::sin(radian);
		float cosX = math::cos(radian);
		
		tmp.get(0, 0) = cosX;
		tmp.get(0, 2) = sinX;
		tmp.get(2, 0) = -sinX;
		tmp.get(2, 2) = cosX;
		
		return tmp;
	}
	
	static kMatrix4x4 rotateZ(float radian)
	{
		kMatrix4x4 tmp;
		
		float sinX = math::sin(radian);
		float cosX = math::cos(radian);
		
		tmp.get(0, 0) = cosX;
		tmp.get(0, 1) = -sinX;
		tmp.get(1, 0) = sinX;
		tmp.get(1, 1) = cosX;
		
		return tmp;
	}
	
	static kMatrix4x4 scale(float x, float y, float z)
	{
		kMatrix4x4 tmp;
		tmp.m[0] = x;
		tmp.m[5] = y;
		tmp.m[10] = z;
		return tmp;
	}
	
	static kMatrix4x4 lookAt(kVec3 eye, kVec3 center, kVec3 up)
	{
		kMatrix4x4 tmp;
		
		kVec3 z = eye - center;
		
		kVec3 x = up.cross(z);
		
		kVec3 y = z.cross(x);
		
		x.normalize();
		y.normalize();
		z.normalize();
		
		tmp[0] = x.x;
		tmp[1] = y.x;
		tmp[2] = z.x;
		
		tmp[4] = x.y;
		tmp[5] = y.y;
		tmp[6] = z.y;
		
		tmp[8] = x.z;
		tmp[9] = y.z;
		tmp[10] = z.z;
		
		kMatrix4x4 t = kMatrix4x4::translate(-eye.x, -eye.y, -eye.z);
		
		tmp = tmp * t;
		
		return  tmp;
	}
	
	static kMatrix4x4 project(float fovDegree, float aspect, float zNear, float zFar)
	{
		kMatrix4x4 tmp;
		
		float fovRadian = degreeToRadian(fovDegree);
		float deltaZ = zFar - zNear;
		float s = math::sin(fovRadian);
		float cotangent = 0;
		
		if(deltaZ == 0 || s == 0 || aspect == 0) {
			return tmp;
		}
		
		cotangent = math::cos(fovRadian) / s;
		
		tmp[0] = cotangent / aspect;
		tmp[5] = cotangent;
		tmp[10] = -(zFar + zNear) / deltaZ;
		tmp[11] = -1;
		tmp[14] = -2 * zNear * zFar / deltaZ;
		tmp[15] = 0;
		
		return tmp;
	}
};

inline kVec3 operator * (const kMatrix4x4 & m, const kVec3 & v)
{
	kVec3 tmp;
	tmp.x = m.m[0] * v.x + m.m[4] * v.y + m.m[8] * v.z + m.m[12];
	tmp.y = m.m[1] * v.x + m.m[5] * v.y + m.m[9] * v.z + m.m[13];
	tmp.z = m.m[2] * v.x + m.m[6] * v.y + m.m[10] * v.z + m.m[14];
	return tmp;
}

inline kMatrix4x4 operator * (const kMatrix4x4 & a, const kMatrix4x4 & b)
{
	kMatrix4x4 tmp = a;
	tmp *= b;
	return tmp;
}

math_namespace_end
k_namespace_end

#endif
