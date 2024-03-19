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

		static const std::size_t size() { return 4; }

		// ┌----------------------------------------------------┐
		// │    binary operators                                |
		// └----------------------------------------------------┘

		vec operator + (const vec &v) const { return vec(x + v.x, y + v.y, z + v.z, w + v.w); }
		vec operator - (const vec &v) const { return vec(x - v.x, y - v.y, z - v.z, w - v.w); }
		vec operator * (const vec &v) const { return vec(x * v.x, y * v.y, z * v.z, w * v.w); }
		vec operator / (const vec &v) const { return vec(x / v.x, y / v.y, z / v.z, w / v.w); }

		vec operator * (T scalar) const { return vec(x * scalar, y * scalar, z * scalar, w * scalar); }
		vec operator / (T scalar) const { return vec(x / scalar, y / scalar, z / scalar, w / scalar); }

		friend vec operator * (T scalar, const vec &v) { return vec(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar); }

		// ┌----------------------------------------------------┐
		// │    compound assignment operators                   |
		// └----------------------------------------------------┘
		
		vec & operator += (const vec &v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
		vec & operator -= (const vec &v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
		vec & operator *= (const vec &v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
		vec & operator /= (const vec &v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }

		vec & operator *= (T scalar) { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
		vec & operator /= (T scalar) { x /= scalar; y /= scalar; z /= scalar; w /= scalar; return *this; }

		// ┌----------------------------------------------------┐
		// │    comparison operators                            |
		// └----------------------------------------------------┘

		bool operator == (const vec &v) const { return x == v.x && y == v.y && z == v.z && w == v.w; }
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
				case 3: return w;

				default: GLA_ASSERT(false, "trying to access or write to a non-existent vec4 index!");
			}
		}

		const T & operator [] (std::size_t index) const
		{
			switch (index)
			{
				case 0: return x;
				case 1: return y;
				case 2: return z;
				case 3: return w;

				default: GLA_ASSERT(false, "trying to access or write to a non-existent vec4 index!");
			}
		}

		// ┌----------------------------------------------------┐
		// │    properties                                      |
		// └----------------------------------------------------┘

		T length()
		{
			GLA_STATIC_ASSERT(std::is_floating_point<T>::value, "function 'length()' only accepts floating-point value inputs!");

			return std::sqrt(x * x + y * y + z * z + w * w);
		}

		T squared_length()
		{
			return x * x + y * y + z * z + w * w;
		}

		vec opposite()
		{
			return { -x, y, -z, -w };
		}

		vec normalized()
		{
			GLA_STATIC_ASSERT(std::is_floating_point<T>::value, "function 'normalized()' only accepts floating-point value inputs!");

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

		static vec reflection(const vec &incident, const vec &normal)
		{
			return incident - 2 * dot(normal, incident) * normal;
		}

		static T distance(const vec &v0, const vec &v1)
		{
			GLA_STATIC_ASSERT(std::is_floating_point<T>::value, "function 'distance()' only accepts floating-point value inputs!");

			return std::sqrt((v1.x - v0.x) * (v1.x - v0.x) + (v1.y - v0.y) * (v1.y - v0.y) + (v1.z - v0.z) * (v1.z - v0.z));
		}
	};
}