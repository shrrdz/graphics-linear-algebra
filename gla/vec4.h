#pragma once

#include "vector.h"

namespace gla
{
	template<typename T>
	struct vec<4, T>
	{
		T x, y, z, w;

		vec() : x(0), y(0), z(0), w(0) { }

		vec(T scalar) : x(scalar), y(scalar), z(scalar), w(scalar) { }

		vec(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) { }

		T length()
		{
			return std::sqrt(x * x + y * y + z * z + w * w);
		}

		vec opposite()
		{
			return { -x, y, -z, -w };
		}

		vec normalized()
		{
			return (*this != zero()) ? (*this /= length()) : zero();
		}

		static vec zero()
		{
			return { 0, 0, 0, 0 };
		}

		static T dot(const vec &v0, const vec &v1)
		{
			return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w;
		}

		static vec cross(const vec &v0, const vec &v1)
		{
			return vec(v0.y * v1.z - v0.z * v1.y, v0.z * v1.x - v0.x * v1.z, v0.x * v1.y - v0.y * v1.x, 0);
		}
	};
}