#pragma once

#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <iostream>

namespace otus {

struct input_types_t
{
    using value_type = std::string;
    using result_t = std::vector<value_type>;
    static const value_type& to_result(const std::string& v) { return v; };
};

struct entry_types_t
{
    using value_type = uint32_t;
    using result_t = std::vector<value_type>;
    static value_type to_result(const std::string& v)
    {
        return (!v.empty())? std::stoi(v) : 0;
    };
};

using input_t = std::vector<input_types_t::value_type>;
using entry_t = std::vector<entry_types_t::value_type>;
using pool_t = std::vector<entry_t>;
using filter_t = pool_t::value_type::value_type;

template <typename R>
typename R::result_t split(const std::string& str, char d)
{
    typename R::result_t r;
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos) {
        r.push_back(R::to_result(str.substr(start, stop - start)));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    r.push_back(R::to_result(str.substr(start)));

    return r;
}

void print_reverse(std::ostream& out, pool_t& pool);
void print(std::ostream& out, const pool_t& pool);
std::ostream& print_entry(std::ostream& out, const entry_t& ip);
pool_t& reverse(pool_t& pool);

template<typename... Args>
pool_t filter(const pool_t& pool, Args... args)
{
    std::array<filter_t, sizeof... (args)> expr {args...};
    auto predicate = [&expr](const pool_t::value_type& e)
    {
        return std::equal(expr.begin(), expr.end(), e.begin());
    };

    pool_t dst_pool;
    std::copy_if(pool.begin(), pool.end(), std::back_inserter(dst_pool), predicate);
    return dst_pool;
}

pool_t filter_any(const pool_t& pool, filter_t value);

template<typename ... Args>
void print_filter(std::ostream& out, const pool_t& pool, Args ... args)
{
    pool_t dst = filter(pool, args ...);
    print(out, dst);
}

void print_filter_any(std::ostream& out, const pool_t& pool, int value);

}
