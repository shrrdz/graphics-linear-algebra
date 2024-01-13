#pragma once

namespace gla
{
    // ┌----------------------------------------------------┐
    // │    templates                                       |
    // └----------------------------------------------------┘

    template<std::size_t L, typename T>                 struct vec;
    template<std::size_t C, std::size_t R, typename T>  struct mat;

    // ┌----------------------------------------------------┐
    // |    type definitions                                |
    // └----------------------------------------------------┘

    typedef vec<2, bool>            bvec2;
    typedef vec<3, bool>            bvec3;
    typedef vec<4, bool>            bvec4;

    typedef vec<2, int>             ivec2;
    typedef vec<3, int>             ivec3;
    typedef vec<4, int>             ivec4;

    typedef vec<2, float>           vec2;
    typedef vec<3, float>           vec3;
    typedef vec<4, float>           vec4;

    typedef vec<2, double>          dvec2;
    typedef vec<3, double>          dvec3;
    typedef vec<4, double>          dvec4;

    typedef vec<2, long>            lvec2;
    typedef vec<3, long>            lvec3;
    typedef vec<4, long>            lvec4;

    typedef mat<2, 2, bool>         bmat2x2;
    typedef mat<3, 3, bool>         bmat3x3;
    typedef mat<4, 4, bool>         bmat4x4;

    typedef mat<2, 2, int>          imat2x2;
    typedef mat<3, 3, int>          imat3x3;
    typedef mat<4, 4, int>          imat4x4;

    typedef mat<2, 2, float>        mat2x2;
    typedef mat<3, 3, float>        mat3x3;
    typedef mat<4, 4, float>        mat4x4;

    typedef mat<2, 2, double>       dmat2x2;
    typedef mat<3, 3, double>       dmat3x3;
    typedef mat<4, 4, double>       dmat4x4;

    typedef mat<2, 2, long>         lmat2x2;
    typedef mat<3, 3, long>         lmat3x3;
    typedef mat<4, 4, long>         lmat4x4;

    // ┌----------------------------------------------------┐
    // |    type aliases                                    |
    // └----------------------------------------------------┘

    template <typename T> using tvec2 = vec<2, T>;
    template <typename T> using tvec3 = vec<3, T>;
    template <typename T> using tvec4 = vec<4, T>;
}