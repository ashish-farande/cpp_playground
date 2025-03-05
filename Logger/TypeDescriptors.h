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


template <typename T>
class Span {
public:
    // Constructors
    template <std::size_t N>
    constexpr Span(std::array<T, N>& arr) noexcept
        : data_(arr.data()), size_(N) {}

    template <std::size_t N>
    constexpr Span(const std::array<T, N>& arr) noexcept
        : data_(arr.data()), size_(N) {}

    // Getter functions
    constexpr T* data() noexcept { return data_; }
    constexpr const T* data() const noexcept { return data_; }
    constexpr std::size_t size() const noexcept { return size_; }

    // Indexing
    constexpr T& operator[](std::size_t index) { return data_[index]; }
    constexpr const T& operator[](std::size_t index) const { return data_[index]; }

    // Iterators
    constexpr T* begin() noexcept { return data_; }
    constexpr const T* begin() const noexcept { return data_; }
    constexpr T* end() noexcept { return data_ + size_; }
    constexpr const T* end() const noexcept { return data_ + size_; }

private:
    const T* data_;
    std::size_t size_;
};

using TypeDescriptor = std::variant<Int, Float, CStr>;
using TypeDescriptors = Span<TypeDescriptor>;

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
