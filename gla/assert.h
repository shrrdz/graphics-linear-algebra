#pragma once

#define GLA_ASSERT(c, note)                          \
                                                     \
    if (!(c))                                        \
    {                                                \
        std::cerr << "Assertion failed: " << note    \
                  << " :: file: " << __FILE__        \
                  << " :: line: " << __LINE__        \
                  << std::endl; std::abort();        \
    }                                                \

#define GLA_STATIC_ASSERT(c, note) static_assert(c, note)