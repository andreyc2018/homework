#pragma once

#include <string>
#include <vector>

namespace otus {

using pool_t = std::vector<std::vector<std::string>>;
using entry_t = std::vector<std::string>;
entry_t split(const std::string &str, char d);
std::ostream & print(std::ostream& out, const otus::pool_t& pool);
pool_t& sort(pool_t& pool, bool reverse);
std::ostream &print_entry(std::ostream &out, const std::vector<std::string> &ip);
bool operator<(const otus::entry_t& l, const otus::entry_t& r);
}
