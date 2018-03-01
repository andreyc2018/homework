#include <iostream>
#include <string>

int main(int, char const**)
{
    try {
        for (std::string input; std::getline(std::cin, input);) {
            std::cout << input << "\n";
        }
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
