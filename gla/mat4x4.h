#pragma once

#include "matrix.h"

namespace gla
{
    template<typename T>
    struct mat<4, 4, T>
    {
        typedef vec<4, T> column;
        typedef vec<4, T> row;
        
    private:
        column values[4];
        
    public:
        static const std::size_t columns() { return column::size(); };
        static const std::size_t rows()    { return row::size(); };

        // ┌----------------------------------------------------┐
        // │    access operators                                |
        // └----------------------------------------------------┘

        column & operator [] (std::size_t index)
        {
            GLA_ASSERT(index < 4, "trying to access or write to a non-existant mat4x4 index!")
            
            return values[index];
        }

        const column & operator [] (std::size_t index) const
        {
            GLA_ASSERT(index < 4, "trying to access or write to a non-existant mat4x4 index!")
            
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
            identity[3][3] = 1;

            return identity;
        }

        mat transpose()
        {
            mat result;

            for (int c = 0; c < columns(); c++)
            {
                for (int r = 0; r < rows(); r++)
                {
                    result.values[c][r] = values[r][c];
                }
            }

            return result;
        }
    };
}