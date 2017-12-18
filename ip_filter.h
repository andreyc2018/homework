#pragma once

#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <iostream>

namespace otus {
using entry_t = std::vector<std::string>;
using pool_t = std::vector<entry_t>;

entry_t split(const std::string& str, char d);

void print_reverse(std::ostream& out, pool_t pool);
void print(std::ostream& out, const pool_t& pool);
std::ostream& print_entry(std::ostream& out, const entry_t& ip);

pool_t& reverse(pool_t& pool);

template<typename T, typename... Args>
pool_t filter(const pool_t& pool, T first, Args... args)
{
    std::array<T, sizeof... (args)+1> expr {first, args...};
    auto f = [&expr](const entry_t& e)
    {
        for (size_t i = 0; i < expr.size(); ++i) {
            if (std::stoi(e[i]) != expr[i])
                return false;
        }
        return true;
    };

    pool_t dst_pool;
    std::copy_if(pool.begin(), pool.end(), std::back_inserter(dst_pool), f);
    return dst_pool;
}

template<typename T>
pool_t filter_any(const pool_t& pool, T value)
{
    auto f = [&value](const entry_t& e)
    {
        for (size_t i = 0; i < e.size(); ++i) {
            if (std::stoi(e[i]) == value)
                return true;
        }
        return false;
    };

    pool_t dst_pool;
    std::copy_if(pool.begin(), pool.end(), std::back_inserter(dst_pool), f);
    return dst_pool;
}

template<typename ... Args>
void print_filter(std::ostream& out, pool_t pool, Args ... args)
{
    pool_t dst = filter(pool, args ...);
    print(out, dst);
}

void print_filter_any(std::ostream& out, pool_t pool, int value);

}
