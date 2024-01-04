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