#include <iostream>
#include <string>
#include <map>
#include <set>

template<typename T>
char read_input(T& container)
{
    size_t n;
    std::string line; 
    std::getline(std::cin, line);
    n = std::stoul(line);
    for (size_t i = 0; i < n; ++i) {
        std::getline(std::cin, line);
        container[line[0]].insert(line[1]);
    }

    char request;
    std::cin >> request;
    return request;
}

template<typename T>
void print_input(const T& input)
{
    for (const auto& l : input) {
        std::cout << l.first << ": ";
        for (const auto& k : l.second) {
            std::cout << k << ", ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

template<typename T>
void print_output(const T& input, char request)
{
    const auto& output = input.find(request);
    if (output != input.end()) {
        for (const auto& s : output->second) {
            std::cout << output->first << s << "\n";
        }
    }
}

int main(int, char const**)
{
    try {
        std::map<char, std::set<char>> input;
        char request = read_input(input);
        // print_input(input);
        print_output(input, request);
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
