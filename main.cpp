#include "homework_tools.h"
#include "version.h"
#include <iostream>

void map_std_allocator()
{
    otus::map_t m;
    otus::fill(m);
}

void map_custom_allocator()
{
    otus::map_alloc_t m_ca;
    otus::fill(m_ca);
    otus::print(m_ca);
}

int main(int argc, char const** argv)
{
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'v') {
        std::cout << "Homework # " << VERSION << "\n";
        exit(0);
    }
    try
    {
        map_std_allocator();
        map_custom_allocator();
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
