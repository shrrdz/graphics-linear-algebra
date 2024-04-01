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
                    result[c][r] = 0;

                    for (int v = 0; v < rows(); v++)
                    {
                        result[c][r] += values[v][r] * m[c][v];
                    }
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
            mat result;

            for (int c = 0; c < columns(); c++)
            {
                for (int r = 0; r < rows(); r++)
                {
                    result[c][r] = 0;

                    for (int v = 0; v < rows(); v++)
                    {
                        result[c][r] += values[v][r] * m[c][v];
                    }
                }
            }

            *this = result;

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

        mat cofactor()
        {
            mat result;

            result[0][0] =   values[1][1];
            result[0][1] = - values[1][0];
            result[1][0] = - values[0][1];
            result[1][1] =   values[0][0];

            return result;
        }

        mat adjugate()
        {
            return cofactor().transpose();
        }

        mat inverse()
        {
            GLA_ASSERT(determinant != 0, "the given mat2x2 is singular, therefore it does not have an inverse!")

            return adjugate() * (1 / determinant());
        }

        T trace()
        {
            return values[0][0] + values[1][1];
        }

        T determinant()
        {
            return values[0][0] * values[1][1] - values[0][1] * values[1][0];
        }

        void insert(const float (&values)[2][2])
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