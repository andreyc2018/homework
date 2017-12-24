#include "ip_filter.h"
#include "version.h"
#include <iostream>

int main(int argc, char const** argv)
{
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'v') {
        std::cout << "Homework version " << VERSION << "\n";
        exit(0);
    }
    try
    {
        otus::pool_t ip_pool;

        for(std::string line; std::getline(std::cin, line);) {
            auto v = otus::split<otus::input_types_t>(line, '\t');
            ip_pool.push_back(otus::split<otus::entry_types_t>(v.at(0), '.'));
        }

        otus::print_reverse(std::cout, ip_pool);
        otus::print_filter(std::cout, ip_pool, 46u);
        otus::print_filter(std::cout, ip_pool, 46u, 70u);
        otus::print_filter_any(std::cout, ip_pool, 46u);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
