#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

template<typename I, typename O>
void read_input(I& input, O& spammers)
{
    std::string line; 
    std::getline(std::cin, line);
    size_t n = std::stoul(line);
    for (size_t i = 0; i < n; ++i) {
        std::getline(std::cin, line);
        auto search = input.find(line);
        if(search == input.end()) {
            input[line] = 1;
        }
        else {
            input[line] += 1;
            spammers.insert(line);
        }
    }
}

template<typename T>
void print_output(const T& spammers)
{
    for (const auto& s : spammers) {
        std::cout << s << "\n";
    }
}

int main(int, char const**)
{
    try {
        std::unordered_map<std::string, size_t> input;
        std::unordered_set<std::string> spammers;
        read_input(input, spammers);
        print_output(spammers);
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
