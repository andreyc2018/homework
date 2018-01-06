#include "homework_tools.h"
#include <iostream>

int main(int, char const**)
{
    try {
        otus::print_ip(std::cout, 0xfffffffeff);
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
