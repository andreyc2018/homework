#pragma once

#include "allocator.h"
#include <map>
#include <algorithm>

namespace otus {
    constexpr size_t MaxElements = 10;
    using map_t = std::map<int, int>;
    using map_alloc_t = std::map<int, int, std::less<int>,
                                 hw_allocator<std::pair<const int, int>,
                                              MaxElements>>;
    int factorial(int n);

    struct generator
    {
        size_t i = 0;
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
        std::for_each(m.begin(), m.end(), [](typename MapType::value_type e) {
            std::cout << e.first << " " << e.second << "\n";
        });
        return m;
    }

}
