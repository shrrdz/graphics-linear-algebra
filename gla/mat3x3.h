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
        // │    binary operators                                |
        // └----------------------------------------------------┘

        mat operator + (const mat &m) const
        {
            mat result;

            for (int c = 0; c < columns(); c++)
            {
                for (int r = 0; r < rows(); r++)
                {
                    result[c][r] = values[c][r] + m[c][r];
                }
            }

            return result;
        }

        mat operator - (const mat &m) const
        {
            mat result;

            for (int c = 0; c < columns(); c++)
            {
                for (int r = 0; r < rows(); r++)
                {
                    result[c][r] = values[c][r] - m[c][r];
                }
            }

            return result;
        }

        mat operator * (const mat &m) const
        {
            mat result;

            for (int c = 0; c < columns(); c++)
            {
                for (int r = 0; r < rows(); r++)
                {
                    result[c][r] = values[c][0] * m[0][r] + values[c][1] * m[1][r] + values[c][2] * m[2][r];
                }
            }

            return result;
        }

        mat operator * (T scalar) const
        {
            for (int c = 0; c < columns(); c++)
            {
                for (int r = 0; r < rows(); r++)
                {
                    values[c][r] *= scalar;
                }
            }

            return *this;
        }

		friend mat operator * (T scalar, const mat &m)
        {
            mat result;
            
            for (int c = 0; c < columns(); c++)
            {
                for (int r = 0; r < rows(); r++)
                {
                    result[c][r] = m[c][r] * scalar;
                }
            }

            return result;
        }

        // ┌----------------------------------------------------┐
        // │    compound assignment operators                   |
        // └----------------------------------------------------┘

        mat & operator += (const mat &m)
        {
            for (int c = 0; c < columns(); c++)
            {
                for (int r = 0; r < rows(); r++)
                {
                    values[c][r] += m[c][r];
                }
            }

            return *this;
        }

        mat & operator -= (const mat &m)
        {
            for (int c = 0; c < columns(); c++)
            {
                for (int r = 0; r < rows(); r++)
                {
                    values[c][r] -= m[c][r];
                }
            }

            return *this;
        }

        mat & operator *= (const mat &m)
        {
            for (int c = 0; c < columns(); c++)
            {
                for (int r = 0; r < rows(); r++)
                {
                    values[c][r] = values[c][0] * m[0][r] + values[c][1] * m[1][r] + values[c][2] * m[2][r];
                }
            }

            return *this;
        }

		// ┌----------------------------------------------------┐
		// │    comparison operators                            |
		// └----------------------------------------------------┘

        bool operator == (const mat &m) const
        {
            for (int c = 0; c < columns(); c++)
            {
                for (int r = 0; r < rows(); r++)
                {
                    if (values[c][r] != m[c][r])
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        bool operator != (const mat &m) const
        {
            return !(*this == m);
        }

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

        mat cofactor()
        {
            mat result;

            result[0][0] =    values[1][1] * values[2][2] - values[1][2] * values[2][1];
            result[0][1] = - (values[1][0] * values[2][2] - values[1][2] * values[2][0]);
            result[0][2] =    values[1][0] * values[2][1] - values[1][1] * values[2][0];

            result[1][0] = - (values[0][1] * values[2][2] - values[0][2] * values[2][1]);
            result[1][1] =    values[0][0] * values[2][2] - values[0][2] * values[2][0];
            result[1][2] = - (values[0][0] * values[2][1] - values[0][1] * values[2][0]);

            result[2][0] =    values[0][1] * values[1][2] - values[0][2] * values[1][1];
            result[2][1] = - (values[0][0] * values[1][2] - values[0][2] * values[1][0]);
            result[2][2] =    values[0][0] * values[1][1] - values[0][1] * values[1][0];

            return result;
        }

        mat adjugate()
        {
            return cofactor().transpose();
        }

        mat inverse()
        {
            GLA_ASSERT(determinant != 0, "the given mat3x3 is singular, therefore it does not have an inverse!")

            return adjugate() * (1 / determinant());
        }

        T trace()
        {
            return values[0][0] + values[1][1] + values[2][2];
        }

        T determinant()
        {
            return values[0][0] * values[1][1] * values[2][2] +
                   values[1][0] * values[2][1] * values[0][2] +
                   values[2][0] * values[0][1] * values[1][2] -
                
                   values[0][2] * values[1][1] * values[2][0] -
                   values[1][2] * values[2][1] * values[0][0] -
                   values[2][2] * values[0][1] * values[1][0];
        }

        mat<2, 2, T> submatrix(std::size_t remove_column, std::size_t remove_row)
        {
            GLA_ASSERT(remove_column < columns() && remove_row < rows(), "trying to remove a non-existant mat3x3 index!");

            mat<2, 2, T> result;

            int result_column = 0;
            
            for (int c = 0; c < columns(); c++)
            {
                // remove the column
                if (c == remove_column) continue;

                int result_row = 0;
                
                for (int r = 0; r < rows(); r++)
                {
                    // remove the row
                    if (r == remove_row) continue;

                    result[result_column][result_row] = values[c][r];

                    result_row++;
                }

                result_column++;
            }

            return result;
        }

        void insert(const float (&values)[3][3])
        {
            for (int c = 0; c < columns(); c++)
            {
                for (int r = 0; r < rows(); r++)
                {
                    this->values[c][r] = values[c][r];
                }
            }
        }
    };
}