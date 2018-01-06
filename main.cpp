#include "homework_tools.h"
#include <tuple>
#include <iostream>

/*** Base case: end template recursion when I == sizeof(Tuple)
 */
template<std::size_t I = 0, typename... Tuple>
inline typename std::enable_if<I == sizeof...(Tuple), void>::type
print_ips(std::ostream&, std::tuple<Tuple...>&)
{ }

/*** Call print_ip for each element of std::tuple until I < sizeof(Tuple)
 */
template<std::size_t I = 0, typename... Tuple>
inline typename std::enable_if<I < sizeof...(Tuple), void>::type
print_ips(std::ostream& out, std::tuple<Tuple...>& t)
{
    otus::print_ip(out, std::get<I>(t));
    print_ips<I + 1, Tuple...>(out, t);
}

int main(int, char const**)
{
    try {
        std::tuple<char, unsigned char,
                short, unsigned short,
                int, unsigned int,
                long, unsigned long> v;
        v = std::make_tuple(0x11, 0xf1, 0x2122, 0xe1e2,
                            0x31323334, 0xd1d2d3d4,
                            0x4142434445464748, 0xc1c2c3c4c5c6c7c8);

        print_ips(std::cout, v);
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
