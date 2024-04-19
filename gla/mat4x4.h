#pragma once

#include "matrix.h"

namespace gla
{
    template<typename T>
    struct mat<4, 4, T>
    {
        typedef vec<4, T> column;
        typedef vec<4, T> row;

        GLA_NODISCARD static GLA_CONSTEXPR const std::size_t columns() { return column::size(); };
        GLA_NODISCARD static GLA_CONSTEXPR const std::size_t rows() { return row::size(); };

    private:
        column values[4];

    public:
        // ┌----------------------------------------------------┐
        // │    constructors                                    |
        // └----------------------------------------------------┘

        GLA_CONSTEXPR mat() : values { vec<4, T>(0), vec<4, T>(0), vec<4, T>(0), vec<4, T>(0) } { }

        GLA_CONSTEXPR mat(const column &c0, const column &c1, const column &c2, const column &c3) : values { c0, c1, c2, c3 } { }

        GLA_CONSTEXPR explicit mat(T scalar) : values { vec<4, T>(scalar), vec<4, T>(scalar), vec<4, T>(scalar), vec<4, T>(scalar) } { }

        GLA_CONSTEXPR mat(T x0, T x1, T x2, T x3, T y0, T y1, T y2, T y3, T z0, T z1, T z2, T z3, T w0, T w1, T w2, T w3) : values
        {
            vec<4, T>(x0, x1, x2, x3), vec<4, T>(y0, y1, y2, y3), vec<4, T>(z0, z1, z2, z3), vec<4, T>(w0, w1, w2, w3),
        } { }

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
            GLA_ASSERT(index < 4, "trying to access or write to a non-existant mat4x4 index!")

            return values[index];
        }

        GLA_NODISCARD GLA_CONSTEXPR const column & operator [] (std::size_t index) const
        {
            GLA_ASSERT(index < 4, "trying to access or write to a non-existant mat4x4 index!")

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
            identity[2][2] = 1;
            identity[3][3] = 1;

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

            for (int c = 0; c < columns(); c++)
            {
                for (int r = 0; r < rows(); r++)
                {
                    mat<3, 3, T> minor_matrix = submatrix(c, r);

                    T determinant = minor_matrix.determinant();

                    result[c][r] = (((c + r) % 2 == 0) || determinant == 0) ? determinant : -determinant;
                }
            }

            return result;
        }

        GLA_NODISCARD GLA_CONSTEXPR mat adjugate()
        {
            return cofactor().transpose();
        }

        GLA_NODISCARD GLA_CONSTEXPR mat inverse()
        {
            GLA_ASSERT(determinant != 0, "the given mat4x4 is singular, therefore it does not have an inverse!")

            return adjugate() * (1 / determinant());
        }

        GLA_NODISCARD GLA_CONSTEXPR T trace()
        {
            return values[0][0] + values[1][1] + values[2][2] + values[3][3];
        }

        GLA_NODISCARD GLA_CONSTEXPR T determinant()
        {
            return values[0][0] *
                   (
                       values[1][1] * (values[2][2] * values[3][3] - values[2][3] * values[3][2]) -
                       values[2][1] * (values[1][2] * values[3][3] - values[1][3] * values[3][2]) +
                       values[3][1] * (values[1][2] * values[2][3] - values[1][3] * values[2][2])
                   )
                   - values[1][0] *
                   (
                       values[0][1] * (values[2][2] * values[3][3] - values[2][3] * values[3][2]) -
                       values[2][1] * (values[0][2] * values[3][3] - values[0][3] * values[3][2]) +
                       values[3][1] * (values[0][2] * values[2][3] - values[0][3] * values[2][2])
                   )
                   + values[2][0] *
                   (
                       values[0][1] * (values[1][2] * values[3][3] - values[1][3] * values[3][2]) -
                       values[1][1] * (values[0][2] * values[3][3] - values[0][3] * values[3][2]) +
                       values[3][1] * (values[0][2] * values[1][3] - values[0][3] * values[1][2])
                   )
                   - values[3][0] *
                   (
                       values[0][1] * (values[1][2] * values[2][3] - values[1][3] * values[2][2]) -
                       values[1][1] * (values[0][2] * values[2][3] - values[0][3] * values[2][2]) +
                       values[2][1] * (values[0][2] * values[1][3] - values[0][3] * values[1][2])
                   );
        }

        GLA_NODISCARD GLA_CONSTEXPR mat<3, 3, T> submatrix(std::size_t remove_column, std::size_t remove_row) const
        {
            GLA_ASSERT(remove_column < columns() && remove_row < rows(), "trying to remove a non-existant mat4x4 index!");

            mat<3, 3, T> result;

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

        void insert(const float (&values)[4][4])
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