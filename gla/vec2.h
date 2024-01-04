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