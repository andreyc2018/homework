#include <iostream>
#include <vector>
#include <string>

using graph = std::vector<std::vector<std::string>>;

int main(int, char const**)
{
    try {
        size_t n;
        std::string line;
        std::getline(std::cin, line);
        n = std::stoul(line);
        for (size_t i = 0; i < n; ++i) {
            std::getline(std::cin, line);
            std::cout << line << "\n";
        }
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
