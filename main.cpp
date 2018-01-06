#include "homework_tools.h"
#include "version.h"
#include <iostream>

void std_map_std_allocator()
{
    otus::map_t m;
    otus::fill_map(m, otus::MaxElements);
}

void std_map_custom_allocator()
{
    otus::map_alloc_t m;
    otus::fill_map(m, otus::MaxElements);
    otus::print_map(std::cout, m);
}

void custom_list_std_allocator()
{
    otus::custom_list_t m;
    otus::fill_list(m, otus::MaxElements);
}

void custom_list_custom_allocator()
{
    otus::custom_list_alloc_t m;
    otus::fill_list(m, otus::MaxElements);
    otus::print_list(std::cout, m);
}

int main(int argc, char const** argv)
{
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'v') {
        std::cout << "Homework # " << VERSION << "\n";
        exit(0);
    }
    try
    {
        std_map_std_allocator();
        std_map_custom_allocator();
        custom_list_std_allocator();
        custom_list_custom_allocator();
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
