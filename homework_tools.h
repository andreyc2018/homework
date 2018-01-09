#pragma once

#include "type_traits_helper.h"
#include <iostream>
#include <vector>
#include <numeric>

using otus::decay_t;
using otus::enable_if_t;
using otus::is_char;
using otus::is_stl_sequence_container;
using otus::is_stl_string;
using otus::to_string;

namespace otus {

using byte = unsigned char;

/*! \brief Convert value to a vector of bytes
 */
template <typename T>
std::vector<byte> to_bytes(const T& value)
{
    std::vector<byte> bytes;
    bytes.reserve(sizeof (value));
    const byte* begin = reinterpret_cast<const byte*>(std::addressof(value));
    const byte* end = begin + sizeof(T);
    std::copy(begin, end, std::back_inserter(bytes));
    return bytes;
}

/*! \brief Print a string like that looks like an IP address
 */
template<typename T>
std::ostream& print_ip_container(std::ostream& out, const T& ip, char delimiter)
{
    std::string result = std::accumulate(std::next(ip.begin()), ip.end(), to_string(ip.front()),
                                         [delimiter](std::string& s, typename T::value_type segment) {
                         return s + delimiter + to_string(segment);
        });
    return out << result;
}

/*! \brief Print original address presented a number
 */
template<typename T,
         enable_if_t<std::is_integral<T>::value || std::is_floating_point<T>::value, int> = 0>
std::ostream& print_original(std::ostream& out, const T& ip)
{
    return out << to_string(ip);
}

/*! \brief Print original address presented a number:
 *         specialization for <I>sequence_container</I>
 */
template<typename T,
         enable_if_t<is_stl_sequence_container<T>::value, int> = 0>
std::ostream& print_original(std::ostream& out, const T& ip)
{
    return print_ip_container(out, ip, ',');
}

/*! \brief Print address presented as a container
 */
template<typename T,
         enable_if_t<is_stl_sequence_container<T>::value, int> = 0>
int print_ip(std::ostream& out, const T& ip)
{
    print_original(out, ip) << " --> ";
    print_ip_container(out, ip, '.') << "\n";
    return 0;
}

/*! \brief Print address presented as an integral or floating point number
 */
template<typename T,
         enable_if_t<std::is_integral<T>::value
                     || std::is_floating_point<T>::value, int> = 0>
int print_ip(std::ostream& out, const T& ip)
{
    std::vector<byte> bytes = to_bytes(ip);
    print_original(out, ip) << " --> ";
    print_ip_container(out, bytes, '.') << "\n";
    return 0;
}

/*! \brief Print all IPs.
 * End of template resursion.
 */
template<std::size_t I = 0, typename... Tuple>
enable_if_t<I == sizeof...(Tuple), void>
print_all_ips(std::ostream&, std::tuple<Tuple...>&)
{ }

/*! \brief  Print all IPs.
 * Call print_ip for each element of std::tuple until I < sizeof(Tuple)
 */
template<std::size_t I = 0, typename... Tuple>
enable_if_t<I < sizeof...(Tuple), void>
print_all_ips(std::ostream& out, std::tuple<Tuple...>& t)
{
    otus::print_ip(out, std::get<I>(t));
    print_all_ips<I + 1, Tuple...>(out, t);
}

}
