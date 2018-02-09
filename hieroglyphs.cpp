#include <iostream>

int main(int, char const**)
{
    try {
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
