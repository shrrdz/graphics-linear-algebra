#pragma once

#include "vec3.h"
#include "mat4x4.h"

/*
   ┌--------------------------------------------------------------------------┐
   |                                                                          |
   | order of application:                                                    |
   |                                                                          |
   |        scale * z-rotation * y-rotation * x-rotation * translation        |
   |                                                                          |
   └--------------------------------------------------------------------------┘
*/

namespace gla
{
    template<typename T>
    mat<4, 4, T> translate(const mat<4, 4, T> &input, const vec<3, T> &scalar)
    {
        mat<4, 4, T> result = input;

        result[3][0] = input[3][0] + scalar.x;
        result[3][1] = input[3][1] + scalar.y;
        result[3][2] = input[3][2] + scalar.z;

        return result;
    }

    template<typename T>
    mat<4, 4, T> rotate_x(const mat<4, 4, T> &input, const T angle)
    {
        mat<4, 4, T> result = mat4x4::identity();

        result[1][1] =   std::cos(angle);
        result[1][2] =   std::sin(angle);
        result[2][1] = - std::sin(angle);
        result[2][2] =   std::cos(angle);

        return result * input;
    }

    template<typename T>
    mat<4, 4, T> rotate_y(const mat<4, 4, T> &input, const T angle)
    {
        mat<4, 4, T> result = mat4x4::identity();

        result[0][0] =   std::cos(angle);
        result[0][2] = - std::sin(angle);
        result[2][0] =   std::sin(angle);
        result[2][2] =   std::cos(angle);

        return result * input;
    }
    
    template<typename T>
    mat<4, 4, T> rotate_z(const mat<4, 4, T> &input, const T angle)
    {
        mat<4, 4, T> result = mat4x4::identity();

        result[0][0] =   std::cos(angle);
        result[0][1] =   std::sin(angle);
        result[1][0] = - std::sin(angle);
        result[1][1] =   std::cos(angle);

        return result * input;
    }

    template<typename T>
    mat<4, 4, T> scale(const mat<4, 4, T> &input, const vec<3, T> &scalar)
    {
        mat<4, 4, T> result = input;

        result[0][0] = input[0][0] * scalar.x;
        result[1][1] = input[1][1] * scalar.y;
        result[2][2] = input[2][2] * scalar.z;

        return result;
    }
}