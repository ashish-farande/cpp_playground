#pragma once
#include <algorithm>
#include <ranges>
#include <print>
#include <iostream>

void testRanges()
{

    std::array<int, 6> a{6, 5, 4, 3, 2, 1};
    std::ranges::sort(a);

    // std::print("{} \n", a);
    std::ranges::for_each(a, [&](const auto &val)
                          { std::cout << val << " "; });
    std::cout << '\n';

    auto iter = std::ranges::find_if(a, [](int i)
                                     { return i == 6; });

    if (iter != a.end())
        std::cout << "i: " << *iter << '\n';

    auto divisible_by_3 = std::views::filter([](int i)
                                             { return i % 3 == 0; });
    auto x = a | divisible_by_3;

    std::ranges::for_each(x, [&](const auto &val)
                          { std::cout << val << " "; });

    std::cout << '\n';
}
