#include "ip_filter.h"
#include <iostream>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
otus::entry_t otus::split(const std::string &str, char d)
{
    otus::entry_t r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

std::ostream& otus::print(std::ostream& out, const otus::pool_t& pool)
{
    for(const auto& ip : pool) {
        print_entry(out, ip) << std::endl;
    }
    return out;
}

std::ostream &otus::print_entry(std::ostream &out, const entry_t& ip)
{
    for(size_t i = 0; i < ip.size(); ++i) {
        if (i != 0) {
            out << ".";
        }
        out << ip[i];
    }
    return out;
}

bool otus::operator<(const otus::entry_t& l, const otus::entry_t& r)
{
    if (l.size() < r.size())
        return true;
    if (r.size() < l.size())
        return false;
    for (size_t i = 0; i < l.size(); ++i) {
        if (std::stoi(l[i]) < std::stoi(r[i])) {
            return true;
        }
    }
    return false;
}

otus::pool_t& otus::sort(otus::pool_t &pool, bool reverse) {
    std::stable_sort(pool.begin(), pool.end(),
                     [reverse](const entry_t& l, const entry_t& r) {
                         for (size_t i = 0; i < l.size(); ++i) {
                             if ((reverse && std::stoi(l[i]) > std::stoi(r[i])) || std::stoi(l[i]) < std::stoi(r[i])) {
                                 return true;
                             }
                         }
                         return false;
                     });
    return pool;
}
