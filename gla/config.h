#pragma once

#define GLA_TRUE            1
#define GLA_FALSE           0

#define GLA_CPP17           201703L


#define GLA_USE_CONSTEXPR   GLA_TRUE
#define GLA_USE_NODISCARD   GLA_TRUE


#if GLA_USE_CONSTEXPR
    #define GLA_CONSTEXPR constexpr
#else
    #define GLA_CONSTEXPR
#endif

#if GLA_USE_NODISCARD && __cplusplus >= GLA_CPP17
    #define GLA_NODISCARD [[nodiscard]]
#else
    #define GLA_NODISCARD
#endif