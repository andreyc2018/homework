#include "homework_tools.h"
#include <tuple>
#include <iostream>

/*! \brief Base case: end template recursion when I == sizeof(Tuple)
 */
template<std::size_t I = 0, typename... Tuple>
inline enable_if_t<I == sizeof...(Tuple), void>
print_ips(std::ostream&, std::tuple<Tuple...>&)
{ }

/*! \brief Call print_ip for each element of std::tuple until I < sizeof(Tuple)
 */
template<std::size_t I = 0, typename... Tuple>
inline enable_if_t<I < sizeof...(Tuple), void>
print_ips(std::ostream& out, std::tuple<Tuple...>& t)
{
    otus::print_ip(out, std::get<I>(t));
    print_ips<I + 1, Tuple...>(out, t);
}

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

        print_ips(std::cout, v);

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
