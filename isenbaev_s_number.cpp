#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <type_traits>
#include <limits>
#include <array>
#include <functional>

using data = std::vector<std::string>;
using data_set = std::map<std::string, size_t>;
using uv_nodes = std::array<std::reference_wrapper<const std::string>, 2>;
using dist = std::map<size_t, size_t>;
using graph = std::map<size_t, std::vector<size_t>>;
constexpr size_t inf = std::numeric_limits<size_t>::max();

void add_node(data& dta, dist& dst, graph& g, const uv_nodes& uv_n)
{
    std::array<size_t, 2> uv;
    for (size_t i = 0; i < uv_n.size(); ++i) {
        const std::string& ref = uv_n[i].get();
        auto it = std::find(dta.begin(), dta.end(), ref);
        if (it == dta.end()) {
            dta.push_back(uv_n[i]);
            it = dta.end() - 1;
            dst.insert(std::make_pair(dta.size()-1, inf));
        }
        uv[i] = std::distance(dta.begin(), it);
    }
    g[uv[0]].push_back(uv[1]);
    g[uv[1]].push_back(uv[0]);
}

void tokenize(const std::string& s, std::vector<std::string>& v,
              const std::string& delimiters = " ")
{
    std::string::size_type lastPos = s.find_first_not_of(delimiters, 0);
    std::string::size_type pos = s.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos) {
        v.push_back(s.substr(lastPos, pos - lastPos));
        lastPos = s.find_first_not_of(delimiters, pos);
        pos = s.find_first_of(delimiters, lastPos);
    }
}

void read_input(data& dta, dist& dst, graph& g)
{
    size_t n;
    std::string line;
    std::getline(std::cin, line);
    n = std::stoul(line);
    std::vector<std::string> v;
    v.reserve(3);
    for (size_t i = 0; i < n; ++i) {
        std::getline(std::cin, line);
        tokenize(line, v);
        for (size_t j = 0; j < v.size(); ++j) {
            size_t j_p = (j < v.size()-1)? j+1 : 0;
            uv_nodes uv_n { { std::cref(v[j]), std::cref(v[j_p]) } };
            add_node(dta, dst, g, uv_n);
        }
        v.clear();
    }
}

void create_numbers(dist& dst, graph& g, size_t initial)
{
    dist sd;
    sd.insert(std::make_pair(initial, 0));
    dst[initial] = 0;
    while(!sd.empty()) {
        auto u = *(sd.begin());
        sd.erase(sd.begin());
        for (const auto& v : g[u.first]) {
            if (dst[v] > dst[u.first] + 1) {
                if (dst[v] != inf && sd.size() > 0) {
                    auto it = sd.find(v);
                    if (it != sd.end())
                        sd.erase(it);
                }
                dst[v] = dst[u.first] + 1;
                sd.insert(std::make_pair(v, dst[v]));
            }
        }
    }
}

int main(int, char const**)
{
    try {
        data dta;
        dist dst;
        graph g;
        read_input(dta, dst, g);

        auto it = std::find(dta.begin(), dta.end(), "Isenbaev");

        if (it != dta.end()) {
            auto init = std::distance(dta.begin(), it);
            create_numbers(dst, g, init);
        }

        data_set sorted;
        for (const auto& it : dst) {
            sorted[dta[it.first]] = it.second;
        }
        for (const auto& it : sorted) {
            std::cout << it.first << " ";
            if (it.second < inf) {
                std::cout << it.second << "\n";
            }
            else {
                std::cout << "undefined\n";
            }
        }
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
