#include "allocator.h"
#include "version.h"
#include <iostream>

int main(int argc, char const** argv)
{
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'v') {
        std::cout << "Homework # " << VERSION << "\n";
        exit(0);
    }
    try
    {
        std::cout << "Homework # " << VERSION << "\n";
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
