#include "homework_tools.h"
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
        otus::map_t m;
        otus::fill(m);

        otus::map_alloc_t m_ca;
        otus::fill(m_ca);
        otus::print(m_ca);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
