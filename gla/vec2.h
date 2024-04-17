#pragma once

#include "vector.h"

namespace gla
{
    template<typename T>
    struct vec<2, T>
    {
        T x, y;

        // ┌----------------------------------------------------┐
        // │    constructors                                    |
        // └----------------------------------------------------┘

        GLA_CONSTEXPR vec() : x(0), y(0) { }

        GLA_CONSTEXPR vec(T x, T y) : x(x), y(y) { }

        GLA_CONSTEXPR explicit vec(T scalar) : x(scalar), y(scalar) { }

        // ┌----------------------------------------------------┐
        // │    binary operators                                |
        // └----------------------------------------------------┘

        GLA_NODISCARD GLA_CONSTEXPR vec operator + (const vec &v) const { return { x + v.x, y + v.y }; }
        GLA_NODISCARD GLA_CONSTEXPR vec operator - (const vec &v) const { return { x - v.x, y - v.y }; }
        GLA_NODISCARD GLA_CONSTEXPR vec operator * (const vec &v) const { return { x * v.x, y * v.y }; }
        GLA_NODISCARD GLA_CONSTEXPR vec operator / (const vec &v) const { return { x / v.x, y / v.y }; }

        GLA_NODISCARD GLA_CONSTEXPR vec operator * (T scalar) const { return { x * scalar, y * scalar }; }
        GLA_NODISCARD GLA_CONSTEXPR vec operator / (T scalar) const { return { x / scalar, y / scalar }; }

        GLA_NODISCARD GLA_CONSTEXPR friend vec operator * (T scalar, const vec &v) { return { v.x * scalar, v.y * scalar }; }

        // ┌----------------------------------------------------┐
        // │    compound assignment operators                   |
        // └----------------------------------------------------┘

        GLA_CONSTEXPR vec & operator += (const vec &v) { x += v.x; y += v.y; return *this; }
        GLA_CONSTEXPR vec & operator -= (const vec &v) { x -= v.x; y -= v.y; return *this; }
        GLA_CONSTEXPR vec & operator *= (const vec &v) { x *= v.x; y *= v.y; return *this; }
        GLA_CONSTEXPR vec & operator /= (const vec &v) { x /= v.x; y /= v.y; return *this; }

        GLA_CONSTEXPR vec & operator *= (T scalar) { x *= scalar; y *= scalar; return *this; }
        GLA_CONSTEXPR vec & operator /= (T scalar) { x /= scalar; y /= scalar; return *this; }

        // ┌----------------------------------------------------┐
        // │    comparison operators                            |
        // └----------------------------------------------------┘

        GLA_NODISCARD GLA_CONSTEXPR bool operator == (const vec &v) const { return x == v.x && y == v.y; }
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

                default: GLA_ASSERT(false, "trying to access or write to a non-existent vec2 index!");
            }
        }

        GLA_NODISCARD GLA_CONSTEXPR const T & operator [] (std::size_t index) const
        {
            switch (index)
            {
                case 0: return x;
                case 1: return y;

                default: GLA_ASSERT(false, "trying to access or write to a non-existent vec2 index!");
            }
        }

        // ┌----------------------------------------------------┐
        // │    properties                                      |
        // └----------------------------------------------------┘

        GLA_NODISCARD static GLA_CONSTEXPR const std::size_t size()
        {
            return 2;
        }

        GLA_NODISCARD GLA_CONSTEXPR T length() const
        {
            GLA_STATIC_ASSERT(std::is_floating_point<T>::value, "function 'length()' only accepts floating-point value inputs!");

            return std::sqrt(x * x + y * y);
        }

        GLA_NODISCARD GLA_CONSTEXPR T squared_length() const
        {
            return x * x + y * y;
        }

        GLA_NODISCARD GLA_CONSTEXPR vec opposite() const
        {
            return { -x, -y };
        }

        GLA_NODISCARD GLA_CONSTEXPR vec normalized() const
        {
            GLA_STATIC_ASSERT(std::is_floating_point<T>::value, "function 'normalized()' only accepts floating-point value inputs!");

            return (*this != zero()) ? (*this / length()) : zero();
        }

        GLA_NODISCARD static GLA_CONSTEXPR vec zero()
        {
            return { 0, 0 };
        }

        GLA_NODISCARD static GLA_CONSTEXPR T dot(const vec &v0, const vec &v1)
        {
            return v0.x * v1.x + v0.y * v1.y;
        }

        GLA_NODISCARD static GLA_CONSTEXPR vec reflection(const vec &incident, const vec &normal)
        {
            return incident - 2 * dot(normal, incident) * normal;
        }

        GLA_NODISCARD static GLA_CONSTEXPR T distance(const vec &v0, const vec &v1)
        {
            GLA_STATIC_ASSERT(std::is_floating_point<T>::value, "function 'distance()' only accepts floating-point value inputs!");

            return std::sqrt((v1.x - v0.x) * (v1.x - v0.x) + (v1.y - v0.y) * (v1.y - v0.y));
        }

        GLA_NODISCARD static GLA_CONSTEXPR vec min(const vec &v0, const vec &v1)
        {
            return { (v0.x < v1.x) ? v0.x : v1.x, (v0.y < v1.y) ? v0.y : v1.y };
        }

        GLA_NODISCARD static GLA_CONSTEXPR vec max(const vec &v0, const vec &v1)
        {
            return { (v0.x > v1.x) ? v0.x : v1.x, (v0.y > v1.y) ? v0.y : v1.y };
        }
    };
}