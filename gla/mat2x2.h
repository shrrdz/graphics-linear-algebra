#pragma once

#include "matrix.h"

namespace gla
{
    template<typename T>
    struct mat<2, 2, T>
    {
        typedef vec<2, T> column;
        typedef vec<2, T> row;

        GLA_NODISCARD static GLA_CONSTEXPR const std::size_t columns() { return column::size(); };
        GLA_NODISCARD static GLA_CONSTEXPR const std::size_t rows() { return row::size(); };

    private:
        column values[2];

    public:
        // ┌----------------------------------------------------┐
        // │    constructors                                    |
        // └----------------------------------------------------┘

        GLA_CONSTEXPR mat() : values { vec<2, T>(0), vec<2, T>(0) } { }

        GLA_CONSTEXPR mat(const column &c0, const column &c1) : values { c0, c1 } { }

        GLA_CONSTEXPR explicit mat(T scalar) : values { vec<2, T>(scalar), vec<2, T>(scalar) } { }

        GLA_CONSTEXPR mat(T x0, T x1, T y0, T y1) : values { vec<2, T>(x0, x1), vec<2, T>(y0, y1) } { }

        // ┌----------------------------------------------------┐
        // │    binary operators                                |
        // └----------------------------------------------------┘

        GLA_NODISCARD GLA_CONSTEXPR mat operator + (const mat &m) const
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

        GLA_NODISCARD GLA_CONSTEXPR mat operator - (const mat &m) const
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

        GLA_NODISCARD GLA_CONSTEXPR mat operator * (const mat &m) const
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

        GLA_NODISCARD GLA_CONSTEXPR mat operator * (T scalar) const
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

		GLA_NODISCARD GLA_CONSTEXPR friend mat operator * (T scalar, const mat &m)
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

        GLA_CONSTEXPR mat & operator += (const mat &m)
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

        GLA_CONSTEXPR mat & operator -= (const mat &m)
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

        GLA_CONSTEXPR mat & operator *= (const mat &m)
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

        GLA_NODISCARD GLA_CONSTEXPR bool operator == (const mat &m) const
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

        GLA_NODISCARD GLA_CONSTEXPR bool operator != (const mat &m) const
        {
            return !(*this == m);
        }

        // ┌----------------------------------------------------┐
        // │    access operators                                |
        // └----------------------------------------------------┘

        GLA_NODISCARD GLA_CONSTEXPR column & operator [] (std::size_t index)
        {
            GLA_ASSERT(index < 2, "trying to access or write to a non-existant mat2x2 index!")

            return values[index];
        }

        GLA_NODISCARD GLA_CONSTEXPR const column & operator [] (std::size_t index) const
        {
            GLA_ASSERT(index < 2, "trying to access or write to a non-existant mat2x2 index!")

            return values[index];
        }

        // ┌----------------------------------------------------┐
        // │    properties                                      |
        // └----------------------------------------------------┘

        GLA_NODISCARD static GLA_CONSTEXPR mat identity()
        {
            mat identity;

            identity[0][0] = 1;
            identity[1][1] = 1;

            return identity;
        }

        GLA_NODISCARD GLA_CONSTEXPR mat transpose()
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

        GLA_NODISCARD GLA_CONSTEXPR mat cofactor()
        {
            mat result;

            result[0][0] =   values[1][1];
            result[0][1] = - values[1][0];
            result[1][0] = - values[0][1];
            result[1][1] =   values[0][0];

            return result;
        }

        GLA_NODISCARD GLA_CONSTEXPR mat adjugate()
        {
            return cofactor().transpose();
        }

        GLA_NODISCARD GLA_CONSTEXPR mat inverse()
        {
            GLA_ASSERT(determinant != 0, "the given mat2x2 is singular, therefore it does not have an inverse!")

            return adjugate() * (1 / determinant());
        }

        GLA_NODISCARD GLA_CONSTEXPR T trace()
        {
            return values[0][0] + values[1][1];
        }

        GLA_NODISCARD GLA_CONSTEXPR T determinant()
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