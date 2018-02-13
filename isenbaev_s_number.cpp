#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <type_traits>
#include <limits>
#include <array>

using data = std::vector<std::string>;
using uv_nodes = std::array<std::string, 2>;
using dist = std::map<size_t, size_t>;
using graph = std::map<size_t, std::vector<size_t>>;
constexpr size_t inf = std::numeric_limits<size_t>::max();

void add_node(data& dta, dist& dst, graph& g, const uv_nodes& uv_n)
{
    std::array<size_t, 2> uv;
    for (size_t i = 0; i < uv_n.size(); ++i) {
        auto it = std::find(dta.begin(), dta.end(), uv_n[i]);
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
    for (size_t i = 0; i < n; ++i) {
        std::getline(std::cin, line);
        std::vector<std::string> v;
        tokenize(line, v);
        for (size_t j = 0; j < v.size(); ++j) {
            size_t j_p = (j < v.size()-1)? j+1 : 0;
            uv_nodes uv_n { v[j], v[j_p] };
            add_node(dta, dst, g, uv_n);
        }
    }
}

void create_numbers(data& dta, dist& dst, graph& g, size_t initial)
{
    if (dst.find(initial) == dta.end()) {
        return;
    }
    dist sd;
    sd.insert(std::make_pair(initial, 0));
    dta[initial] = 0;
    while(!sd.empty()) {
        auto u = *(sd.begin());
        sd.erase(sd.begin());
        for (const auto& v : g[u.first]) {
            if (dta[v] > dta[u.first] + 1) {
                if (dta[v] != inf) {
                    sd.erase(sd.find(v));
                }
                dta[v] = dta[u.first] + 1;
                sd.insert(std::make_pair(v, dta[v]));
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
            create_numbers(dta, dst, g, init);
        }

        for (const auto& it : dta) {
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
