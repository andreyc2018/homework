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

std::ostream& print_reverse(std::ostream& out, pool_t pool);
std::ostream& print(std::ostream& out, const pool_t& pool);
std::ostream& print_entry(std::ostream& out, const entry_t& ip);

pool_t& reverse(pool_t& pool);

//template<typename T, typename... Args>
//struct filter_expresssion {
//    constexpr static size_t size = sizeof... (Args);
//    constexpr static std::array<T, size> expressions {{Args... args}};
//};

template<typename T, typename... Args>
pool_t filter(const pool_t& pool, T first, Args... args)
{
    pool_t dst_pool;
    std::array<T, sizeof... (args)+1> expr {first, args...};
    std::copy_if(pool.begin(), pool.end(),
                 std::back_inserter(dst_pool),
                 [&expr](const entry_t& e)
        {
//            std::cout << expr.size() << "\n\t";
            for (size_t i = 0; i < expr.size(); ++i) {
                if (std::stoi(e[i]) != expr[i])
                    return false;
//                std::cout << "i = " << i << " : " << expr[i] << " ";
            }
//            print_entry(std::cout, e) << "\n";
            return true;
        });
    return dst_pool;
}

template<typename ... Args>
std::ostream& print_filter(std::ostream& out, pool_t pool, Args ... args)
{
// out << sizeof... (args) << "\n";
    pool_t dst = filter(pool, args ...);
    print(out, dst);
    return out;
}
}
