#pragma once

#include "gla.h"

namespace gla
{
    static const float PI = 3.1415927F;     // ratio of a circle's circumference to its diameter
    static const float PHI = 1.6180339F;    // golden ratio
    static const float TAU = 2 * PI;        // ratio of the circumference to the radius of a circle
    static const float E = 2.7182818F;      // Euler's number
    static const float EPSILON = 1e-5F;

    static float radians(float degrees)
    {
        return degrees * (PI / 180);
    }

    static float degrees(float radians)
    {
        return radians * (180 / PI);
    }

    template<typename T>
    static T clamp(T value, T min, T max)
    {
        value = (value < min) ? min : (value > max) ? max : value;

        return value;
    }

    template<typename T>
    static T lerp(const T a, const T b, float t)
    {
        return a + (b - a) * clamp(t, 0.0F, 1.0F);
    }

    template<typename T>
    static float random(T min, T max)
    {
        return static_cast<T>(rand()) / (RAND_MAX / (max - min)) + min;
    }
}