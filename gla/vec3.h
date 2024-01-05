#pragma once

#include "vector.h"

namespace gla
{
	template<typename T>
	struct vec<3, T>
	{
		T x, y, z;

		vec() : x(0), y(0), z(0) { }

		vec(T scalar) : x(scalar), y(scalar), z(scalar) { }

		vec(T x, T y, T z) : x(x), y(y), z(z) { }

		// ┌----------------------------------------------------┐
		// │    binary operators                                |
		// └----------------------------------------------------┘

		vec operator + (const vec &v) const { return vec(x + v.x, y + v.y, z + v.z); }
		vec operator - (const vec &v) const { return vec(x - v.x, y - v.y, z - v.z); }
		vec operator * (const vec &v) const { return vec(x * v.x, y * v.y, z * v.z); }
		vec operator / (const vec &v) const { return vec(x / v.x, y / v.y, z / v.z); }

		vec operator * (T scalar) const { return vec(x * scalar, y * scalar, z * scalar); }
		vec operator / (T scalar) const { return vec(x / scalar, y / scalar, z / scalar); }

		friend vec operator * (T scalar, const vec &v) { return vec(v.x * scalar, v.y * scalar, v.z * scalar); }

		// ┌----------------------------------------------------┐
		// │    compound assignment operators                   |
		// └----------------------------------------------------┘

		vec & operator += (const vec &v) { x += v.x; y += v.y; z += v.z; return *this; }
		vec & operator -= (const vec &v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		vec & operator *= (const vec &v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
		vec & operator /= (const vec &v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

		vec & operator *= (T scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
		vec & operator /= (T scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

		// ┌----------------------------------------------------┐
		// │    comparison operators                            |
		// └----------------------------------------------------┘

		bool operator == (const vec &v) const { return x == v.x && y == v.y && z == v.z; }
		bool operator != (const vec &v) const { return !(*this == v); }

		// ┌----------------------------------------------------┐
		// │    access operators                                |
		// └----------------------------------------------------┘

        T & operator [] (std::size_t index)
        {            
			switch (index)
			{
				case 0: return x;
				case 1: return y;
				case 2: return z;
			}
        }

        const T & operator [] (std::size_t index) const
        {
			switch (index)
			{
				case 0: return x;
				case 1: return y;
				case 2: return z;
			}
        }

		T length()
		{
			return std::sqrt(x * x + y * y + z * z);
		}

		vec opposite()
		{
			return { -x, -y, -z };
		}

		vec normalized()
		{
			return (*this != zero()) ? (*this /= length()) : zero();
		}

		static vec zero()
		{
			return { 0, 0, 0 };
		}

		static float dot(const vec &v0, const vec &v1)
		{
			return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
		}

		static vec cross(const vec &v0, const vec &v1)
		{
			return vec(v0.y * v1.z - v0.z * v1.y, v0.z * v1.x - v0.x * v1.z, v0.x * v1.y - v0.y * v1.x);
		}
	};
}