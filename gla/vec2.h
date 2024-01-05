#pragma once

#include "vector.h"

namespace gla
{
	template<typename T>
	struct vec<2, T>
	{
		T x, y;
		
		vec() : x(0), y(0) { }

		vec(T scalar) : x(scalar), y(scalar) { }

		vec(T x, T y) : x(x), y(y) { }

		// ┌----------------------------------------------------┐
		// │    binary operators                                |
		// └----------------------------------------------------┘

		vec operator + (const vec &v) const { return vec(x + v.x, y + v.y); }
		vec operator - (const vec &v) const { return vec(x - v.x, y - v.y); }
		vec operator * (const vec &v) const { return vec(x * v.x, y * v.y); }
		vec operator / (const vec &v) const { return vec(x / v.x, y / v.y); }

		vec operator * (T scalar) const { return vec(x * scalar, y * scalar); }
		vec operator / (T scalar) const { return vec(x / scalar, y / scalar); }

		friend vec operator * (T scalar, const vec &v) { return vec(v.x * scalar, v.y * scalar); }

		// ┌----------------------------------------------------┐
		// │    compound assignment operators                   |
		// └----------------------------------------------------┘

		vec & operator += (const vec &v) { x += v.x; y += v.y; return *this; }
		vec & operator -= (const vec &v) { x -= v.x; y -= v.y; return *this; }
		vec & operator *= (const vec &v) { x *= v.x; y *= v.y; return *this; }
		vec & operator /= (const vec &v) { x /= v.x; y /= v.y; return *this; }

		vec & operator *= (T scalar) { x *= scalar; y *= scalar; return *this; }
		vec & operator /= (T scalar) { x /= scalar; y /= scalar; return *this; }

		// ┌----------------------------------------------------┐
		// │    comparison operators                            |
		// └----------------------------------------------------┘

		bool operator == (const vec &v) const { return x == v.x && y == v.y; }
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
			}
        }

        const T & operator [] (std::size_t index) const
        {
			switch (index)
			{
				case 0: return x;
				case 1: return y;
			}
        }

		T length()
		{
			return std::sqrt(x * x + y * y);
		}

		vec opposite()
		{
			return { -x, -y };
		}

		vec normalized()
		{
			return (*this != zero()) ? (*this /= length()) : zero();
		}

		static vec zero()
		{
			return { 0, 0 };
		}

		static T dot(const vec &v0, const vec &v1)
		{
			return v0.x * v1.x + v0.y * v1.y;
		}
	};
}