#pragma once

#include <string>
#include <vector>

namespace otus {
using entry_t = std::vector<std::string>;
using pool_t = std::vector<entry_t>;

entry_t split(const std::string& str, char d);
std::ostream& print_reverse(std::ostream& out, pool_t pool);
std::ostream& print(std::ostream& out, const pool_t& pool);
pool_t& sort(pool_t& pool);
pool_t& reverse(pool_t& pool);

}
