#pragma once

namespace gla
{
    // ┌----------------------------------------------------┐
    // │    templates                                       |
    // └----------------------------------------------------┘

    template<std::size_t L, typename T>                 struct vec;

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
}