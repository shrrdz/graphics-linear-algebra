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

        static const std::size_t size() { return 3; }

        // ┌----------------------------------------------------┐
        // │    binary operators                                |
        // └----------------------------------------------------┘

        vec operator + (const vec &v) const { return { x + v.x, y + v.y, z + v.z }; }
        vec operator - (const vec &v) const { return { x - v.x, y - v.y, z - v.z }; }
        vec operator * (const vec &v) const { return { x * v.x, y * v.y, z * v.z }; }
        vec operator / (const vec &v) const { return { x / v.x, y / v.y, z / v.z }; }

        vec operator * (T scalar) const { return { x * scalar, y * scalar, z * scalar }; }
        vec operator / (T scalar) const { return { x / scalar, y / scalar, z / scalar }; }

        friend vec operator * (T scalar, const vec &v) { return { v.x * scalar, v.y * scalar, v.z * scalar }; }

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

                default: GLA_ASSERT(false, "trying to access or write to a non-existent vec3 index!");
            }
        }

        const T & operator [] (std::size_t index) const
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

        T length() const
        {
            GLA_STATIC_ASSERT(std::is_floating_point<T>::value, "function 'length()' only accepts floating-point value inputs!");

            return std::sqrt(x * x + y * y + z * z);
        }

        T squared_length() const
        {
            return x * x + y * y + z * z;
        }

        vec opposite() const
        {
            return { -x, -y, -z };
        }

        vec normalized() const
        {
            GLA_STATIC_ASSERT(std::is_floating_point<T>::value, "function 'normalized()' only accepts floating-point value inputs!");

            return (*this != zero()) ? (*this / length()) : zero();
        }

        static vec zero()
        {
            return { 0, 0, 0 };
        }

        static vec right()
        {
            return { 1, 0, 0 };
        }

        static vec up()
        {
            return { 0, 1, 0 };
        }

        static vec forward()
        {
            return { 0, 0, -1 };
        }

        static T dot(const vec &v0, const vec &v1)
        {
            return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
        }

        static vec cross(const vec &v0, const vec &v1)
        {
            return { v0.y * v1.z - v0.z * v1.y, v0.z * v1.x - v0.x * v1.z, v0.x * v1.y - v0.y * v1.x };
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

        static vec min(const vec &v0, const vec &v1)
        {
            return { (v0.x < v1.x) ? v0.x : v1.x, (v0.y < v1.y) ? v0.y : v1.y, (v0.z < v1.z) ? v0.z : v1.z };
        }

        static vec max(const vec &v0, const vec &v1)
        {
            return { (v0.x > v1.x) ? v0.x : v1.x, (v0.y > v1.y) ? v0.y : v1.y, (v0.z > v1.z) ? v0.z : v1.z };
        }
    };
}