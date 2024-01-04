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
	};
}