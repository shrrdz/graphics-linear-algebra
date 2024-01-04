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
	};
}