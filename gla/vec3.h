#pragma once

#include "vector.h"

namespace gla
{
    template<typename T>
    struct vec<3, T>
    {
        T x, y, z;

        // ┌----------------------------------------------------┐
        // │    constructors                                    |
        // └----------------------------------------------------┘

        GLA_CONSTEXPR vec() : x(0), y(0), z(0) { }

        GLA_CONSTEXPR vec(T x, T y, T z) : x(x), y(y), z(z) { }

        GLA_CONSTEXPR explicit vec(T scalar) : x(scalar), y(scalar), z(scalar) { }

        // ┌----------------------------------------------------┐
        // │    binary operators                                |
        // └----------------------------------------------------┘

        GLA_NODISCARD GLA_CONSTEXPR vec operator + (const vec &v) const { return { x + v.x, y + v.y, z + v.z }; }
        GLA_NODISCARD GLA_CONSTEXPR vec operator - (const vec &v) const { return { x - v.x, y - v.y, z - v.z }; }
        GLA_NODISCARD GLA_CONSTEXPR vec operator * (const vec &v) const { return { x * v.x, y * v.y, z * v.z }; }
        GLA_NODISCARD GLA_CONSTEXPR vec operator / (const vec &v) const { return { x / v.x, y / v.y, z / v.z }; }

        GLA_NODISCARD GLA_CONSTEXPR vec operator * (T scalar) const { return { x * scalar, y * scalar, z * scalar }; }
        GLA_NODISCARD GLA_CONSTEXPR vec operator / (T scalar) const { return { x / scalar, y / scalar, z / scalar }; }

        GLA_NODISCARD GLA_CONSTEXPR friend vec operator * (T scalar, const vec &v) { return { v.x * scalar, v.y * scalar, v.z * scalar }; }

        // ┌----------------------------------------------------┐
        // │    compound assignment operators                   |
        // └----------------------------------------------------┘

        GLA_CONSTEXPR vec & operator += (const vec &v) { x += v.x; y += v.y; z += v.z; return *this; }
        GLA_CONSTEXPR vec & operator -= (const vec &v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
        GLA_CONSTEXPR vec & operator *= (const vec &v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
        GLA_CONSTEXPR vec & operator /= (const vec &v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

        GLA_CONSTEXPR vec & operator *= (T scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
        GLA_CONSTEXPR vec & operator /= (T scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

        // ┌----------------------------------------------------┐
        // │    comparison operators                            |
        // └----------------------------------------------------┘

        GLA_NODISCARD GLA_CONSTEXPR bool operator == (const vec &v) const { return x == v.x && y == v.y && z == v.z; }
        GLA_NODISCARD GLA_CONSTEXPR bool operator != (const vec &v) const { return !(*this == v); }

        // ┌----------------------------------------------------┐
        // │    access operators                                |
        // └----------------------------------------------------┘

        GLA_NODISCARD GLA_CONSTEXPR T & operator [] (std::size_t index)
        {
            switch (index)
            {
                case 0: return x;
                case 1: return y;
                case 2: return z;

                default: GLA_ASSERT(false, "trying to access or write to a non-existent vec3 index!");
            }
        }

        GLA_NODISCARD GLA_CONSTEXPR const T & operator [] (std::size_t index) const
        {
            switch (index)
            {
                case 0: return x;
                case 1: return y;
                case 2: return z;

                default: GLA_ASSERT(false, "trying to access or write to a non-existent vec3 index!");
            }
        }

        // ┌----------------------------------------------------┐
        // │    properties                                      |
        // └----------------------------------------------------┘

        GLA_NODISCARD static GLA_CONSTEXPR const std::size_t size()
        {
            return 3;
        }

        GLA_NODISCARD GLA_CONSTEXPR T length() const
        {
            GLA_STATIC_ASSERT(std::is_floating_point<T>::value, "function 'length()' only accepts floating-point value inputs!");

            return std::sqrt(x * x + y * y + z * z);
        }

        GLA_NODISCARD GLA_CONSTEXPR T squared_length() const
        {
            return x * x + y * y + z * z;
        }

        GLA_NODISCARD GLA_CONSTEXPR vec opposite() const
        {
            return { -x, -y, -z };
        }

        GLA_NODISCARD GLA_CONSTEXPR vec normalized() const
        {
            GLA_STATIC_ASSERT(std::is_floating_point<T>::value, "function 'normalized()' only accepts floating-point value inputs!");

            return (*this != zero()) ? (*this / length()) : zero();
        }

        GLA_NODISCARD static GLA_CONSTEXPR vec zero()
        {
            return { 0, 0, 0 };
        }

        GLA_NODISCARD static GLA_CONSTEXPR vec right()
        {
            return { 1, 0, 0 };
        }

        GLA_NODISCARD static GLA_CONSTEXPR vec up()
        {
            return { 0, 1, 0 };
        }

        GLA_NODISCARD static GLA_CONSTEXPR vec forward()
        {
            return { 0, 0, -1 };
        }

        GLA_NODISCARD static GLA_CONSTEXPR T dot(const vec &v0, const vec &v1)
        {
            return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
        }

        GLA_NODISCARD static GLA_CONSTEXPR vec cross(const vec &v0, const vec &v1)
        {
            return { v0.y * v1.z - v0.z * v1.y, v0.z * v1.x - v0.x * v1.z, v0.x * v1.y - v0.y * v1.x };
        }

        GLA_NODISCARD static GLA_CONSTEXPR vec reflection(const vec &incident, const vec &normal)
        {
            return incident - 2 * dot(normal, incident) * normal;
        }

        GLA_NODISCARD static GLA_CONSTEXPR T distance(const vec &v0, const vec &v1)
        {
            GLA_STATIC_ASSERT(std::is_floating_point<T>::value, "function 'distance()' only accepts floating-point value inputs!");

            return std::sqrt((v1.x - v0.x) * (v1.x - v0.x) + (v1.y - v0.y) * (v1.y - v0.y) + (v1.z - v0.z) * (v1.z - v0.z));
        }

        GLA_NODISCARD static GLA_CONSTEXPR vec min(const vec &v0, const vec &v1)
        {
            return { (v0.x < v1.x) ? v0.x : v1.x, (v0.y < v1.y) ? v0.y : v1.y, (v0.z < v1.z) ? v0.z : v1.z };
        }

        GLA_NODISCARD static GLA_CONSTEXPR vec max(const vec &v0, const vec &v1)
        {
            return { (v0.x > v1.x) ? v0.x : v1.x, (v0.y > v1.y) ? v0.y : v1.y, (v0.z > v1.z) ? v0.z : v1.z };
        }
    };
}