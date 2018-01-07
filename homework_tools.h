#pragma once

#include "type_traits_helper.h"
#include <iostream>
#include <vector>

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

/*! \brief Print original address presented a number
 */
template<typename T,
         enable_if_t<(std::is_integral<T>::value || std::is_floating_point<T>::value)
                     && !is_char<T>::value, int> = 0>
std::ostream& print_original(std::ostream& out, const T& ip)
{
    out << std::hex << ip;
    return out;
}

/*! \brief Print original address presented a number:
 *         specialization for <I>char</I> and <I>unsigned char</I>
 */
template<typename T,
         enable_if_t<is_char<T>::value, int> = 0>
std::ostream& print_original(std::ostream& out, const T& ip)
{
    return print_original(out, uint(ip));
}

template<typename T,
         enable_if_t<std::is_integral<T>::value, int> = 0>
std::ostream& print_segment(std::ostream& out, const T& ip)
{
    out << uint(ip);
    return out;
}

template<typename T,
         enable_if_t<is_stl_string<T>::value, int> = 0>
std::ostream& print_segment(std::ostream& out, const T& ip)
{
    out << ip;
    return out;
}

template<typename T>
std::ostream& print_ip_container(std::ostream& out, const T& ip, char delimiter)
{
    size_t i = 0;
    for (const auto& s : ip) {
        if (i++ != 0)
            out << delimiter;
        print_segment(out, s);
    }
    return out;
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
    std::cout << __PRETTY_FUNCTION__ << "\n";

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
    std::cout << __PRETTY_FUNCTION__ << "\n";

    std::vector<byte> bytes = to_bytes(ip);
    print_original(out, ip) << " --> ";
    print_ip_container(out, bytes, '.') << "\n";
    return 0;
}

}
