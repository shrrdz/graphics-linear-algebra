#pragma once

#include "gla.h"

namespace gla
{
    static const float PI = 3.1415927F;
    static const float PHI = 1.6180399F;
    static const float TAU = 2 * PI;
    static const float EPSILON = 1e-5F;

    static float radians(const float degrees)
    {
        return degrees * (PI / 180);
    }

    static float degrees(const float radians)
    {
        return radians * (180 / PI);
    }

    template<typename T>
    static T clamp(T value, const T min, const T max)
    {
        value = (value < min) ? min : (value > max) ? max : value;

        return value;
    }

    template<typename T>
    static T lerp(const T a, const T b, const float t)
    {
        return a + (b - a) * clamp(t, 0.0F, 1.0F);
    }

    template<typename T>
    static float random(const T min, const T max)
    {
        return static_cast<T>(rand()) / (RAND_MAX / (max - min)) + min;
    }
}