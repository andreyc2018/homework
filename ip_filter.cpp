#include "ip_filter.h"
#include <iostream>
#include <algorithm>

namespace {
bool string_number_cmp(const std::string& lhs, const std::string& rhs)
{
    return (std::stoi(lhs) < std::stoi(rhs));
}

}

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
otus::entry_t otus::split(const std::string& str, char d)
{
    otus::entry_t r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    r.push_back(str.substr(start));

    return r;
}

std::ostream& otus::print_entry(std::ostream& out, const otus::entry_t& ip)
{
    for (size_t i = 0; i < ip.size(); ++i) {
        if (i != 0) {
            out << ".";
        }
        out << ip[i];
    }
    return out;
}

void otus::print(std::ostream& out, const otus::pool_t& pool)
{
    for (const auto& ip : pool) {
        print_entry(out, ip) << std::endl;
    }
}

otus::pool_t& otus::reverse(otus::pool_t& pool)
{
    std::stable_sort(pool.begin(), pool.end(),
                     [](const entry_t& lhs, const entry_t& rhs)
    {
        return std::lexicographical_compare(rhs.begin(), rhs.end(),
                                            lhs.begin(), lhs.end(),
                                            string_number_cmp);
    });
    return pool;
}

void otus::print_reverse(std::ostream& out, otus::pool_t pool)
{
    otus::reverse(pool);
    otus::print(out, pool);
}

void otus::print_filter_any(std::ostream& out, pool_t pool, int value)
{
    pool_t dst = otus::filter_any(pool, value);
    print(out, dst);
}
