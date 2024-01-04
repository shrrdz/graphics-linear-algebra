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
	};
}