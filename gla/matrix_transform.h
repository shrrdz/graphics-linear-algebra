#pragma once

#include "vec3.h"
#include "mat4x4.h"

/*
   ┌--------------------------------------------------------------------------┐
   |                                                                          |
   | all matrices are in right-handed coordinate system by default:           |
   |                                                                          |
   |                 +y                                                       |
   |                   |                                                      |
   |                   |                                                      |
   |                   |________                                              |
   |                  /        +x                                             |
   |              +z /                                                        |
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
    GLA_NODISCARD GLA_CONSTEXPR mat<4, 4, T> translate(const mat<4, 4, T> &input, const vec<3, T> &scalar)
    {
        mat<4, 4, T> result = input;

        result[3][0] = input[3][0] + scalar.x;
        result[3][1] = input[3][1] + scalar.y;
        result[3][2] = input[3][2] + scalar.z;

        return result;
    }

    template<typename T>
    GLA_NODISCARD GLA_CONSTEXPR mat<4, 4, T> rotate_x(const mat<4, 4, T> &input, T angle)
    {
        mat<4, 4, T> result = mat4x4::identity();

        result[1][1] =   std::cos(angle);
        result[1][2] =   std::sin(angle);
        result[2][1] = - std::sin(angle);
        result[2][2] =   std::cos(angle);

        return input * result;
    }

    template<typename T>
    GLA_NODISCARD GLA_CONSTEXPR mat<4, 4, T> rotate_y(const mat<4, 4, T> &input, T angle)
    {
        mat<4, 4, T> result = mat4x4::identity();

        result[0][0] =   std::cos(angle);
        result[0][2] = - std::sin(angle);
        result[2][0] =   std::sin(angle);
        result[2][2] =   std::cos(angle);

        return input * result;
    }

    template<typename T>
    GLA_NODISCARD GLA_CONSTEXPR mat<4, 4, T> rotate_z(const mat<4, 4, T> &input, T angle)
    {
        mat<4, 4, T> result = mat4x4::identity();

        result[0][0] =   std::cos(angle);
        result[0][1] =   std::sin(angle);
        result[1][0] = - std::sin(angle);
        result[1][1] =   std::cos(angle);

        return input * result;
    }

    template<typename T>
    GLA_NODISCARD GLA_CONSTEXPR mat<4, 4, T> scale(const mat<4, 4, T> &input, const vec<3, T> &scalar)
    {
        mat<4, 4, T> result = input;

        result[0][0] = input[0][0] * scalar.x;
        result[1][1] = input[1][1] * scalar.y;
        result[2][2] = input[2][2] * scalar.z;

        return result;
    }

    // view matrix
    template<typename T>
    GLA_NODISCARD static GLA_CONSTEXPR mat<4, 4, T> view(const vec<3, T> &eye, const vec<3, T> &at, const vec<3, T> &up)
    {
        mat<4, 4, T> view = gla::mat4x4::identity();

        const vec<3, T> front = (at - eye).normalized();
        const vec<3, T> side  = vec<3, T>::cross(front, up).normalized();
        const vec<3, T> above = vec<3, T>::cross(side, front);

        view[0][0] =   side.x;
        view[0][1] =   above.x;
        view[0][2] = - front.x;

        view[1][0] =   side.y;
        view[1][1] =   above.y;
        view[1][2] = - front.y;

        view[2][0] =   side.z;
        view[2][1] =   above.z;
        view[2][2] = - front.z;

        view[3][0] = - vec<3, T>::dot(side, eye);
        view[3][1] = - vec<3, T>::dot(above, eye);
        view[3][2] =   vec<3, T>::dot(front, eye);

        return view;
    }

    // projection matrix - perspective
    template<typename T>
    GLA_NODISCARD static GLA_CONSTEXPR mat<4, 4, T> perspective(T fov_degrees, T aspect_ratio, T near, T far)
    {
        mat<4, 4, T> projection;

        const T tan_half_fov = std::tan(radians(fov_degrees) / 2);

        projection[0][0] =   1 / (aspect_ratio * tan_half_fov);
        projection[1][1] =   1 / tan_half_fov;
        projection[2][2] = - (far + near) / (far - near);
        projection[2][3] = - 1;
        projection[3][2] = - (2 * far * near) / (far - near);

        return projection;
    }

    // projection matrix - orthographic
    template<typename T>
    GLA_NODISCARD static GLA_CONSTEXPR mat<4, 4, T> orthographic(T left, T right, T bottom, T top, T near, T far)
    {
        mat<4, 4, T> projection = gla::mat4x4::identity();

        projection[0][0] =   2 / (right - left);
        projection[1][1] =   2 / (top - bottom);
        projection[2][2] = - 2 / (far - near);
        projection[3][0] = - (right + left) / (right - left);
        projection[3][1] = - (top + bottom) / (top - bottom);
        projection[3][2] = - (far + near) / (far - near);

        return projection;
    }
}