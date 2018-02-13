#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <type_traits>
#include <limits>

using data = std::map<std::string, int>;
using key = std::string;
using value = std::set<std::string>;
using graph = std::map<key, value>;

/// Insert the pointers to adjacent nodes u and v into grapth g. keep real value in d
void add_node(graph& g, const std::string& u, const std::string& v)
{
    g[u].insert(v);
    g[v].insert(u);
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

void read_input(data& d, graph& g)
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
            add_node(g, v[j], v[j_p]);
            d.insert(std::make_pair(v[j], std::numeric_limits<int>::max()));
        }
    }
}

void create_numbers(data& d, graph& g, std::string initial)
{
    data sd;
    sd.insert(std::make_pair(initial, 0));
    d[initial] = 0;
    while(!sd.empty()) {
        auto u = *(sd.begin());
        sd.erase(sd.begin());
        for (const auto& v : g[u.first]) {
            if (d[v] > d[u.first] + 1) {
                if (d[v] != std::numeric_limits<int>::max()) {
                    sd.erase(sd.find(v));
                }
                d[v] = d[u.first] + 1;
                sd.insert(std::make_pair(v, d[v]));
            }
        }
    }
}

int main(int, char const**)
{
    try {
        data d;
        graph g;
        read_input(d, g);
//        for (const auto& it : d) {
//            std::cout << it.first << ": " << it.second << "\n";
//        }
//        std::cout << "\n";

//        for (const auto& it : g) {
//            std::cout << it.first << ": ";
//            for (const auto& jt : it.second) {
//                std::cout << jt << ", ";
//            }
//            std::cout << "\n";
//        }
//        std::cout << "\n";

        create_numbers(d, g, "Isenbaev");

        for (const auto& it : d) {
            std::cout << it.first << " ";
            if (it.second < std::numeric_limits<int>::max()) {
                std::cout << it.second << "\n";
            }
            else {
                std::cout << "undefined\n";
            }
        }
//        std::cout << "\n";
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
