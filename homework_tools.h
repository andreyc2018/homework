#pragma once

#include "logging_allocator.h"
#include "allocator.h"
#include <map>
#include <algorithm>

namespace otus {
    constexpr int MaxElements = 10;
    using map_t = std::map<int, int>;
    using map_alloc_t = std::map<int, int, std::less<int>,
                                 hw_allocator<std::pair<int, int>,
                                              MaxElements>>;

    int factorial(int n);

    struct generator
    {
        int i = 0;
        std::pair<int, int> operator()() {
            int f = (i < MaxElements)? factorial(i) : 0;
            return std::make_pair(i++, f);
        }
    };

    template <typename MapType>
    MapType& fill(MapType& m) {
        otus::generator g;
        std::generate_n(std::inserter(m, m.begin()), otus::MaxElements, g);
        return m;
    }

    template <typename MapType>
    MapType& print(MapType& m) {
        std::for_each(m.begin(), m.end(), [](auto e) {
            std::cout << e.first << " " << e.second << "\n";
        });
        return m;
    }

}
