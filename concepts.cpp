#pragma once

#include <vector>
#include <set>
#include <concepts>

// template <typename Container>
// concept HashPushBack = requires(Container c, Container::value_type v) {
//     c.push_back(v);
// };

// Better way to define a concept which removes the references
template <typename Container>
concept HashPushBack = requires(Container c, std::remove_cvref_t<Container>::value_type v) {
    c.push_back(v);
};

template <typename Container, typename T>
void add(Container &cont1, const T &val)
{
    cont1.insert(val);
}

// Method 1
// template <typename Container, typename T>
//     requires HashPushBack<Container>
// void add(Container &cont1, const T &val)
// {
//     cont1.push_back(val);
// }

// Method 2
// template<HashPushBack Container, typename T>
// void add(Container& cont1, const T& val)
// {
//     cont1.push_back(val);
// }

// Method 3
void add(HashPushBack auto& cont1, const auto& val)
{
    cont1.push_back(val);
}

// Method 4
// void add(auto &cont1, const auto &val)
//     requires HashPushBack<std::remove_cvref_t<decltype(cont1)>>
// {
//     cont1.push_back(val);
// }

// Method 5 - can be used only if the reference is remove in the concept definition
// void add(auto &cont1, const auto &val)
//     requires HashPushBack<decltype(cont1)>
// {
//     cont1.push_back(val);
// }

void testConcepts()
{
    static_assert(HashPushBack<std::vector<int>>);
    static_assert(HashPushBack<std::vector<int> &>);

    static_assert(!HashPushBack<std::set<int>>);

    std::vector<int> c1;
    std::set<int> c2;

    add(c1, 42);
    add(c2, 42);
}