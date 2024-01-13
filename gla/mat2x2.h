#pragma once

#include "matrix.h"

namespace gla
{
    template<typename T>
    struct mat<2, 2, T>
    {
        typedef vec<2, T> column;
        typedef vec<2, T> row;
        
    private:
        column values[2];
        
    public:
        static const std::size_t columns() { return column::size(); };
        static const std::size_t rows()    { return row::size(); };

        // ┌----------------------------------------------------┐
        // │    access operators                                |
        // └----------------------------------------------------┘

        column & operator [] (std::size_t index)
        {
            GLA_ASSERT(index < 2, "trying to access or write to a non-existant mat2x2 index!")
            
            return values[index];
        }

        const column & operator [] (std::size_t index) const
        {
            GLA_ASSERT(index < 2, "trying to access or write to a non-existant mat2x2 index!")
            
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