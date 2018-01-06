#pragma once

#include "allocator.h"
#include "sl_list.h"
#include <map>
#include <algorithm>
#include <numeric>

namespace otus {

constexpr size_t MaxElements = 10;

using map_t = std::map<int, int>;
using map_alloc_t = std::map<int, int, std::less<int>,
                             hw_allocator<std::pair<const int, int>,
                                          MaxElements>>;
using custom_list_t = single_linked_list<int>;
using custom_list_alloc_t = single_linked_list<int, hw_allocator<int, MaxElements>>;

int factorial(int n);

struct pair_generator
{
    size_t i = 0;
    size_t max = 0;
    pair_generator(size_t n) : max(n)
    {
    }

    std::pair<int, int> operator()()
    {
        int f = (i < max) ? factorial(i) : 0;
        return std::make_pair(i++, f);
    }
};

template<typename MapType>
MapType& fill_map(MapType& m, size_t n)
{
    otus::pair_generator g(n);
    std::generate_n(std::inserter(m, m.begin()), n, g);
    return m;
}

template<typename MapType>
void print_map(std::ostream& out, const MapType& m)
{
    for (const auto& e : m) {
        out << e.first << " " << e.second << "\n";
    }
}

template<typename ListType>
ListType& fill_list(ListType& l, size_t n)
{
    l.resize(n);
    std::iota(l.begin(), l.end(), 0);
    return l;
}

template<typename ListType>
void print_list(std::ostream& out, const ListType& l)
{
    char comma[3] = {'\0', ' ', '\0'};
    for (const auto& e : l) {
        out << comma << e;
        comma[0] = ',';
    }
    out << "\n";
}

}
