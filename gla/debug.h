#pragma once

#include "gla.h"

namespace gla
{
    namespace debug
    {
        template<std::size_t D, typename T>
        static void print_vec(const vec<D, T> &input)
        {
            std::cout << "[ ";

            for (int i = 0; i < D; i++)
            {
                std::cout << input[i];

                if (i < D - 1)
                {
                    std::cout << ", ";
                }
            }

            std::cout << " ]" << std::endl;
        }

        template<std::size_t C, std::size_t R, typename T>
        static void print_mat(const mat<C, R, T> &input)
        {
            for (int r = 0; r < R; r++)
            {
                std::cout << "| ";

                for (int c = 0; c < C; c++)
                {
                    std::cout << input[c][r];

                    if (c < C - 1)
                    {
                        std::cout << " ";
                    }
                }

                std::cout << " |" << std::endl;
            }
        }
    }
}