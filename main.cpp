#include <tuple>
#include <iostream>
#include "homework_tools.h"

/*! \todo print ips from the containers
 */
int main(int, char const**)
{
    try {
        std::tuple<char, unsigned char,
                short, unsigned short,
                int, unsigned int,
                long, unsigned long,
                float, double, long double> v;

        v = std::make_tuple(0x11, 0xf1, 0x2122, 0xe1e2,
                            0x31323334, 0xd1d2d3d4,
                            0x4142434445464748, 0xc1c2c3c4c5c6c7c8,
                            1.1, 2.2, 3.3);

        otus::print_all_ips(std::cout, v);

        std::vector<std::string> vip {"1", "2", "100", "999", "1"};
        otus::print_ip(std::cout, vip);

        std::list<std::string> lip {"1", "2", "100", "999", "1"};
        otus::print_ip(std::cout, lip);

        std::array<std::string, 5> aip {{"1", "2", "100", "999", "1"}};
        otus::print_ip(std::cout, aip);
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
