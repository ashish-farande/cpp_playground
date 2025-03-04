#ifndef A2AE456B_683F_49D9_87F3_C98F503E0DAF
#define A2AE456B_683F_49D9_87F3_C98F503E0DAF

#include <stdio.h>
#include <variant>
#include <array>

struct Int
{
};

struct Float
{
};

struct CStr
{
};


using TypeDescriptor = std::variant<Int, Float, CStr>;

template <size_t N>
using TypeDescriptors = std::array<TypeDescriptor, N>;

template <typename T>
struct GetTypeDescriptor;

template <>
struct GetTypeDescriptor<int>
{
    static constexpr TypeDescriptor value{Int{}};
};

template <>
struct GetTypeDescriptor<float>
{
    static constexpr TypeDescriptor value{Float{}};
};

template <>
struct GetTypeDescriptor<const char *>
{
    static constexpr TypeDescriptor value{CStr{}};
};


#endif /* A2AE456B_683F_49D9_87F3_C98F503E0DAF */
