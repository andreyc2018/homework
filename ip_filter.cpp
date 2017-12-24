#include "ip_filter.h"
#include <iostream>
#include <algorithm>

//namespace {
//bool string_number_cmp(const std::string& lhs, const std::string& rhs)
//{
//    return (std::stoi(lhs) < std::stoi(rhs));
//}

//}

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

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
    std::sort(pool.begin(), pool.end(),
              [](const entry_t& lhs, const entry_t& rhs)
    {
        return std::lexicographical_compare(rhs.begin(), rhs.end(),
                                            lhs.begin(), lhs.end());
    });
    return pool;
}

void otus::print_reverse(std::ostream& out, otus::pool_t& pool)
{
    otus::reverse(pool);
    otus::print(out, pool);
}

void otus::print_filter_any(std::ostream& out, const otus::pool_t& pool, int value)
{
    pool_t dst = otus::filter_any(pool, value);
    print(out, dst);
}

otus::pool_t otus::filter_any(const otus::pool_t& pool, filter_t value)
{
    auto f = [&value](const pool_t::value_type& e)
    {
        return std::any_of(e.begin(), e.end(),
                           [&value](const entry_t::value_type& d) {
            return d == value;
        });
    };

    pool_t dst_pool;
    std::copy_if(pool.begin(), pool.end(), std::back_inserter(dst_pool), f);
    return dst_pool;
}
