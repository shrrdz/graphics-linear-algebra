#pragma once

#define GLA_TRUE            1
#define GLA_FALSE           0


#define GLA_USE_CONSTEXPR   GLA_TRUE


#if GLA_USE_CONSTEXPR
    #define GLA_CONSTEXPR constexpr
#else
    #define GLA_CONSTEXPR
#endif