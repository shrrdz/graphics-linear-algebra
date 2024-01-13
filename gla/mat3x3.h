#pragma once

#include "matrix.h"

namespace gla
{
    template<typename T>
    struct mat<3, 3, T>
    {
        typedef vec<3, T> column;
        typedef vec<3, T> row;
        
    private:
        column values[3];
        
    public:
        static const std::size_t columns() { return column::size(); };
        static const std::size_t rows()    { return row::size(); };

        // ┌----------------------------------------------------┐
        // │    access operators                                |
        // └----------------------------------------------------┘

        column & operator [] (std::size_t index)
        {
            GLA_ASSERT(index < 3, "trying to access or write to a non-existant mat3x3 index!")
            
            return values[index];
        }

        const column & operator [] (std::size_t index) const
        {
            GLA_ASSERT(index < 3, "trying to access or write to a non-existant mat3x3 index!")
            
            return values[index];
        }

        // ┌----------------------------------------------------┐
        // │    properties                                      |
        // └----------------------------------------------------┘

        static mat identity()
        {
            mat identity;

            identity[0][0] = 1;
            identity[1][1] = 1;
            identity[2][2] = 1;

            return identity;
        }
    };
}